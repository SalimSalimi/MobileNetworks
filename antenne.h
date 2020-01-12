#ifndef ANTENNE_H
#define ANTENNE_H

#include <QJsonObject>
#include "point.h"
#include <iostream>



class Antenne :public Point
{
private:
    Point d_position;
    std::string d_nom;

    double d_frequence;
    double d_puissance;
    // couleur de l'antenne
    int d_r,d_g,d_b;
public:
    Antenne();
    Antenne(double x, double y, std::string nom, double puissance, int r , int g,int b);
    Point position();
    const std::string nom();
    double puissance();
    int r();
    int g();
    int b();
    void setNom(std::string nom);
    void setPuissance(double puissance);
    void setFrequence(double frequence);
    void setPosition(Point position);
    QJsonObject writeAntenneToJSON();
    QJsonObject readAntenneFromJSON();

};

#endif // ANTENNE_H
