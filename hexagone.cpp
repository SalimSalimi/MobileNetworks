#include "hexagone.h"
#include <cmath>
const double PI = 3.14159265358979323846;


Hexagone::Hexagone()
{
    d_centre = Point(90,90);
    d_rayon = 30;
    calculerSommets();
}

Point Hexagone::centre(){return d_centre;}
double Hexagone::rayon(){return d_rayon;}
std::vector<Antenne*> Hexagone::antennes()
{
 return d_antennes;
}

std::vector<Point> Hexagone::sommets(){
    return d_sommets;
}
void Hexagone::setCentre(Point centre){d_centre=centre;}
void Hexagone::setRayon(double rayon){d_rayon=rayon;}
void Hexagone::ajouterAntenne(Antenne *a){d_antennes.push_back(a);}
void Hexagone::supprimerAntenne(Antenne *a)
{
    for(int i=0;i<d_antennes.size();i++)

    {
        if(d_antennes.at(i)==a)
            d_antennes.erase(d_antennes.begin() + i);

    }
}
Point Hexagone::calculeSommet1()
{
    Point A(d_rayon*cos(PI/2)+d_centre.x(), d_rayon*sin(PI/2)+d_centre.y());
    return A;
}
Point Hexagone::calculeSommet2(){
    Point B(d_rayon*cos((5*PI)/6)+d_centre.x(), d_rayon*sin((5*PI)/6)+d_centre.y());
    return B;
 }
Point Hexagone::calculeSommet3()
{
    Point C(d_rayon*cos((-5*PI)/6)+d_centre.x(), d_rayon*sin((-5*PI)/6)+d_centre.y());
    return C;

}

Point Hexagone::calculeSommet4()
{
    Point D(d_rayon*cos(-PI/2)+d_centre.x(), d_rayon*sin(-PI/2)+d_centre.y());
    return D;

}

Point Hexagone::calculeSommet5()
{
    Point E(d_rayon*cos(-PI/6)+d_centre.x(), d_rayon*sin(-PI/6)+d_centre.y());
    return E;

}

Point Hexagone::calculeSommet6()

{

    Point F(d_rayon*cos(PI/6)+d_centre.x(), d_rayon*sin(PI/6)+d_centre.y());
    return F;

}
void Hexagone::calculerSommets()
{
    Point A = calculeSommet1();
    Point B = calculeSommet2();
    Point C = calculeSommet3();
    Point D = calculeSommet4();
    Point E = calculeSommet5();
    Point F = calculeSommet6();
    d_sommets.resize(0);
    d_sommets.push_back(C);
    d_sommets.push_back(D);
    d_sommets.push_back(E);
    d_sommets.push_back(F);
    d_sommets.push_back(A);
    d_sommets.push_back(B);
}

void Hexagone::afficherSommets()
{

    for (int i = 0; i < sommets().size(); i++){
        std::cout << sommets().at(i) << " | ";
    }

}


