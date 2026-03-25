#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;
void initStack(Stack* s) {
    s->top = -1;
}
int isEmpty(Stack* s) {
    return s->top == -1;
}
int isFull(Stack* s) {
    return s->top == MAX_SIZE - 1;
}
void push(Stack* s, char c) {
    if (!isFull(s)) {
        s->data[++s->top] = c;
    }
}
char pop(Stack* s) {
    if (!isEmpty(s)) {
        return s->data[s->top--];
    }
    return '\0';
}
//设计一个算法，检查表达式中的 {}、[]、() 是否匹配，且必须满足以下优先级规则：{} 内
//可以包含 [] 或 ()，但 [] 内不能包含 {}，() 内不能包含 {} 或 []
int main(){
    while(1){
        char str[MAX_SIZE];
        printf("请输入表达式：");
        scanf("%s", str);
        Stack s;
        initStack(&s);
        int valid = 1;
        for (int i = 0; i < strlen(str); i++) {
            char c = str[i];
            if (c == '{' || c == '[' || c == '(') {
                push(&s, c);
            } 
            else if (c == '}' || c == ']' || c == ')') {
                if (isEmpty(&s)) {
                    valid = 0;
                    break;
                }
                char top = pop(&s);
                if ((c == '}' && top != '{') ||
                    (c == ']' && top != '[') ||
                    (c == ')' && top != '(')) {
                    valid = 0;
                    break;
                }
            }
        }
        if (!isEmpty(&s)) {
            valid = 0;
        }
        if (valid) {
            printf("表达式匹配\n");
        } else {
            printf("表达式不匹配\n");
        }
    }
    return 0;
}
