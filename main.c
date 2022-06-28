#include <stdio.h>
#include <stdlib.h>

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
        current=g;
        while(current){
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
    while(current){
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


//структура графа в виде матрицы инцидентности
typedef struct mgraph{
    int n;//количество вершин в графе
    int *address;//ссылка на двумерный массив
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
    adj_list *list2=NULL;
    pair p;
    p.number=number;
    p.distance=0;
    list2=add(list2,p);
    adj_list *list1=list2;
    adj_list *list, *l;
    graph *start= get_vertex(g,number);
    graph *current;
    int curr, status, num;
    int t=1;
    while(list1&&t){
        t=0;
        list2=NULL;
        list=list1;
        while(list){
            curr=list->vertex.number;
            current= get_vertex(g,curr);
            status=current->status;
            if (!status){
                t=1;
                current->status=1;
                printf("%d ",curr);
                l=current->vertexes;
                while(l){
                    num=l->vertex.number;
                    p.number=num;
                    list2=add(list2,p);
                    l=l->next;
                }
            }
            list=list->next;
        }
        list1=list2;
    }
}

//алгоритм Белмана-Форда
double *Belman_Ford(graph *g, int vertex){
    adj_list *current;
    pair p;
    int n=0;
    int number;
    int curr;
    int dist;
    double distance;
    graph *gr=g;
    while(gr){
        n++;
        gr=gr->next;
    }
    double *res= malloc(n * sizeof(double));
    int i;
    for(i=0;i<n;i++){
        if(i==vertex) res[i]=0;
        else res[i]=10000;
    }
    adj_list *list2=NULL;
    p.number=vertex;
    p.distance=0;
    list2=add(list2,p);
    adj_list *list=list2;
    for(i=0;i<n-1;i++){
        list2=NULL;
        while(list){
            curr=list->vertex.number;
            current = get_vertex(g, curr)->vertexes;
            while(current){
                number=current->vertex.number;
                distance=current->vertex.distance;
                dist=res[curr]+distance;
                if(dist<res[number]) res[number]=dist;
                current=current->next;
                p.number=number;
                p.distance=0;
                list2=add(list2,p);
            }
            list=list->next;
        }
        list=list2;
    }
    return res;
}

void top_sort(graph *g, graph *start, int *res, int *n){
    if(start->status) return;
    start->status=1;
    adj_list *list=start->vertexes;
    graph *current;
    while(list){
        current= get_vertex(g,list->vertex.number);
        if(!(current->status)){
            top_sort(g,current,res,n);
        }
        list=list->next;
    }
    res[*n]=start->number;
    *n=*n-1;
}

graph *Topological_Sort(graph *g){
    graph *current=g;
    int *n= malloc(sizeof(int));
    *n=0;
    while(current){
        *n=*n+1;
        current=current->next;
    }
    current=g;
    int *res= malloc(*n * sizeof(int));
    *n=*n-1;
    int k=*n;
    while(current){
        top_sort(g,current,res,n);
        current=current->next;
    }
    free(n);
    int i;
    graph *elem= malloc(sizeof(graph));
    graph *old;
    old= get_vertex(g,res[0]);
    elem->is_empty=old->is_empty;
    elem->number=old->number;
    elem->status=old->status;
    elem->vertexes=old->vertexes;
    graph *ng=elem;
    graph *new_graph=elem;
    for(i=1;i<=k;i++){
        elem= malloc(sizeof(graph));
        old= get_vertex(g,res[i]);
        elem->is_empty=old->is_empty;
        elem->number=old->number;
        elem->status=old->status;
        elem->vertexes=old->vertexes;
        ng->next=elem;
        ng=ng->next;
    }
    ng->next=NULL;
    free(res);
    zero_status(new_graph);
    return new_graph;
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


// Структура для представления каждого звена графа
struct node {
    int d; // вес
    int c; // 1-красный, 0-черный
    struct node* p; // родитель
    struct node* r; // правый ребенок
    struct node* l; // левый ребенок
};

// глобальный корень
struct node* root = NULL;

// функция для вствки бинарного дерева поиска
struct node* bst(struct node* trav,
                 struct node* temp)
{
    // если дерево пустое, возвращает новое звено
    if (trav == NULL)
        return temp;

    // иначе спускается по дереву вниз
    if (temp->d < trav->d)
    {
        trav->l = bst(trav->l, temp);
        trav->l->p = trav;
    }
    else if (temp->d > trav->d)
    {
        trav->r = bst(trav->r, temp);
        trav->r->p = trav;
    }

    // Возвращает указатель узла
    return trav;
}

// функция разворота по часовой
void rightrotate(struct node* temp)
{
    struct node* left = temp->l;
    temp->l = left->r;
    if (temp->l)
        temp->l->p = temp;
    left->p = temp->p;
    if (!temp->p)
        root = left;
    else if (temp == temp->p->l)
        temp->p->l = left;
    else
        temp->p->r = left;
    left->r = temp;
    temp->p = left;
}

// функция для разворота против часовой
void leftrotate(struct node* temp)
{
    struct node* right = temp->r;
    temp->r = right->l;
    if (temp->r)
        temp->r->p = temp;
    right->p = temp->p;
    if (!temp->p)
        root = right;
    else if (temp == temp->p->l)
        temp->p->l = right;
    else
        temp->p->r = right;
    right->l = temp;
    temp->p = right;
}

// балансировка
void fixup(struct node* root, struct node* pt)
{
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;

    while ((pt != root) && (pt->c != 0)
           && (pt->p->c == 1))
    {
        parent_pt = pt->p;
        grand_parent_pt = pt->p->p;

        /* Case : A
            родитель - левый ребенок грендов */
        if (parent_pt == grand_parent_pt->l)
        {

            struct node* uncle_pt = grand_parent_pt->r;

            /* Case : 1
                дядя - красный
                необходимо лишь перекрасить
            */
            if (uncle_pt != NULL && uncle_pt->c == 1)
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }

            else {

                /* Case : 2
                    родитель - правый ребенок грендов
                    необходим поворот против часовой
                 */
                if (pt == parent_pt->r) {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /* Case : 3
                    родитель - левый ребенок грендов
                    необходим поворот по часовой
                 */
                rightrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }

            /* Case : B
                родитель - правый ребенок грендов
                */
        else {
            struct node* uncle_pt = grand_parent_pt->l;

            /* Case : 1
                дядя - красный
                необходимо лишь перекрасить
                */
            if ((uncle_pt != NULL) && (uncle_pt->c == 1))
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
            else {
                /* Case : 2
                    родитель - левый ребенок грендов
                    необходим поворот по часовой
                 */
                if (pt == parent_pt->l) {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }

                /* Case : 3
                    родитель - правый ребенок грендов
                    необходим поворот против часовой
                 */
                leftrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
    }

    root->c = 0;
}

// Функция для печати неупорядоченного обхода сбалансированного дерева
void inorder(struct node* trav)
{
    if (trav == NULL)
        return;
    inorder(trav->l);
    printf("%d ", trav->d);
    inorder(trav->r);
}

// итоговая функция
int RBTree()
{
    int n = 7;
    int a[7] = { 7, 5, 20, 4, 117, 2, 22 };

    for (int i = 0; i < n; i++) {

        // выделение памяти и инициализация
        // 1. по умолчанию увет красный
        // 2. родители и указатели NULL
        // 3. вес берется соответственно из массива
        struct node* temp
                = (struct node*)malloc(sizeof(struct node));
        temp->r = NULL;
        temp->l = NULL;
        temp->p = NULL;
        temp->d = a[i];
        temp->c = 1;

        // создание дерева
        root = bst(root, temp);

        // балансировка
        fixup(root, temp);
    }

    printf("Упорядоченное сбалансированное дерево\n");
    inorder(root);

    return 0;
}


#include <limits.h>
#include <stdbool.h>

// Количество вершин в графе
#define V 9

// Вспомогательная функция для поиска вершины с минимальным значением расстояния из набора вершин,
// еще не включенных в дерево кратчайших путей.
int minDistance(int dist[], bool sptSet[])
{
    // Инициализация минимального значения
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Вспомогательная функция для печати построенного массива расстояний
void printSolution(int dist[])
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Функция, которая реализует алгоритм кратчайшего пути Дейкстры с одним источником для графа,
// представленного с использованием представления матрицы смежности.
void dijkstra(int graph[V][V], int src)
{
    int dist[V];
    // Выходной массив. dist[i] будет содержать кратчайшее расстояние от src до i

    bool sptSet[V];
    // sptSet[i] будет истинным, если вершина i включена в дерево кратчайших путей
    // или кратчайшее расстояние от src до i завершено

    // Инициализация всего расстояния как INFINITE и stpSet[] как false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Расстояние исходной вершины от самой себя всегда равно 0
    dist[src] = 0;

    // Поиск кратчайшего пути для всех вершин
    for (int count = 0; count < V - 1; count++) {
        // Выбирается вершина минимального расстояния из набора еще не обработанных вершин. u всегда равно src в первой итерации.
        int u = minDistance(dist, sptSet);

        // Отмечаем выбранную вершину как пройденную
        sptSet[u] = true;

        // Обновление значений расстояний смежных вершин выбранной вершины.
        for (int v = 0; v < V; v++)

            // Необходимо обновлять dist[v] только в том случае, если его нет в sptSet,
            // есть ребро от u до v и общий вес пути от src до v через u меньше текущего значения dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // печать итога
    printSolution(dist);
}

// итоговая функция с тестовым набором
int Dijkstra()
{
    int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                        { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                        { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                        { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                        { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                        { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                        { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                        { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                        { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };

    dijkstra(graph, 0);

    return 0;
}


#define V 4

#define INF 99999

void Solution(int dist[][V]);

void floydWarshall (int graph[][V])
{
    /* dist[][] будет выходной матрицей которая будет
      иметь кратчайшие расстояния между каждой парой вершин
    */
    int dist[V][V], i, j, k;

    /* Инициализация матрицы решения так же,
     * как матрицы входного графа. Или мы можем сказать,
     * что начальные значения кратчайших расстояний основаны
     * на кратчайших путях без учета промежуточных вершин. */
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    /* Добавляем все вершины одну за другой в набор промежуточных вершин.
     ---> Перед началом итерации у нас есть кратчайшие
     расстояния между всеми парами вершин, такие, что
     кратчайшие расстояния рассматривают только вершины в
     множестве {0, 1, 2, .. k-1} как промежуточные вершины.
     ----> После окончания итерации вершина k добавляется
     к множеству промежуточных вершин, и множество становится {0, 1, 2, .. k} */
    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                // Если вершина k находится на кратчайшем
                // пути из i в j, то обновляем значение dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    printSolution(dist);
}

void Solution(int dist[][V])
{
    printf ("The following matrix shows the shortest distances"
            " between every pair of vertices \n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf ("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// тест
int Floyd_Warshall()
{
    int graph[V][V] = { {0, 5, INF, 10},
                        {INF, 0, 3, INF},
                        {INF, INF, 0, 1},
                        {INF, INF, INF, 0}
    };

    floydWarshall(graph);
    return 0;
}



int main() {
    graph *gr;
    graph *g=NULL;
    mgraph *mg=NULL;
    stack *s;
    double *res;
    int i;
    int t;
    int n;
    double m;
    int from;
    int to;
    char status;
    double distance;
    char answer[100000];

    while (atoi(answer) != 7)
    {
        printf("Input number of action:\n");
        printf("    -1) To exit\n");
        printf("    0) Floyd_Warshall\n");
        printf("    1) RBTree\n");
        printf("    2) Dijkstra\n");
        printf("    3) Create list graph\n");
        printf("    4) Add vertex to list graph\n");
        printf("    5) Add edge to list graph\n");
        printf("    6) Delete edge from list graph\n");
        printf("    7) Delete vertex from list graph\n");
        printf("    8) DFS\n");
        printf("    9) BFS\n");
        printf("    10) Topological Sort\n");
        printf("    11) Bellman-Ford\n");
        printf("    12) Create matrix graph\n");
        printf("    13) Add edge to matrix graph\n");
        printf("    14) Delete edge from matrix graph\n");
        printf("    15) Euler's path\n");
        printf("    16) Print list graph\n");
        printf("    17) Print matrix graph\n");
        scanf("%s",answer);


        switch (atoi(answer))
        {
            case -1:
                return 0;
            case 0:
                Floyd_Warshall();
                printf("\n######################:\n");
                break;
            case 1:
                RBTree();
                printf("\n######################:\n");
                break;
            case 2:
                Dijkstra();
                printf("\n######################:\n");
                break;
            case 3:
                if(!g){
                    g=init();
                    printf("Graph(list) has successfully been created\n");
                }
                else printf("Graph(list) has already been initialized\n");
                break;
            case 4:
                printf("Enter vertex number and its status:\n");
                t = scanf("%d %d", &n,&i);
                printf("\n");
                if(t!=2) printf("Wrong input\n");
                else{
                    add_vertex(g,n,i);
                    printf("Vertex has successfully been added\n");
                }
                break;
            case 5:
                printf("Enter 2 vertex numbers and distance between them:\n");
                t = scanf("%d %d %lf", &n,&i,&m);
                printf("\n");
                if(t!=3) printf("Wrong input\n");
                else{
                    add_edge(g,n,i,m);
                    printf("Edge has successfully been added\n");
                }
                break;
            case 6:
                printf("Enter 2 vertex numbers:\n");
                t = scanf("%d %d", &n,&i);
                printf("\n");
                if(t!=2) printf("Wrong input\n");
                else{
                    del_edge(g,n,i);
                    printf("Edge has successfully been deleted\n");
                }
                break;
            case 7:
                printf("Enter vertex number:\n");
                t = scanf("%d %d", &n);
                printf("\n");
                if(t!=1) printf("Wrong input\n");
                else{
                    del_vertex(g,n);
                    printf("Vertex has successfully been deleted\n");
                }
                break;
            case 8:
                printf("Enter vertex number:\n");
                t = scanf("%d", &n);
                printf("\n");
                if(t!=1) printf("Wrong input\n");
                else DFS(g,n);
                zero_status(g);
                printf("\n");
                break;
            case 9:
                printf("Enter vertex number:\n");
                t = scanf("%d", &n);
                printf("\n");
                if(t!=1) printf("Wrong input\n");
                else BFS(g,n);
                zero_status(g);
                printf("\n");
                break;
            case 10:
                gr= Topological_Sort(g);
                print_graph(gr);
                break;
            case 11:
                printf("Enter vertex number:\n");
                t = scanf("%d", &n);
                printf("\n");
                if(t!=1) printf("Wrong input\n");
                res= Belman_Ford(g,n);
                gr =g;
                i=0;
                printf("distances from vertex number %d to other vertexes:\n",n);
                while(gr){
                    printf("distance to vertex number %d equals %0.2f\n",i,res[i]);
                    i++;
                    gr=gr->next;
                }
                break;
            case 12:
                if(!mg) {
                    printf("Enter number of vertexes in graph(matrix):\n");
                    t = scanf("%d", &n);
                    printf("\n");
                    if(t!=1) {
                        printf("Wrong input\n");
                        continue;
                    }
                    mg=minit(n);
                    printf("Graph(matrix) has successfully been created\n");
                }
                else printf("Graph(matrix) has already been initialized\n");
                break;
            case 13:
                printf("Enter 2 vertex numbers:\n");
                t = scanf("%d %d", &n,&i);
                printf("\n");
                if(t!=2) printf("Wrong input\n");
                else{
                    madd_edge(mg,n,i);
                    printf("Edge has successfully been added\n");
                }
                break;
            case 14:
                printf("Enter 2 vertex numbers:\n");
                t = scanf("%d %d", &n,&i);
                printf("\n");
                if(t!=2) printf("Wrong input\n");
                else{
                    mdel_edge(mg,n,i);
                    printf("Edge has successfully been deleted\n");
                }
                break;
            case 15:
                s= euler_path(mg);
                print_stack(s);
                printf("\n");
                break;
            case 16:
                print_graph(g);
                printf("\n");
                break;
            case 17:
                print_gr(mg);
                printf("\n");
                break;
            default:
                continue;
        }

    }

    return 0;
}