#include "Utils.h";

std::vector<Hexagone> remplirPaire(Point firstCentre, int number){
    std::vector<Hexagone> listHexagonesPaires;

    listHexagonesPaires = creerLigneHexagone(firstCentre, number);
    return listHexagonesPaires;
}

std::vector<Hexagone> remplirImpaire(Hexagone firstHexagonePaire, int number){
    std::vector<Hexagone> listHexagonesImpaires;

    Point firstHexagoneCentre = firstHexagonePaire.centre();
    double newY = firstHexagoneCentre.y() - (firstHexagonePaire.rayon() *1.5);
    double newX = firstHexagoneCentre.x() + (firstHexagonePaire.rayon() * sqrt(3) / 2);

    firstHexagoneCentre.setX(newX);
    firstHexagoneCentre.setY(newY);

    listHexagonesImpaires = creerLigneHexagone(firstHexagoneCentre, number);

    return listHexagonesImpaires;
}

std::vector<Hexagone> creerLigneHexagone(Point firstCenter, int number){
    std::vector<Hexagone> listHexagones;
    double add = 0;
    Point centre = firstCenter;
    for (int i = 0; i < number; i++) {
        Hexagone hexagone;
        centre.setX(firstCenter.x() + add);
        hexagone.setCentre(centre);
        hexagone.calculerSommets();

        listHexagones.push_back(hexagone);
        add += hexagone.rayon() * sqrt(3);
    }

    return listHexagones;
}

