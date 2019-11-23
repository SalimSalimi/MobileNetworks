#ifndef TERRITOIRE_H
#define TERRITOIRE_H
#include <iostream>
#include <vector>
#include "hexagone.h"
class Territoire
{
private:
    int d_longueur, d_largeur;
    std::vector <Hexagone> d_hexagones;
    std::vector <Antenne*> d_antennes;
public:
    Territoire();
    void setLongeur(int longueur);
    void setLargeur(int largeur);
    int longeur();
    int largeur();
    void ajouterHexagone(Hexagone h);
    void ajouterAntenne(Antenne *a);
    std::vector <Hexagone>& hexagones();
    std::vector <Antenne*>& antennes();
    void afficherTerritoire(std::ostream &os);

};

#endif // TERITOIRE_H
