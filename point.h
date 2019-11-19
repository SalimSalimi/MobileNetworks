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
    Point(int x, int y);
     void afficherPoint(std::ostream&);
     void lirePoint(std::istream&);
     const int distance(const Point &p);
     int x();
     int y();
     void setX(int x);
     void setY(int y);
private:
    int d_x;
    int d_y;
};
// Si > 0, alors C est à gauche de la droite, si < 0 alors C est à droite, sinon il est sur la droite.
int aGauche(Point a, Point b, Point c);

#endif // POINT_H
