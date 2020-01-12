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
Antenne::Antenne(double x, double y, std::string nom, double puissance, double frequence, int r,int g,int b):
    Point(x,y),
    d_nom {nom},
    d_puissance{puissance},
    d_r{r},
    d_g{g},
    d_b{b},
    d_frequence{frequence}
{}

const std::string Antenne::nom()
{return d_nom;}
double Antenne::puissance()
{return d_puissance;}
double Antenne::frequence(){
    return d_frequence;
}


int Antenne::r(){return d_r;}
int Antenne::g(){return d_g;}
int Antenne::b(){return d_b;}
void Antenne::setNom(std::string nom){d_nom=nom;}
void Antenne::setPuissance(double puissance){d_puissance=puissance;}
void Antenne::setPosition(Point position){this->d_position=position;}
void Antenne::setFrequence(double frequence){d_frequence=frequence;}

Point Antenne::position(){
    return Point(this->x(), this->y());
};

QJsonObject Antenne::writeAntenneToJSON() {

    QJsonObject json;
    json.insert("nom", QString::fromStdString(this->d_nom));
    json["puissance"] = QJsonValue(this->d_puissance);
    json["position"] = writePointToJSON();
    json["frequence"] = QJsonValue(this->d_frequence);
    json["red"] = this->d_r;
    json["blue"] = this->d_b;
    json["green"] = this->d_g;

    return json;
}

Antenne Antenne::readAntenneFromJSON(QJsonObject json) {
    Point position;
    double frequence, puissance;
    std::string nom;
    int r, g, b;
    if (json.contains("nom") && json["nom"].isString())
        nom = json["nom"].toString().toStdString();

    if (json.contains("position") && json["position"].isDouble())
        position = position.readPointFromJSON(json["position"].toObject());

    if (json.contains("frequence") && json["frequence"].isString())
        frequence = json["frequence"].toDouble();

    if (json.contains("puissance") && json["puissance"].isString())
        puissance = json["puissance"].toDouble();

    if (json.contains("red") && json["red"].isString())
        r = json["red"].toInt();

    if (json.contains("green") && json["green"].isString())
        g = json["green"].toInt();

    if (json.contains("blue") && json["blue"].isString())
        b = json["blue"].toInt();

    Antenne antenne(position.x(), position.y(), nom, puissance, frequence, r, g, b);

    return antenne;
}
