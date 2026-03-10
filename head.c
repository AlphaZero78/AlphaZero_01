#include<stdio.h>
#include<stdlib.h>
#define N 1000

typedef struct ListNode{
	int val;
	struct ListNode *next;
}ListNode;

ListNode *create_linked_list(int *values,int n){
	ListNode *p=NULL,*head=NULL;
	int i=0;
	while(i<n){
		p=(ListNode *)malloc(sizeof(ListNode *));
		p->val=values[i];
		p->next=head;
		head=p;
		i++;
	}
	return head;
}

void traverse_linked_list(ListNode *head,int n){
	ListNode *p=head;
	for(int i=0;i<n;i++){
		printf("%d ",p->val);
		p=p->next;
	}
}

int main(){
	int values[N]={0},i=0,n;
	scanf("%d",&n);
	while(i<n){
		scanf("%d",&values[i]);
		i++;
	}
	ListNode *head=create_linked_list(values,n);
	traverse_linked_list(head,n);
	return 0;
}
