#include "antenne.h"
//un antenne  par defaut
Antenne::Antenne()
{
d_position=Point(0,0);
d_nom="antenne null";
d_puissance=0;
d_frequence=0;
}
// il reste les couleurs des Antenne  et leurs signales a gerer
Antenne::Antenne(Point position, std::string nom, double puissance, double frequence){
    d_position =position ;
    d_nom = nom;
    d_puissance = puissance;
    d_frequence = frequence;

}
 void Antenne::afficherAntenne(std::ostream& os)
 {

     os << "Antenne " << d_nom << " Position " << d_position << " Puissance " << d_puissance << " Frequence " << d_frequence << "/n" ;

}
 void Antenne::lireAntenne(std::istream & is)
 {
    std::string c;
     is >> c >> d_nom >> c >> d_position >> c >> d_puissance >> c >> d_frequence >> c ;

 }
 const Point Antenne::position()
 {return d_position;}
 const std::string Antenne::nom()
 {return d_nom;}
 const double Antenne::puissance()
 {return d_puissance;}
 const double Antenne::frequence()
 {
     return d_frequence;
 }
 void Antenne::setNom(std::string nom){d_nom=nom;}
 void Antenne::setPuissance(double puissance){d_puissance=puissance;}
 void Antenne::setPosition(Point position){d_position=position;}
 void Antenne::setFrequence(double frequence){d_frequence=frequence;}

