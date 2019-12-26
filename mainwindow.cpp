#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "point.h"
#include"territoire.h"
#include <QBrush>
#include <QPushButton>
#include <QColor>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::vector<Hexagone> hexagones ;
std::vector<Hexagone> hexagonesImpaire ;
QPolygon polygonesPaires[10][10] ;
QPolygon polygonesImpaire[10][10];

//la taille du territoire sera fixee a 10:10 dont 5 lignes paires et 5 impaires
Point centresPaires[5][10] ;
Point centresImpaires[5][10] ;
boolean isCoveredPaire[5][10];
boolean isCoveredImpaire[5][10];
QColor colorPaire[5][10];
QColor colorImpaire[5][10];
std::vector<Antenne *> antennes ;

void MainWindow::RemplirPaire(){
    Hexagone hfirst;
    hexagones.push_back(hfirst);
      for (int i=1;i<10;i++) {
                                     Hexagone hexagone;
                                     hexagone.setCentre(Point(hexagones[i-1].centre().x()+50,hexagone.centre().y())) ;
                                     hexagones.push_back(hexagone);

                                      centresPaires[0][i]=hexagone.centre();

                                 }

                               }

//construction
void MainWindow::RemplirImpaire(){
    Hexagone hImpaire ;
    hImpaire.setCentre(Point(hexagones[0].calculeSommet6().x(),135));
    hexagonesImpaire.push_back(hImpaire);
    for (int i=1;i<10;i++) {
        //
        Hexagone hexagone;
        //
        hexagone.setCentre(Point(hexagonesImpaire[i-1].centre().x()+50,hexagonesImpaire[i-1].centre().y())) ;
        hexagonesImpaire.push_back(hexagone);
        centresImpaires[0][i]=hexagone.centre();
    }
}


//colorer les zones de couvertures
void zoneCouverture(int Xantenne , int Yantenne,int puissance,int r,int g,int b )
{

    if(Xantenne %2==0)
    {
        if(puissance  %2==0)
        {

              for (int c=Yantenne;c<Yantenne+puissance/2;c++)
              {
                  if(!isCoveredPaire[Xantenne /2][c])
                  {
                  colorPaire[Xantenne /2][c]=QColor(r,g,b);
                  isCoveredPaire[Xantenne /2][c]=true;
                  }
                  if(!isCoveredImpaire[Xantenne /2][c])
                  {
                  colorImpaire[Xantenne /2][c]=QColor(r,g,b);
                     isCoveredImpaire[Xantenne /2][c]=true;
                  }
              }

        }
        else
        {
     for (int c=Yantenne;c<Yantenne+(puissance-1)/2;c++)
              {
                //
         if(!isCoveredPaire[Xantenne /2][c])
                  {
                  colorPaire[Xantenne /2][c]=QColor(r,g,b);
                  isCoveredPaire[Xantenne /2][c]=true;
                  }
          if(!isCoveredImpaire[Xantenne /2][c])
                  {
                  colorImpaire[Xantenne /2][c]=QColor(r,g,b);
                     isCoveredImpaire[Xantenne /2][c]=true;
                  }
              }
 if(!isCoveredPaire[(Xantenne /2)+1][Yantenne]){
     colorPaire[(Xantenne /2)+1][Yantenne]=QColor(r,g,b);
     isCoveredPaire[(Xantenne /2)+1][Yantenne]=true;
 }

} //else
    }//X paire

    else if(Xantenne %2!=0)
    {
        if(puissance  %2==0)
        {

              for (int c=Yantenne;c<Yantenne+puissance/2;c++)
              {

                  if(!isCoveredImpaire[Xantenne /2][c])
                  {
                  colorImpaire[Xantenne /2][c]=QColor(r,g,b);
                     isCoveredImpaire[Xantenne /2][c]=true;
                  }
                  if(!isCoveredPaire[(Xantenne /2)+1][c])
                  {
                  colorPaire[(Xantenne /2)+1][c]=QColor(r,g,b);
                  isCoveredPaire[(Xantenne /2)+1][c]=true;
                  }
              }

        }
        else
        {
     for (int c=Yantenne;c<Yantenne+(puissance-1)/2;c++)
              {
         if(!isCoveredImpaire[Xantenne /2][c])
                 {
                 colorImpaire[Xantenne /2][c]=QColor(r,g,b);
                    isCoveredImpaire[Xantenne /2][c]=true;
                 }

                //
         if(!isCoveredPaire[Xantenne /2][c])
                  {
                  colorPaire[(Xantenne /2)+1][c]=QColor(r,g,b);
                  isCoveredPaire[(Xantenne /2)+1][c]=true;
                  }
     }
 if(!isCoveredImpaire[(Xantenne /2)+1][Yantenne]){
     colorImpaire[(Xantenne /2)+1][Yantenne]=QColor(r,g,b);
     isCoveredImpaire[(Xantenne /2)+1][Yantenne]=true;
 }

}
}
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    //initialement la couleur des hezagones est le white
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<10;j++)
        {
            colorPaire[i][j]=QColor(255,255,255);
            colorImpaire[i][j]=QColor(255,255,255);
        }
    }
    //au debut aucune hexagone n'est couverte
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<10;j++)
        {
            isCoveredPaire[i][j]=false;
            isCoveredImpaire[i][j]=false;
        }
    }
    QPainter painter(this);
    //Make a pen
    QPen Linepen;
    Linepen.setWidth(8);
    Linepen.setColor(Qt::black);



    //construction a la main de la premiere ligne paire des hexagones
    RemplirPaire();

//construction a la main de la premiere ligne impaire des hexagones
    RemplirImpaire();

    //initialisation du premier centre pair
    centresPaires[0][0]=hexagones[0].centre();
    //initialisation du premier centre impaire
    centresImpaires[0][0]=hexagonesImpaire[0].centre();


//placement des centres pour les lignes paires

for(int i=1;i<5;i++)
{
        for(int j=0;j<10;j++)
        {
            centresPaires[i][j]=Point(centresPaires[i-1][j].x(),centresPaires[i-1][j].y()+90);
        }

}
//placement des centres pour les lignes impaires
for(int i=1;i<5;i++)
{
        for(int j=0;j<10;j++)
        {
            centresImpaires[i][j]=Point(centresImpaires[i-1][j].x(),centresImpaires[i-1][j].y()+90);
        }

}

//pour chaque centre de la ligne paire ,on cree un polygone
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<10;j++)
            {
                Hexagone hexagone;
                hexagone.setCentre(centresPaires[i][j]);
                QPolygon poly;
                poly << QPoint(hexagone.calculeSommet1().x(),hexagone.calculeSommet1().y())
                     << QPoint(hexagone.calculeSommet2().x(),hexagone.calculeSommet2().y())
                     << QPoint(hexagone.calculeSommet3().x(),hexagone.calculeSommet3().y())
                     << QPoint(hexagone.calculeSommet4().x(),hexagone.calculeSommet4().y())
                        << QPoint(hexagone.calculeSommet5().x(),hexagone.calculeSommet5().y())
                        << QPoint(hexagone.calculeSommet6().x(),hexagone.calculeSommet6().y());
                polygonesPaires[i][j]=poly;
                //affichage des centres
               // painter.setBrush(Qt::black);


              //  painter.drawPoint(centresPaires[i][j].x(),centresPaires[i][j].y());
            }
        }


//pour chaque centre de la ligne impaire ,on cree un polygone
for(int i=0;i<5;i++)
{
    for(int j=0;j<10;j++)
    {
        Hexagone hexagone;
        hexagone.setCentre(centresImpaires[i][j]);
        QPolygon poly;
        poly << QPoint(hexagone.calculeSommet1().x(),hexagone.calculeSommet1().y())
             << QPoint(hexagone.calculeSommet2().x(),hexagone.calculeSommet2().y())
             << QPoint(hexagone.calculeSommet3().x(),hexagone.calculeSommet3().y())
             << QPoint(hexagone.calculeSommet4().x(),hexagone.calculeSommet4().y())
                << QPoint(hexagone.calculeSommet5().x(),hexagone.calculeSommet5().y())
                << QPoint(hexagone.calculeSommet6().x(),hexagone.calculeSommet6().y());
        polygonesImpaire[i][j]=poly;
        // painter.drawPoint(centresImpaires[i][j].x(),centresImpaires[i][j].y());
        //affichage des centres

    }
}



//placement des antennes
Antenne *antenne1 = new Antenne(2,0,"antenne!",5,222,16,112);
Antenne *antenne2 = new Antenne(2,5,"antenne!",16,16,222,208);
Antenne *antenne3 = new Antenne(5,5,"antenne!",3,25,230,18);
Antenne *antenne4 = new Antenne(8,0,"antenne!",5,230,82,18);
antennes.push_back(antenne1);
antennes.push_back(antenne2);
antennes.push_back(antenne3);
antennes.push_back(antenne4);

//tracage de la zone de couverture

for (int i=0;i<antennes.size();i++) {
  zoneCouverture(antennes[i]->x(),antennes[i]->y(),antennes[i]->puissance(),antennes[i]->r(),antennes[i]->g(),antennes[i]->b());
}


//dessin des hexagones des lignes paires avec les zones de couvertures

for(int i=0;i<5;i++){
    for(int j=0;j<10;j++)
    {
painter.setBrush(colorPaire[i][j]);
painter.drawPolygon(polygonesPaires[i][j]);

}
}
//dessin des hexagones des lignes impaires  avec les zones de couvertures
for(int i=0;i<5;i++){
    for(int j=0;j<10;j++)
    {
painter.setBrush(colorImpaire[i][j]);
painter.drawPolygon(polygonesImpaire[i][j]);

}
}
}
