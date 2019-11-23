#ifndef ANTENNE_H
#define ANTENNE_H

#include "point.h"
#include <iostream>



class Antenne
{
    friend std::ostream& operator <<(std::ostream &os, Antenne a);
    friend std::istream& operator >>(std::istream &os, Antenne &a);
private:
    Point d_position;
    std::string d_nom;
    double d_puissance;
    double d_frequence;
    // rest couleur de l'antenne a gerer
public:
    Antenne();
    Antenne(Point position, std::string nom, double puissance, double frequence);
    void afficherAntenne(std::ostream&);
    void lireAntenne(std::istream&);
    const Point position();
    const std::string nom();
    const double puissance();
    const double frequence();
    void setNom(std::string nom);
    void setPuissance(double puissance);
    void setFrequence(double frequence);
    void setPosition(Point position);

};

#endif // ANTENNE_H
