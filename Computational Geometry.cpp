/*
TLsLib - version WIP 0.1
Computational Geometry Collection
WARNING : This Header file used namespace std.
*/
#include <cmath>
#include <vector>
using namespace std;

const double eps=1e-8;
#define inl inline

inl int fcmp(double a) {return (fabs(a)<=eps) ? 0 : (a<0 ? -1 : 1);}
//template<class FloatType> inl int fcmp(FloatType a) {return (fabs(a)<=eps) ? 0 : (a<0 ? -1 : 1);}

struct Point {
	double x,y;
	inl Point() {x=y=0;}
	inl Point(double X,double Y) {x=X,y=Y;}
};
typedef Point Vector;

// arithmetic operators
inl bool operator ==(Point a,Point b) {return (fcmp(a.x-b.x)==0)&&(fcmp(a.y-b.y)==0);}
inl Vector operator +(Vector a,Vector b) {return Vector(a.x+b.x,a.y+b.y);}
inl Vector operator -(Point a,Point b) {return Vector(a.x-b.x,a.y-b.y);}
inl Vector operator *(Vector a,double b) {return Vector(a.x*b,a.y*b);}
inl Vector operator /(Vector a,double b) {return Vector(a.x/b,a.y/b);}
inl double operator &(Vector a,Vector b) {return a.x*b.x+a.y*b.y;}
inl double operator ^(Vector a,Vector b) {return a.x*b.y-a.y*b.x;}

inl double Length(Vector a) {return sqrt(a&a);}
inl double Angle(Vector a,Vector b) {return acos((a&b)/Length(a)/Length(b));}
inl Vector Rotate(Vector a,double rad) {return Vector(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));}

// points and lines

// condition: p^q != 0
inl Point LineIntersection(Point x,Vector p,Point y,Vector q) {
	Vector t=x-y;
	return x+p*((q^t)/(p^q));
}

inl double DistanceToLine(Point p,Point a,Point b) {
	Vector v=b-a;
	return fabs(v^(p-a))/Length(v);
}
