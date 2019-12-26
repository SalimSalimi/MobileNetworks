#ifndef ANTENNE_H
#define ANTENNE_H

#include "point.h"
#include <iostream>



class Antenne :public Point
{
    friend std::ostream& operator <<(std::ostream &os, Antenne a);
    friend std::istream& operator >>(std::istream &os, Antenne &a);
private:
    Point d_position;
    std::string d_nom;

    double d_frequence;
      double d_puissance;
    // couleur de l'antenne
    int d_r,d_g,d_b;
public:
    Antenne();
    Antenne(int x, int y, std::string nom, double puissance, int r , int g,int b);
    void afficherAntenne(std::ostream&);
    void lireAntenne(std::istream&);

    const std::string nom();
     double puissance();
     int r();
     int g();
     int b();
    void setNom(std::string nom);
    void setPuissance(double puissance);
    void setFrequence(double frequence);
    void setPosition(Point position);


};

#endif // ANTENNE_H
