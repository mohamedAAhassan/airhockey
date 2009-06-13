#ifndef __STACK_H
#define __STACK_H

#include "Vertex.h"

struct el
{
    Vertex *v;
    el *prev;
};

class Stack
{
private:
    int s_size;

public:
    el *top;
    el *bottom;


    Stack()
    {
        top = NULL;
        bottom = NULL;
        s_size = 0;
//        top->prev = NULL;
 //       bottom->prev = NULL;
    }

    void push(Vertex *v)
    {
        el *novi = new el;
        novi->v = v;

        if(top == NULL && bottom == NULL)
        {
            top = novi;
            bottom = novi;
            novi->prev = NULL;
        }
        else
        {
            novi->prev = top;
            top = novi;
        }

        s_size++;
    }

    Vertex* pop()
    {
        el *tmp = top;
        top = top->prev;
        tmp->prev = NULL;
        Vertex *tmpv = tmp->v;
        delete tmp;
        return tmpv;

        s_size --;
    }

    Vertex* second()
    {
        return top->prev->v;
    }

    Vertex* top_el()
    {
        return top->v;
    }


    void loop()
    {
        for(el *e=top; e->prev!=NULL ;e=e->prev)
        {
            e->v->point.dumpInfo();
        }
    }

    int size()
    {
       /* if(top == NULL) return 0;
        int sum = 0;
        for(el *e=top; e->prev!=NULL ;e=e->prev)
            sum++;

        return ++sum;*/
        return this->s_size;
    }

    int scan_size()
    {
        int sum=0;
        for(el *e=top; e!=NULL ;e=e->prev)
            sum++;
        return sum;
    }

    void release()
    {
        if(this->size()>0)
        {
         //   for(el *e=top; e->prev!=NULL ;e=e->prev)

            el *e = top;
            while(e!=NULL)
            {
                el *tmp = top;
                top = top->prev;
                e = top;

                tmp->prev = NULL;
                delete tmp;
                s_size --;
            }
        }
    }

};


#endif
