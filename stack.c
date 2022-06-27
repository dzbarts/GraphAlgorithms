//#include <stdio.h>
//#include <stdlib.h>
//
////структура стека
//typedef struct stack{
//    int n;
//    int address[100];
//}stack;
//
////функция инициализации стека
//stack *create(){
//    stack *s= malloc(sizeof(stack));
//    s->n=0;
//}
//
////функция push
//int push(stack *s, int value){
//    int n=s->n;
//    *(s->address+n)=value;
//    s->n=n+1;
//    return value;
//}
//
////функция pop
//int pop(stack *s){
//    int n=s->n;
//    if(!n) return -1;
//    int value=*(s->address+n-1);
//    s->n=n-1;
//    return value;
//}
//
////функция выводв стека на экран
//void print_stack(stack *s){
//    int i;
//    int n=s->n;
//    if(!n){
//        printf("stack is empty");
//        return;
//    }
//    int *add=s->address;
//    for(i=0;i<n;i++) printf("%d ",add[i]);
//}
//
//
//
//
