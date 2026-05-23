//带括号的算术表达式求值
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
void push(Node** top, int data) {
    Node* newNode = createNode(data);
    newNode->next = *top;
    *top = newNode;
}
int pop(Node** top) {
    if (*top == NULL) {
        return -1; // 栈空返回特殊值
    }
    Node* temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}
char precedence(char op1, char op2) {
    if (op1 == '(' || op1 == '#') {
        return '<';
    }
    if ((op1 == '+' || op1 == '-') && (op2 == '*' || op2 == '/')) {
        return '<';
    }
    return '>';
}
int culculate(int operand1, int operand2, char operator) {
    switch (operator) {
        case '+': return operand1 + operand2;
        case '-': return operand1 - operand2;
        case '*': return operand1 * operand2;
        case '/': return operand1 / operand2;
        default: return 0; // 无效操作符
    }
}
Node** OPTR;
Node** OPND;
void initStack() {
    OPTR = (Node**)malloc(sizeof(Node*));
    OPND = (Node**)malloc(sizeof(Node*));
    *OPTR = NULL;
    *OPND = NULL;
}

int main() {
    fp = fopen("lab1_2_data.txt", "r");
    if (fp == NULL) {
        printf("无法打开文件\n");
        return 1;
    }
    initStack();
    push(OPTR, '#');
    int data;
    char op;
    
    while ((op = fgetc(fp)) != EOF) {
        if (op == ' ' || op == '\n' || op == '\r' || op == '\t') {
            continue;
        }

        if (op >= '0' && op <= '9') {
            ungetc(op, fp);
            fscanf(fp, "%d", &data);
            push(OPND, data);
            continue;
        }
        if (op == '(') {
            push(OPTR, op);
            continue;
        }
        if (op == ')') {
            while ((*OPTR)->data != '(') {
                char operator = pop(OPTR);
                int operand2 = pop(OPND);
                int operand1 = pop(OPND);
                int result = 0;
                result = culculate(operand1, operand2, operator);
                push(OPND, result);
            }
            pop(OPTR); // 弹出 '('
            continue;
        }
        while (precedence((*OPTR)->data, op) == '>') {
            char operator = pop(OPTR);
            int operand2 = pop(OPND);
            int operand1 = pop(OPND);
            int result = 0;
            result = culculate(operand1, operand2, operator);
            push(OPND, result);
        }
        push(OPTR, op);
    }
    // 处理剩余的操作符
    while ((*OPTR)->data != '#') {
        char operator = pop(OPTR);
        int operand2 = pop(OPND);
        int operand1 = pop(OPND);
        int result = 0;
        result = culculate(operand1, operand2, operator);
        push(OPND, result);
    }
    
    FILE* fp2 = fopen("lab1_2_output.txt", "w");
    if (fp2 == NULL) {
        printf("无法打开输出文件\n");
        return 1;
    }
    fprintf(fp2, "%d\n", pop(OPND));
    fclose(fp2);
    
    return 0;
}