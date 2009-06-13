#include "Point3.h"


Point3::Point3() : x(0.0), y(0.0), z(0.0) { }

Point3::Point3(const Point3 &p) : x(p.x), y(p.y), z(p.z), angle(p.angle), r(p.r)
{
   // cout<<"this construc."<<endl;
   // this->x = p.x;
    //this->y = p.y;
    //this->z = p.z;
}

Point3::Point3(double x, double y, double z) : x(x), y(y), z(z) { }


double Point3::Length()
{
    // vector length = sqrt(x^2 + y^2 + z^2)
    return sqrt(x*x + y*y + z*z);
}


Point3 Point3::Normalize()
{
    // normalizacija - x, y in z deljeno z dolizno vektorja
    if((int)this->Length() != 0) // da ne delimo z 0
    {

        this->x /= this->Length();
        this->y /= this->Length();
        this->z /= this->Length();
    }

    return *this;
}

double Point3::operator*(Point3 &p)
{
    // skalarni je vsota(i=1 -> n) a1*b1 + a2*b2 + ... + an*bn
    return this->x*p.x + this->y*p.y + this->z*p.z;
}

Point3 Point3::operator*(double t)
{
  /*  this->x *= t;
    this->y *= t;
    this->z *= t;*/

    return Point3(this->x*t, this->y*t, this->z*t);//*this;
}

void Point3::dumpInfo()
{
    cout<<"------------------------------"<<endl;
    cout<<"x: "<<x<<" y: "<<y<<" z: "<<z<<" angle: "<<angle<<endl;
}

Point3 Point3::operator+(Point3 &p)
{
   // return Point3(this->x +
/*    this->x += p.x;
    this->y += p.y;
    this->z += p.z;

    return *this;*/
    return Point3(this->x + p.x, this->y + p.y, this->z + p.z);
}

Point3 Point3::operator-(Point3 &p)
{
 /*   this->x -= p.x;
    this->y -= p.y;
    this->z -= p.z;

    return *this;
   */
   return Point3(this->x - p.x, this->y - p.y, this->z - p.z);

}

Point3 &Point3::operator=(const Point3 &a)
{
    this->x = a.x; this->y = a.y; this->z = a.z; this->angle = a.angle; this->r = a.r;
    return *this;
}

bool Point3::operator==(const Point3 &p) const
{
    return this->x == p.x && this->y == p.y && this->z == p.z;//((this->x == p.x) && (this->y == p.y) && (this->z == p.z)) ? true : false;
}

bool  Point3::operator!=(const Point3 &a) const
{
    return this->x!=a.x || this->y!=a.y || this->z!=a.z;
}

Point3 Point3::operator^(Point3 &p)
{
    /* vektorski produkt... aXb =
        ay*bz - az*by
        az*bx - ax*bz
        ax*by - ay*bx
    */

    double tx = this->y*p.z - this->z*p.y;
    double ty = this->z*p.x - this->x*p.z;
    double tz = this->x*p.y - this->y*p.x;

    this->x = tx;
    this->y = ty;
    this->z = tz;

    return *this;
}

void Point3::calcPolarCoords()
{
    // r = sqrt(x^2 + y^2)
    this->r = sqrt(x*x + y*y);

    double tmp = atan2(y,x);//*57.295; // v kotih

    (((sin(tmp) < 0) && (cos(tmp)<0)) || ((sin(tmp) < 0) && (cos(tmp)>0))) ? this->angle = tmp*57.295 + 360 : this->angle = tmp*57.295;

    // angle = ctg(y/x)
   // this->angle = atan2(y,x);            ///  = atan(y/x); W#$Y#Y$^%^#$%^&*^(%^*&#^&^(%*#$%
}

void Point3::calcPolarCoords(const Point3 &p)
{

    // r = sqrt(x^2 + y^2)
    this->r = sqrt(p.x*p.x + p.y*p.y);

    // angle = ctg(y/x)
  //  this->angle = atan(p.y/p.x);



    double tmp = atan2(p.y,p.x);//*57.295; // v kotih
  //  (((sin(tmp) < 0) && (cos(tmp)<0)) || ((sin(tmp) < 0) && (cos(tmp)>0))) ? this->angle = tmp*57.295 + 360 : this->angle = tmp*57.295;
  this->angle = tmp*57.295;
}

////////////////////////////
// NONMEMBER
////////////////////////////
inline Point3 crossProduct(const Point3 &a, const Point3 &b)
{
    return Point3(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
        );
}


