#ifndef HEXAGONE_H
#define HEXAGONE_H
#include<vector>
#include "antenne.h"


class Hexagone
{
private:
    //Centre de Lhexagone
    Point d_centre;
    //taille de Lhexagone
    double d_rayon;
    //tableau de sommets
    std::vector <Point> d_sommets;
    //tableau d'antenne
    std::vector <Antenne*> d_antennes;
public:

    Hexagone();
    Point centre();
    double rayon();
    std::vector <Antenne*> antennes();
    std::vector<Point> sommets();
    void setCentre(Point centre);
    void setRayon(double rayon);
    void ajouterAntenne(Antenne *a);
    void supprimerAntenne(Antenne *a);

    void calculerSommets();
    Point calculeSommet1();
    Point calculeSommet2();
    Point calculeSommet3();
    Point calculeSommet4();
    Point calculeSommet5();
    Point calculeSommet6();

    void afficherSommets();

    bool contientPoint(Point p);
    double puissanceRecue(Antenne antenne);

};

#endif // HEXAGONE_H
