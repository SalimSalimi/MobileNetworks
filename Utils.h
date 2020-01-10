#include "hexagone.h"
#include <math.h>

#ifndef UTILS_H
#define UTILS_H


std::vector<Hexagone> creerLigneHexagone(Point, int);
std::vector<Hexagone> remplirPaire(Point, int);
std::vector<Hexagone> remplirImpaire(Hexagone, int);

#endif // UTILS_H
