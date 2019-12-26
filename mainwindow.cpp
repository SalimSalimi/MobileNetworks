#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "point.h"
#include"territoire.h"

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
vector<QPolygon> polygonesPaires;
vector<QPolygon> polygonesImpaire;

//la taille du territoire sera fixee a 10:10 dont 5 lignes paires et 5 impaires
Point centresPaires[5][10] ;
Point centresImpaires[5][10] ;



void MainWindow::RemplirPaire(){
    Hexagone hfirst;
    hexagones.push_back(hfirst);
      for (int i=1;i<10;i++) {
                                     Hexagone hexagone;
                                     hexagone.setCentre(Point(hexagones[i-1].centre().x()+155,hexagone.centre().y())) ;
                                     hexagones.push_back(hexagone);

                                     QPolygon poly;
                                     poly << QPoint(hexagone.calculeSommet1().x(),hexagone.calculeSommet1().y())
                                          << QPoint(hexagone.calculeSommet2().x(),hexagone.calculeSommet2().y())
                                          << QPoint(hexagone.calculeSommet3().x(),hexagone.calculeSommet3().y())
                                          << QPoint(hexagone.calculeSommet4().x(),hexagone.calculeSommet4().y())
                                             << QPoint(hexagone.calculeSommet5().x(),hexagone.calculeSommet5().y())
                                             << QPoint(hexagone.calculeSommet6().x(),hexagone.calculeSommet6().y());
                                     polygonesPaires.push_back(poly);
                                      centresPaires[0][i]=hexagone.centre();

                                 }

                               }


void MainWindow::RemplirImpaire(){
    Hexagone hImpaire ;
    hImpaire.setCentre(Point(hexagones[0].calculeSommet6().x(),225));
    hexagonesImpaire.push_back(hImpaire);
    for (int i=1;i<10;i++) {
        //
        Hexagone hexagone;
        //
        hexagone.setCentre(Point(hexagonesImpaire[i-1].centre().x()+155,hexagonesImpaire[i-1].centre().y())) ;
        hexagonesImpaire.push_back(hexagone);
        //
        QPolygon poly;
        poly << QPoint(hexagone.calculeSommet1().x(),hexagone.calculeSommet1().y())
             << QPoint(hexagone.calculeSommet2().x(),hexagone.calculeSommet2().y())
             << QPoint(hexagone.calculeSommet3().x(),hexagone.calculeSommet3().y())
             << QPoint(hexagone.calculeSommet4().x(),hexagone.calculeSommet4().y())
                << QPoint(hexagone.calculeSommet5().x(),hexagone.calculeSommet5().y())
                << QPoint(hexagone.calculeSommet6().x(),hexagone.calculeSommet6().y());
        polygonesImpaire.push_back(poly);
        centresImpaires[0][i]=hexagone.centre();
    }
}



void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    //Make a pen
    QPen Linepen;
    Linepen.setWidth(5);
    Linepen.setColor(Qt::black);

    painter.setPen(Linepen);

    //construction a la main de la premiere ligne paire
    RemplirPaire();

//construction a la main de la premiere ligne impaire
    RemplirImpaire();

    centresPaires[0][0]=hexagones[0].centre();
    centresImpaires[0][0]=hexagonesImpaire[0].centre();


//placement des centres pour les lignes paires
for(int i=1;i<5;i++)
{
        for(int j=0;j<10;j++)
        {
            centresPaires[i][j]=Point(centresPaires[i-1][j].x(),centresPaires[i-1][j].y()+270);
        }

}
//placement des centres pour les lignes impaires
for(int i=1;i<5;i++)
{
        for(int j=0;j<10;j++)
        {
            centresImpaires[i][j]=Point(centresImpaires[i-1][j].x(),centresImpaires[i-1][j].y()+270);
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
                polygonesPaires.push_back(poly);
                //affichage des centres
                painter.drawPoint(centresPaires[i][j].x(),centresPaires[i][j].y());
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
        polygonesImpaire.push_back(poly);
        //affichage des centres
        painter.drawPoint(centresImpaires[i][j].x(),centresImpaires[i][j].y());
    }
}


// dessin de tt les polygones paires
for (int p=0;p<polygonesPaires.size();p++) {
painter.drawPolygon(polygonesPaires[p]);

}

// dessin de tt les polygonesImpaires
for (int p=0;p<polygonesImpaire.size();p++) {
 painter.drawPolygon(polygonesImpaire[p]);
}

}
