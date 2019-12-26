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
Antenne::Antenne(int x, int y, std::string nom, double puissance,int r,int g,int b):
  Point{x,y},
    d_nom {nom},
    d_puissance{puissance},
    d_r{r},
    d_g{g},
    d_b{b}

{}
 void Antenne::afficherAntenne(std::ostream& os)
 {

     os << "Antenne " << d_nom << " Position " << d_position << " Puissance " << d_puissance << " Frequence " << d_frequence << "/n" ;

}
 void Antenne::lireAntenne(std::istream & is)
 {
    std::string c;
     is >> c >> d_nom >> c >> d_position >> c >> d_puissance >> c >> d_frequence >> c ;

 }

 const std::string Antenne::nom()
 {return d_nom;}
  double Antenne::puissance()
 {return d_puissance;}


  int Antenne::r(){return d_r;}
  int Antenne::g(){return d_g;}
  int Antenne::b(){return d_b;}
 void Antenne::setNom(std::string nom){d_nom=nom;}
 void Antenne::setPuissance(double puissance){d_puissance=puissance;}
 void Antenne::setPosition(Point position){d_position=position;}
 void Antenne::setFrequence(double frequence){d_frequence=frequence;}

