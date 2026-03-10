#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 1000

typedef struct{
	char name[100];
	char number[100];
	int score;
}STUDENT;

typedef struct ListNode{
	STUDENT stu;
	struct ListNode *next;
}ListNode;

ListNode *create_linked_list(STUDENT *stu,int n){
	ListNode *p=NULL,*head=NULL;
	int i=0;
	while(i<n){
		p=(ListNode *)malloc(sizeof(ListNode));
		p->stu=stu[i];
		p->next=head;
		head=p;
		i++;
	}
	return head;
}

ListNode *delete_linked_list(ListNode *head,char *target){
	ListNode *p=head,*q=head;
	while(p->next != NULL){
		if(strcmp(p->stu.name,target) == 0){
			if(p==head){
				head=head->next;
				return head;
			}
			q->next=p->next;
			free(p);
			return head;
		}
		q=p;
		p=p->next;
	}
	return head;
}

int main(){
	int n;char target[100];
	STUDENT stu[100];
	scanf("%d",&n);
	FILE *fp=fopen("output.txt","w");
	for(int i=0;i<n;i++){
		scanf("%s %s %d",stu[i].name,stu[i].number,&stu[i].score);
		fprintf(fp,"%s %s %d\n",stu[i].name,stu[i].number,stu[i].score);
	}
	
	scanf("%s",target);
	fclose(fp);
	fp=fopen("output.txt","r");
	for(int i=0;i<n;i++){
		fscanf(fp,"%s %s %d",stu[i].name,stu[i].number,&stu[i].score);
	}
	
	ListNode *head=create_linked_list(stu,n);
    fp=fopen("output.txt","w");

    ListNode *p=head;

	for(int i=0;i<n;i++){
			fprintf(fp,"%s %s %d\n",p->stu.name,p->stu.number,p->stu.score);
			p=p->next;
	}
	fclose(fp);
	
	fp=fopen("output.txt","a");
    p=delete_linked_list(head,target);

	for(int i=0;i<n-1;i++){
		fprintf(fp,"%s %s %d\n",p->stu.name,p->stu.number,p->stu.score);
		p=p->next;
	}
	fclose(fp);
	return 0;
}

