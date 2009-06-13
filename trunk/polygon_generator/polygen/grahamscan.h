#ifndef __GRAHAM_SCAN
#define __GRAHAM_SCAN

#include <ctime>
#include "Vertex.h"
#include "Point3.h"

#include "seznam.h"
#include "stack.h"


using namespace std;

bool cmp(Vertex *a, Vertex *b)
{
    return a->point.angle > b->point.angle ? true : false;
}

class GrahamSearch
{
public:
    GrahamSearch()
    {
   //     srand(time(NULL));
    }

    Vertex* findMinY(vector<Vertex*> vertices)
    {
       // double minY = (*vertices.begin())->point.y;
     //   vector<Vertex*>::iterator ptr = vertices.begin();
    /*   vector<Vertex*>::iterator ptr = vertices.front();
        for(vector<Vertex*>::iterator i=(vertices.begin()+1); i!=vertices.end(); i++)
        {
            if((*i)->point.y < (*ptr)->point.y)
            {
             //   minY = (*i)->point.y;
                ptr = i;
            }
        }

        return ptr;*/

        Vertex* ptr = vertices[0];
        for(int i=0; i<(int)vertices.size(); i++)
        {
            if(vertices[i]->point.y < ptr->point.y)
                ptr = vertices[i];

        }

        return ptr;
    }


    bool rightTurn(Point3 p1, Point3 p2, Point3 p3)
    {
       // Point3 cross = crossProduct(p3-p1, p2-p1);
        Point3 cross = crossProduct( p2-p1,p3-p1);
        return cross.z <= 0 ? true : false;
      //  return true;
    }



/*    void bubble_angle(vector<Vertex*> &v)
    {
        for(int i=0; i<v.size()-1; i++)
        {
            for(int j=0; j<v.size()-1; j++)
            {
                if(v[j+1]->point.angle < v[j]->point.angle)
                {
                    Vertex *tmp = v[j];
                    v[j] = v[j+1];
                    v[j+1] = tmp;
                }
                else if(v[j+1]->point.angle == v[j]->point.angle && v[j+1]->point.x < v[j]->point.x)
                {
                     Vertex *tmp = v[j];
                    v[j] = v[j+1];
                    v[j+1] = tmp;
                }
            }
        }
    }
    */

    Stack scan(vector<Point3> S)
    {
        seznam sz;
        Stack sklad;
     //   sklad.release();
        if(S.size()<=1) return sklad; // ce ne se sesuje, kadar ni tock

        vector<Vertex*> vertices;
        for(int i=0; i<(int)S.size(); i++)
        {
          //  vertices.push_back(new Vertex(S[i]));
            sz.vstaviVGlavo(new Vertex(S[i]));
        }
        sz.popraviIndexe();

        // vector<Vertex*>::iterator pivot = this->findMinY(vertices);
        Vertex *pivot = sz.vrniElZMinY();//this->findMinY(vertices);

        // tvorimo sistem polar. koordinat
       /* for(int i=0; i<(int)vertices.size(); i++)
            vertices[i]->point.calcPolarCoords(vertices[i]->point - pivot->point); // (*pivot)->point, ce je iterator*/
        for(element *p=sz.head; p!=NULL; p=p->next)
            p->key->point.calcPolarCoords(p->key->point - pivot->point);

        sort(vertices.begin(), vertices.end()); /// !!!!!!!!!!!!!!!!!!!!!!!!!!
     //       sort(vertices.begin(), vertices.end(), cmp); /// !!!!!!!!!!!!!!!!!!!!!!!!!!
      //  this->bubble_angle(vertices);

        sz.hitroUredi(sz.head, sz.tail);

        //////////////// ALGORITM
      /*  sklad.push(vertices[0]);
        sklad.push(vertices[1]);*/

        sklad.push(sz.head->key);
        sklad.push(sz.head->next->key);
    //    for(int i=2; i<(int)vertices.size(); i++)
        for(element *p=sz.head->next->next; p!=NULL; p=p->next)
        {
            while((sklad.size() >= 2) && (this->rightTurn(sklad.second()->point, sklad.top_el()->point, p->key->point)))
                sklad.pop();

            sklad.push(p->key);
         //   sklad.push(vertices[i]);
        }

        return sklad;
    }
};

#endif
