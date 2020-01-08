#include<iostream>
#include<cmath>
#include "point.h"

Point::Point():d_x(0), d_y(0){}
Point::Point(double x, double y):d_x(x), d_y(y){}

 void Point::afficherPoint(std::ostream& os){
    os << "( " << d_x << " , " << d_y << " )";
}

 void Point::lirePoint(std::istream& is){
     std::string c;

     is >> c >> d_x >> c >> d_y >> c;
 }
   double Point::distance(const Point& p)
 {
  double dx= p.d_x-d_x;
  double dy=p.d_y-d_y;
  return std::sqrt(dx*dx +dy*dy);
 }
  double Point::x(){
     return d_x;
 }
  double Point::y(){
     return d_y;
 }
 void Point::setX(double x){
     d_x = x;
 }
 void Point::setY(double y){
     d_y = y;
 }

 std::ostream& operator <<(std::ostream &os, Point p){
     p.afficherPoint(os);
     return os;
 }

 std::istream& operator >>(std::istream &is, Point &p){
     p.lirePoint(is);
     return is;
 }
/*
 int aGauche(Point a, Point b, Point c){
     int d = (b.x()-a.x())*(c.y()-a.y())-(b.y()-a.y())*(c.x()-a.x());
     return d;
 }
 */
