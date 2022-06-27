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