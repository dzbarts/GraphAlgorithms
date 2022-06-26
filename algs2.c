#include <stdio.h>
#include <stdlib.h>
#include "mgraph.c"
#include "stack.c"

//проверка графа на эйлеровость
int check_euler(mgraph *g){
    int count=0;
    int n=g->n;
    int i;
    for(i=0;i<n;i++){
        if(power(g,i)%2) count++;
        if(count>2) return 0;
    }
    if(count==1) return 0;
    if(count==2) return 2;
    return 1;

}

//поиск эйлерова пути из заданой вершины(вспомогательная функция для поиска эйлерова пути в графе)
void euler_path0(mgraph *g, int start, stack *l, stack *c){
    int n=g->n;
    int i=0;
    int t=1;
    int *add=g->address;
    push(l,start);
    while(t&&i<n) {
        if (add[n*start + i]) {
            t=0;
            add[start*n+i]=0;
            add[i*n+start]=0;
            euler_path0(g,i,l,c);
        }
        i++;
    }
    if(t){
        push(c, pop(l));
        if(l->n) euler_path0(g,pop(l),l,c);
    }
}

//функция поиска эйлерова пути в графе
stack *euler_path(mgraph *g){
    int t= check_euler(g);
    int start;
    stack *c=create();
    if(!t) return c;
    stack *l=create();
    if(t==1) start=0;
    else{
        mgraph *gr=g;
        int i=0;
        int f=1;
        while(power(g,f)%2==0){
            i++;
        }
        start=i;
    }
    euler_path0(g,start,l,c);
    free(l);
    return c;
}

