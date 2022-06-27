#include <stdio.h>
#include <stdlib.h>

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