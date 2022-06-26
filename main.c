#include <stdio.h>
#include <stdlib.h>

//структура пара, в которой будет храниться номер сежной вершины и расстояние до нее
typedef struct pair{
    unsigned int number;
    double distance;
}pair;

//структура список смежных вершин
typedef struct adj_list{
    pair vertex;
    struct adj_list *next;
}adj_list;

//функция добавления элемента в список смежных вершин
adj_list *add(adj_list *list, pair new_pair){
    if (!list){
        adj_list *new_list= (malloc(sizeof(adj_list)));
        new_list->vertex=new_pair;
        new_list->next=NULL;
        return new_list;
    }
    adj_list *current=list;
    while(current->next&&current->vertex.number!=new_pair.number) current=current->next;
    if (current->vertex.number==new_pair.number){
        current->vertex=new_pair;
        return list;
    }
    adj_list *elem = (malloc(sizeof(adj_list)));
    elem->vertex=new_pair;
    elem->next=NULL;
    current->next=elem;
    return list;
}

//функция удаления элемента из списка смежных вершин
adj_list *del(adj_list *list, unsigned int number){
    if (!list) return list;
    adj_list *current=list;
    if(list->vertex.number==number){
        list=list->next;
        free(current);
        return list;
    }
    while(current->next&&current->next->vertex.number!=number){
        current=current->next;
    }
    if (!current->next) return list;
    adj_list *next=current->next;
    current->next=current->next->next;
    free(next);
    return list;
}

//функция полного удаления списка смежных вершин
adj_list *del_list(adj_list *list){
    if (!list) return list;
    adj_list *current=list;
    adj_list *next=list;
    while(next){
        next=next->next;
        free(current);
        current=next;
    }
    return NULL;
}

//структура граф в виде списков смежности
typedef struct graph{
    unsigned char is_empty;//поле, позволяющее определить пустой ли граф
    unsigned int number;//номер вершины
    unsigned char status;//ствтус вершины
    adj_list *vertexes;//список смежных вершин для данной вершины
    struct graph *next;//ссылка на следующую вершину графа
}graph;

//функция инициализации графа
graph *init(){
    graph *new_graph= (malloc(sizeof(graph)));
    new_graph->is_empty=1;
    new_graph->vertexes=NULL;
    new_graph->next=NULL;
    return new_graph;
}

//функция добавления вершины в граф
void add_vertex(graph *g, unsigned int number, unsigned char status){
    if (g->is_empty){
        g->is_empty=0;
        g->number=number;
        g->status=status;
        return;
    }
    graph *current = g;
    while(current->next&&current->number!=number) current=current->next;
    if (current->number==number){
        current->status=status;
        return;
    }
    graph *new_g=init();
    new_g->number=number;
    new_g->status=status;
    current->next=new_g;
}

//функция добавления ребра в граф
void add_edge(graph *g, unsigned int from, unsigned int to, double distance){
    graph *current = g;
    pair pair0;
    pair0.number =to;
    pair0.distance=distance;
    if (g->is_empty) add_vertex(g,from,0);
    while(current->number!=from&&current->next) current=current->next;
    if (current->number!=from){
        graph *new_g= init();
        new_g->is_empty=0;
        new_g->number=from;
        new_g->status=0;

        new_g->vertexes=add(new_g->vertexes, pair0);
        current->next=new_g;
    }
    else current->vertexes=add(current->vertexes,pair0);
    current=g;
    while(current->number!=to&&current->next) current=current->next;
    if (current->number!=to){
        graph *new_g= init();
        new_g->is_empty=0;
        new_g->number=to;
        new_g->status=0;
        current->next=new_g;
        return;
    }
}


//функция удаления ребра из графа
void del_edge(graph *g, unsigned int from, unsigned int to){
    graph *current=g;
    while(current->next&&current->number!=from) current=current->next;
    if (current->number!=from) return;
    current->vertexes=del(current->vertexes, to);
}

//функция удаления вершины из графа
void del_vertex(graph *g, unsigned int number){
    graph *current=g;
    graph *prev=g;
    if (g->number==number&&!g->next){
        del_list(g->vertexes);
        free(g);
        g->is_empty=1;
        g->vertexes=NULL;
        g->next=NULL;
        return;
    }
    if(g->number==number){
        g->status=g->next->status;
        g->number=g->next->number;
        del_list(g->vertexes);
        g->vertexes=g->next->vertexes;
        prev=g->next;
        g->next=g->next->next;
        free(prev);
        while(current->next){
            current->vertexes=del(current->vertexes,number);
            current=current->next;
        }
        return;
    }
    while(current->next&&current->number!=number){
        prev=current;
        current=current->next;
    }
    if (current->number!=number) return;
    prev->next=current->next;
    del_list(current->vertexes);
    free(current);
    current=g;
    while(current->next){
        current->vertexes=del(current->vertexes,number);
        current=current->next;
    }
}

//функция печати графа на экран
void print_graph(graph *g){
    graph *current=g;
    if(current->is_empty){
        printf("Graph is empty");
        return;
    }
    while(current){
        printf("number = %d, status=%d, vertexes={" ,current->number, current->status);
        adj_list *list=current->vertexes;
        while(list){
            printf("(to =%d, distance=%.2f)",list->vertex.number, list->vertex.distance);
            if(list->next) printf(", ");
            list=list->next;
        }
        printf("}\n");
        current=current->next;
    }

}

//функция обнуления статуса всех вершин графа
void zero_status(graph *g){
    graph *current=g;
    while (current){
        current->status=0;
        current=current->next;
    }
}

//функция получения адреса вершины в шрафе
graph *get_vertex(graph *g, unsigned int number){
    graph *current=g;
    while(current&&current->number!=number) current=current->next;
    return current;
}

//алгоритм поиска в глубину в графе
void DFS(graph *g, int number){
    graph *start=get_vertex(g,number);
    adj_list *current;
    if (!start->status){
        start->status=1;
        printf("%d ",start->number);
        current=start->vertexes;
        while(current){
            DFS(g,current->vertex.number);
            current=current->next;
        }
    }
    else return;
}

//алгоритм поиска в ширину в графе
void BFS(graph *g, int number){
    graph *start=get_vertex(g,number);
    adj_list *current;
    if (!start->status) {
        start->status = 1;
        printf("%d ", start->number);
    }
    current=start->vertexes;
    while(current){
        unsigned int n=current->vertex.number;
        graph *address=get_vertex(g,n);
        if(!address->status){
            printf("%d ",n);
            address->status=1;
        }
        current=current->next;
    }
    current=start->vertexes;
    while(current){
        unsigned int n=current->vertex.number;
        BFS(g,n);
        current=current->next;
    }

}

//структура графа в виде матрицы инцидентности
typedef struct mgraph{
    int n;
    int *address;
}mgraph;

//функция инициализации графа
mgraph *minit(int n){
    mgraph *new_graph= malloc(sizeof(mgraph));
    new_graph->n=n;
    int *address = malloc(n*n*sizeof(int));
    int i;
    for(i=0;i<n*n;i++) address[i]=0;
    new_graph->address=address;
    return new_graph;
}

//функция добавления ребра в графе
void madd_edge(mgraph *g, int from, int to){
    if (from>=g->n||to>=g->n) return;
    int n1=g->n*from+to;
    int n2=g->n*to+from;
    int *add=g->address;
    add[n1]=1;
    add[n2]=1;
}

//функция удаления ребра в графе
void mdel_edge(mgraph *g, int from, int to){
    if (from>=g->n||to>=g->n) return;
    int n1=g->n*from+to;
    int n2=g->n*to+from;
    int *add =g->address;
    add[n1]=0;
    add[n2]=0;
}

//функция получения степени вершины графа
int power(mgraph *g, int v){
    int n=g->n;
    int *add=g->address;
    int i;
    int p=0;
    for(i=0;i<n;i++) p=p+add[v*n+i];
    return p;
}

//функция печати графа на экран
void print_gr(mgraph *g){
    unsigned int n = g->n;
    int i;
    printf("  ");
    for (i=0; i<n; i++) printf("%d ",i);
    printf("\n0 ");
    for(i=0; i<n*n; i++){
        printf("%d ", g->address[i]);
        if ((i+1)%n==0) {
            printf("\n");
            if (i != n * n - 1) printf("%d ", (i + 1) / n);
        }
    }
}

//структура стека
typedef struct stack{
    int n;
    int address[100];
}stack;

//функция инициализации стека
stack *create(){
    stack *s= malloc(sizeof(stack));
    s->n=0;
}

//функция push
int push(stack *s, int value){
    int n=s->n;
    *(s->address+n)=value;
    s->n=n+1;
    return value;
}

//функция pop
int pop(stack *s){
    int n=s->n;
    if(!n) return -1;
    int value=*(s->address+n-1);
    s->n=n-1;
    return value;
}

//функция выводв стека на экран
void print_stack(stack *s){
    int i;
    int n=s->n;
    if(!n){
        printf("stack is empty");
        return;
    }
    int *add=s->address;
    for(i=0;i<n;i++) printf("%d ",add[i]);
}

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


