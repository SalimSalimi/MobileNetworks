#include "antenne.h"
//un antenne  par defaut
Antenne::Antenne()
{
    d_position=Point(0,0);
    d_nom="antenne null";
    d_puissance=400;
    d_frequence=400;
}
// il reste les couleurs des Antenne  et leurs signales a gerer
Antenne::Antenne(double x, double y, std::string nom, double puissance,int r,int g,int b):
    Point(x,y),
    d_nom {nom},
    d_puissance{puissance},
    d_r{r},
    d_g{g},
    d_b{b}
{}

const std::string Antenne::nom()
{return d_nom;}
double Antenne::puissance()
{return d_puissance;}

int Antenne::r(){return d_r;}
int Antenne::g(){return d_g;}
int Antenne::b(){return d_b;}
void Antenne::setNom(std::string nom){d_nom=nom;}
void Antenne::setPuissance(double puissance){d_puissance=puissance;}
void Antenne::setPosition(Point position){this->d_position=position;}
void Antenne::setFrequence(double frequence){d_frequence=frequence;}

QJsonObject Antenne::writeAntenneToJSON() {

    QJsonObject json;
    json["nom"] = QString::fromStdString(this->d_nom);
    json["puissance"] = QJsonValue(this->d_puissance);
    json["point"] = writePointToJSON();
    json["frequence"] = QJsonValue(this->d_frequence);
    json["red"] = this->d_r;
    json["blue"] = this->d_b;
    json["green"] = this->d_g;
}

/*Antenne readAntenneFromJSON(QJsonObject json) {
    Point position;
    double frequence, puissance;
    std::string nom;
    int r, g, b;
    if (json.contains("nom") && json["nom"].isString())
        nom = json["nom"].toString();

    if (json.contains("y") && json["y"].isDouble())
        y = json["y"].toDouble();
}*/
