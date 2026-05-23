//链表结构及其环路检测
#include <stdio.h>
#include <stdlib.h>
FILE *fp;
typedef struct Node {
    int data;
    struct Node* next;
} Node;
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
//定位该链表环路的入口点
Node* findCycleEntry(Node* head) {
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            break;
        }
    }
    if (fast == NULL || fast->next == NULL) {
        return NULL; // 没有环
    }
    slow = head;
    while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
    }
    return slow; // 环路入口点
}
//计算环路中所包含的节点总数
int countCycleNodes(Node* head) {
    Node* entry = findCycleEntry(head);
    if (entry == NULL) {
        return 0;
    }
    int count = 1;
    Node* current = entry->next;
    while (current != entry) {
        count++;
        current = current->next;
    }
    return count;
}
int main() {
    fp = fopen("lab1_1_data.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    int data;
    Node* head1 = NULL,* head2 = NULL;
    //从文件中读取两行
    Node* p1 = NULL;
    while (fscanf(fp, "%d", &data) == 1) {
        Node* newNode = createNode(data);
        if (head1 == NULL) {
            head1 = newNode;
            p1 = newNode;
        } else {
            p1->next = newNode;
            p1 = newNode;
        }
        char c = fgetc(fp);
        if (c == '\n' || c == EOF) break;
    }
    
    Node* p2 = NULL;
    while (fscanf(fp, "%d", &data) == 1) {
        Node* newNode = createNode(data);
        if (head2 == NULL) {
            head2 = newNode;
            p2 = newNode;
        } else {
            p2->next = newNode;
            p2 = newNode;
        }
        char c = fgetc(fp);
        if (c == '\n' || c == EOF) break;
    }
    if (p2 != NULL) p2->next = head2; // 创建环
    if (p1 != NULL) p1->next = head2;//将head1的末尾节点指向head2中的起始节点
    FILE *output = fopen("lab1_1_output.txt", "w");
    if (output == NULL) {
        printf("无法打开输出文件\n");
        return 1;
    }
    Node* entry = findCycleEntry(head1);
    if (entry != NULL) {
        fprintf(output,"%d\n",entry->data);
        fprintf(output,"%d\n",countCycleNodes(head1));
    } else {
        fprintf(output,"No cycle\n");
    }
    fclose(output);
    fclose(fp);
    return 0;
}
