#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//给定一个不带头结点的单链表，请设计一个递归算法实现链表的原地逆序
typedef struct Node {
    int data;
    struct Node* next;
} Node;
Node* reverse(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    Node* newHead = reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return newHead;
}
