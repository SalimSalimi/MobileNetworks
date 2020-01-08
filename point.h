#ifndef POINT_H
#define POINT_H

#include<ostream>
#include<istream>

class Point
{
    //pourquoi mettre les operateurs d'entree sortie en freind?
    friend std::ostream& operator <<(std::ostream &os, Point p);
    friend std::istream& operator >>(std::istream &os, Point &p);
public:
    Point();
    Point(double x, double y);
     void afficherPoint(std::ostream&);
     void lirePoint(std::istream&);
     double distance(const Point &p);
     double x();
     double y();
     void setX(double x);
     void setY(double y);
private:
    double d_x;
    double d_y;
};
/* Si > 0, alors C est à gauche de la droite, si < 0 alors C est à droite, sinon il est sur la droite.
int aGauche(Point a, Point b, Point c);

*/

#endif // POINT_H
