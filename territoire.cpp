#include "territoire.h"
#include<iostream>
#include<vector>

Territoire::Territoire()
{
    //les mettres en parammetres
//d_longueur=
//d_largeur=
}
void Territoire::setLargeur(int largeur){d_largeur=largeur;}
void Territoire::setLongeur(int longeur){d_longueur=longeur;}
int  Territoire::largeur(){return d_largeur;}
int  Territoire::longeur(){return  d_longueur;}
void Territoire::ajouterHexagone(Hexagone h){d_hexagones.push_back(h);}
void Territoire::ajouterAntenne(Antenne *a){d_antennes.push_back(a);}
std::vector <Hexagone>& Territoire::hexagones()
{

    return d_hexagones;

}

std::vector <Antenne*>& Territoire::antennes()
{

    return d_antennes;

}

void Territoire::afficherTerritoire(std::ostream &os)
{
    os<<"Largeur du Territoir"<<largeur()<<std::endl;
    os<<"longeur du Territoir"<<longeur()<<std::endl;


        //utiliser laffiche de l'antenne retourn voir sa apres cest justre une versio du test

}
