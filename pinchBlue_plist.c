#include "pinchBlue.h"
#include <pthread.h>

typedef struct s_elem
{
    void* data;
    elem* next;
} elem;

typedef struct s_protecter_list
{
    pthread_mutex_t* mutex;
    elem* start;
} plist;

plist* pinchBlue_plist_createPlist()
{
    plist* out = (plist*)malloc(sizeof(plist));
    if(!out)
        return NULL;
    if (pthread_mutex_init(out->mutex, NULL))
    {
        free(out);
        return NULL;
    }
    out->start = NULL;
    return out;
}

elem* pinchBlue_plist_createElem(void* data)
{
    elem* out = (elem*)malloc(sizeof(elem));
    if (out)
    {
        out->data = data;
        out->next = NULL;
    }
    return out;
}

void pinchBlue_plist_addElem(void* data, plist* l)
{
    if (l->start)
    {
        elem* current = l->start;
        while (current->next)
            current = current->next;
        current->next = pinchBlue_plist_createElem(data);
    }
    else l->start = pinchBlue_plist_createElem(data);
}

void pinchBlue_plist_removeElem(int index, plist* l)
{
    if (pinchBlue_plist_count(l) <= index)
        return;
    if (index == 0)
    {
        elem* current = l->start;
        l->start = current->next;
        free(current->data);
        current->data = NULL;
        current->next = NULL;
        free(current);
    }
    else
    {
        int x = 0;
        elem* current = l->start;
        elem* next = current-> next;    
        while (x != index - 1)
        {
            next = next->next;
            current = current->next;
            x++;
        }
        current->next = current->next->next;
        free(next->data);
        next->data = NULL;
        next->next = NULL;
        free(next);
    }
}

void pinchBlue_plist_removeLastElem(plist* l)
{
    elem* current = l->start;
    if (current)
    {
        if(current->next)
        {
            while (current->next->next)
                current = current->next;
            free(current->next);
            current->next = NULL;
        }
        else
        {
            free(current->data);
            free(current);
            l->start = NULL;
        }
    }
}

int pinchBlue_plist_count(plist* l)
{
    int i = 0;
    elem* current = l->start;
    while (current)
    {
        i++;
        current = current->next;
    } 
    return i;
}

void* pinchBlue_plist_get(int index, plist* l)
{
    int x = 0;
    elem* current = l->start;
    while(current && x < index)
    {
        current = current->next;
        x++;
    }
    return (current) ? current->data : NULL;
}

void* pinchBlue_plist_getLast(plist* l)
{
    elem* current = l->start;
    while(current)
    {
        if(current->next)
            current = current->next;
        else break;
    }
    return (current) ? current->data : NULL;
}

void* pinchBlue_plist_getFirst(plist* l)
{
    return (l->start) ? l->start->data : NULL;
}

void* pinchBlue_plist_pop(plist* l)
{
    void* out = pinchBlue_plist_getLast(l);
    pinchBlue_plist_removeLastElem(l);
    return out;
}
