#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int currentTime = 0; // 当前时间
typedef struct Patient {
    char name[20];
    int severity;      // 病情严重程度 (1-10),>=7急诊
    int arrivalTime;   // 到达时间
    int duration;      // 治疗耗时 (2 + severity)
} Patient;
typedef struct Doctor {
    int id;             // 医生编号 (1, 2, 3)
    bool isBusy;        // 是否忙碌
    int finishTime;     // 治疗当前患者的预计结束时间
    Patient currentP;   // 正在治疗的患者信息
} Doctor;
typedef struct Queue {
    Patient* patients[100];
    int front; // 队头索引
    int rear;  // 队尾索引 
} Queue;
// 当医生忙碌时 —— 在治疗病人currentP —— 预测结束时间finishTime
// 当医生空闲时 —— finishTime，currentP 没有实际含义
// 有急诊患者时必须先治疗急诊患者，只有当没有急诊患者时，才按顺序接诊普通患者
// 急诊患者病情非常严重，必须等到所有 3 名医生全部空闲，一起治疗这位病人
void Initqueue(Queue* queue) {
    queue->front = 0;
    queue->rear = 0;
}
bool IsEmpty(Queue* queue) {
    return queue->front == queue->rear;
}
Queue Normal_queue; // 普通病人队列
Queue Emergency_queue; // 急诊病人队列
void Enqueue(Queue* queue,Patient* p) {
    queue->patients[queue->rear] = p;
    queue->rear++;
}
Patient* Dequeue(Queue* queue) {
    if (queue->front == queue->rear) {
        return NULL; // 队列为空
    }
    Patient* p = queue->patients[queue->front];
    queue->front++;
    return p;
}
int main(){
    FILE *fp = fopen("lab2_data.txt", "r");
    int patientCount;
    fscanf(fp, "%d", &patientCount);
    Patient patients[100];
    for(int i = 0; i < patientCount; i++) {
        fscanf(fp, "%s %d %d", patients[i].name, &patients[i].arrivalTime, &patients[i].severity);
        patients[i].duration = 2 + patients[i].severity;
    }
    fclose(fp);

    Doctor doctors[3];
    for(int i = 0; i < 3; i++) {
        doctors[i].id = i + 1;
        doctors[i].isBusy = false;
        doctors[i].finishTime = 0;
    }
    Initqueue(&Normal_queue);
    Initqueue(&Emergency_queue);

    fp = fopen("lab2_output.txt", "w");
    fprintf(fp,"--- 医院仿真系统启动 ---\n");
    for(int time = 0; time < 100; time++) {
        for(int i=0;i<patientCount;i++){
            if(patients[i].arrivalTime == time) {
                if(patients[i].severity <7){
                    Enqueue(&Normal_queue, &patients[i]);
                    fprintf(fp, "[Time %d]: 患者 %s 到达\n", time, patients[i].name);                    
                } else {
                    Enqueue(&Emergency_queue, &patients[i]);
                    fprintf(fp, "[Time %d]: 急诊患者 %s 到达\n", time, patients[i].name);
                }
            }
        }

        bool allRest = true;
        for(int i=0;i<3;i++) {
            if(doctors[i].isBusy && doctors[i].finishTime == time) {
                fprintf(fp, "[Time %d]: %d号医生完成治疗患者 %s\n", time, doctors[i].id, doctors[i].currentP.name);
                doctors[i].isBusy = false;
            }
        }
        if(IsEmpty(&Emergency_queue)) {
            for(int i=0;i<3;i++) {
                if(!IsEmpty(&Normal_queue)) { 
                    for(int j=0;j<3;j++) {
                        if(!doctors[j].isBusy) {
                            Patient *p = Dequeue(&Normal_queue);
                            doctors[j].currentP = *p;
                            doctors[j].isBusy = true;
                            doctors[j].finishTime = time + p->duration;
                            fprintf(fp, "[Time %d]: %d号医生接诊患者 %s ,预计 Time %d 结束\n", time, doctors[j].id, p->name, doctors[j].finishTime);
                            break;
                        }
                    }
                }   
            }         
        }
        else{
            for(int i=0;i<3;i++) {
                if(doctors[i].isBusy) {
                    allRest = false;
                    break;
                }
            }
        }
        if(!IsEmpty(&Emergency_queue) && allRest) {
            Patient *p = Dequeue(&Emergency_queue);
            for(int i=0;i<3;i++) {
                doctors[i].currentP = *p;
                doctors[i].isBusy = true;
                doctors[i].finishTime = time + p->duration;
            }
            fprintf(fp, "[Time %d]: 1号、2号、3号医生开始救治急诊患者 %s。预计 Time %d 结束\n", time, p->name, doctors[0].finishTime);
        }
    }
    if(IsEmpty(&Emergency_queue) && IsEmpty(&Normal_queue)) {
        fprintf(fp,"所有患者治疗完毕，系统运行结束\n");
    }
    return 0;
}