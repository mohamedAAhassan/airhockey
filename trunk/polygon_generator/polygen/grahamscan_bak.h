#ifndef __GRAHAM_SCAN
#define __GRAHAM_SCAN

#include <ctime>
#include "Vertex.h"
#include "Point3.h"
#include "graphic.h"

#include "seznam.h"

GraphicInterface gif;
//g->init();

using namespace std;

bool cmp(Point3 a, Point3 b)
{
    return a.angle > b.angle ? true : false;
}

class GrahamSearch
{
public: // private!
    Point3 o;

public:
    GrahamSearch()
    {
        srand(time(NULL));
    }

    void calcRadialCoordSysCenter(vector<Point3> points)
    {
        Point3 randPoints[] = {points[rand()%points.size()], points[rand()%points.size()], points[rand()%points.size()]};
        double xsum=0, ysum=0;

        for(int i=0; i<3; i++)
        {
            xsum += randPoints[i].x;
            ysum += randPoints[i].y;
        }

        o.x = xsum/3;
        o.y = ysum/3;
        o.z = 0.0;
    }

   vector<Vertex*>::iterator findMinY(vector<Vertex*> vertices)
    {
        double minY = (*vertices.begin())->point.y;
        vector<Vertex*>::iterator ptr = vertices.begin();

        for(vector<Vertex*>::iterator i=vertices.begin(); i!=vertices.end(); i++)
        {
            if((*i)->point.y < minY)
            {
                minY = (*i)->point.y;
                ptr = i;
            }
        }

        return ptr;
    }


    bool rightTurn(Point3 pi, Point3 pj, Point3 pk)
    {
        cout<<"------coord info-------"<<endl;
        pi.dumpInfo();
        pj.dumpInfo();
        pk.dumpInfo();
        Point3 cross = crossProduct(pk-pi, pj-pi);

        return cross.x < 0 ? true : false;
        return true;
    }

    vector<Vertex*>::iterator desniSosed(vector<Vertex*> v, vector<Vertex*>::iterator element)
    {
        if(element+1 >v.end())
        {
            cout<<"FATAL ERROR!"<<endl;
//            return seznam.begin();
        }
        return element+1;
    }

    vector<Vertex*>::iterator leviSosed(vector<Vertex*> v, vector<Vertex*>::iterator element)
    {

        if(element-1 < v.begin())
            cout<<"FATAL ERROR!"<<endl;
        return element-1;
    }

    void bubble_angle(vector<Vertex*> &v)
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
            }
        }
    }

    void scan(vector<Point3> &S)
    {
        this->calcRadialCoordSysCenter(S); // zracunamo notranjo tocko O(center)
     //  o.x = 0; o.y = 0; o.z = 0;
        gif.drawDot(o, 0.0, 1.0, 0.0);
        o.dumpInfo();

        // tvorimo sistem polar. koordinat
        for(int i=0; i<S.size(); i++)
        {
            cout<<"O: "<<o.x<<' '<<o.y<<endl;
            Point3 tmp = this->o - S[i];
            cout<<"razlika: "<<tmp.x<<' '<<tmp.y<<endl;
            S[i].calcPolarCoords(this->o - S[i]);

      // S[i].calcPolarCoords();
        }

        for(int i=0; i<S.size(); i++)
        {
            cout<<"NEUREJENI: "<<endl;
            cout<<"angle: "<<S[i].angle<<endl;//<<' '<<' '<<"sinx: "<<sin(S[i].angle)<<" cos: "<<cos(S[i].angle)<<' '<<"DEG: "<<S[i].angle*57.295<<endl;
       //     cout<<"coords: "<<S[i].x<<' '<<S[i].y<<endl;
        //    cout<<"X/Y: "<<S[i].y/S[i].x<<endl;
        }
        cout<<endl;


        vector<Vertex*> seznam;

        // napolni seznam
       // for(vector<Point3>::iterator i = S.begin(); i!=S.end(); i++)
       for(int i=0; i<S.size(); i++)
        {

            seznam.push_back(new Vertex(S[i]));
         //   seznam.push_back(new Vertex(*i));
        }

        // uredi sistem polar. koordinat
      //  sort(seznam.begin(), seznam.end());
      bubble_angle(seznam);

        for(int i=0; i<seznam.size(); i++)
        {
                        cout<<"UREJENI: "<<endl;
            cout<<"angle: "<<seznam[i]->point.angle<<endl; //"deg: "<<seznam[i]->point.angle*57.295<<endl;
        //       cout<<"coords: "<<seznam[i]->point.x<<' '<<seznam[i]->point.y<<endl;
        }


        // poisce minimum glede na y
      //  Vertex *zacetek = this->findMinY(seznam);
        vector<Vertex*>::iterator zacetek = this->findMinY(seznam); // iterator na zacetek

        gif.drawDot((*zacetek)->point, 0.3, 0.4, 0.1);

        vector<Vertex*>::iterator pi = zacetek;
        vector<Vertex*>::iterator pj = desniSosed(seznam, pi);
        vector<Vertex*>::iterator pk = desniSosed(seznam, pj);
        //cout<<"Min found: "<<(*zacetek).point.x<<' '<<(*zacetek).point.y<<endl;


    //    zacetek->i
        while(zacetek!=pk)
        {
            if(this->rightTurn( (*pi)->point, (*pj)->point, (*pk)->point ))
            {
                vector<Vertex*>::iterator d = pj;
                pj = pi;
            //    pi --;
                pi = this->leviSosed(seznam, pi); //!!!
          //   pi = desniSosed(seznam, pi);
                // delete d
                seznam.erase(d);

            }
            else
            {
              //  gif.drawDot((*pi)->point, 0.0, 0.5, 0.5);
                pi = pj;
              //  gif.drawDot((*pj)->point, 0.5, 0.5, 0.0);
                pj = pk;
             //   gif.drawDot((*pk)->point, 0.5, 0.0, 0.5);
            //    pk = desniSosed(seznam, pj);

                pk = desniSosed(seznam, pj); // !!!
         //     pk = leviSosed(seznam, pj);
            }

            for(int i=0; i<seznam.size(); i++)
            {
                gif.drawDot(seznam[i]->point, 0.3, 0.4, 0.3);
            }

        }

        // izbris dinamicno alociranega pomnilnika :)
//        zacetek = NULL;
  //     delete zacetek;


    }
};

#endif
