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
// Territoire *territoire = new Territoire();
 std::vector<Hexagone> hexagones ;
 std::vector<Hexagone> hexagonesImpaire ;
   vector<QPolygon> polygonesPaires;
      vector<QPolygon> polygonesImpaire;
void MainWindow::RemplirPaire(){
Hexagone hfirst;
    hexagones.push_back(hfirst);
 for (int i=0+1;i<8;i++) {
   Hexagone hexagone;
    hexagone.setCentre(Point(hexagones[i-1].centre().x()+155,hexagone.centre().y())) ;
    hexagones.push_back(hexagone);

 }

}


void MainWindow::RemplirImpaire(){
   Hexagone hImpaire ;
   hImpaire.setCentre(Point(hexagones[0].calculeSommet6().x(),225));
    hexagonesImpaire.push_back(hImpaire);
    for (int i=1;i<8;i++) {
      Hexagone hexagone;
       hexagone.setCentre(Point(hexagonesImpaire[i-1].centre().x()+155,hexagonesImpaire[i-1].centre().y())) ;
       hexagonesImpaire.push_back(hexagone);
    }
}

void MainWindow::RemplirPolygonesPaire(){
    //remplir le tableau polygone

    for (int i=0;i<hexagones.size();i++) {
         QPolygon poly;
         poly << QPoint(hexagones[i].calculeSommet1().x(),hexagones[i].calculeSommet1().y())
              << QPoint(hexagones[i].calculeSommet2().x(),hexagones[i].calculeSommet2().y())
              << QPoint(hexagones[i].calculeSommet3().x(),hexagones[i].calculeSommet3().y())
              << QPoint(hexagones[i].calculeSommet4().x(),hexagones[1].calculeSommet4().y())
              << QPoint(hexagones[i].calculeSommet5().x(),hexagones[i].calculeSommet5().y())
              << QPoint(hexagones[i].calculeSommet6().x(),hexagones[i].calculeSommet6().y());
              polygonesPaires.push_back(poly);
    }
}
void MainWindow::RemplirPolygonesImpaire(){

    for (int i=0;i<hexagonesImpaire.size();i++) {
         QPolygon poly;
         poly << QPoint(hexagonesImpaire[i].calculeSommet1().x(),hexagonesImpaire[i].calculeSommet1().y())
              << QPoint(hexagonesImpaire[i].calculeSommet2().x(),hexagonesImpaire[i].calculeSommet2().y())
              << QPoint(hexagonesImpaire[i].calculeSommet3().x(),hexagonesImpaire[i].calculeSommet3().y())
              << QPoint(hexagonesImpaire[i].calculeSommet4().x(),hexagonesImpaire[1].calculeSommet4().y())
              << QPoint(hexagonesImpaire[i].calculeSommet5().x(),hexagonesImpaire[i].calculeSommet5().y())
              << QPoint(hexagonesImpaire[i].calculeSommet6().x(),hexagonesImpaire[i].calculeSommet6().y());
              polygonesImpaire.push_back(poly);
    }

}
void MainWindow::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);
   int numberofLine =0;
    RemplirPaire();
    RemplirPolygonesPaire();
    // dessin des polygones
     for (int p=0;p<polygonesPaires.size();p++) {
            painter.drawPolygon(polygonesPaires[p]);
     }
     numberofLine++;

    RemplirImpaire();
    RemplirPolygonesImpaire();

    // dessin des polygonesImpaires
     for (int p=0;p<polygonesImpaire.size();p++) {
            painter.drawPolygon(polygonesImpaire[p]);
     }
   numberofLine++;


   if(numberofLine % 2==0)
   {
      for (int i=0;i<hexagones.size();i++) {
        hexagones[i].sommets()[4].setY(hexagonesImpaire[i].sommets()[2].y());
           hexagones[i].setCentre(Point(hexagones[i].centre().x(),hexagonesImpaire[0].centre().y()+135));

          // hexagones[0].calculeSommet1()=hexagonesImpaire[0].calculeSommet1();

     }

    RemplirPolygonesPaire();
    // dessin des polygones
     for (int p=0;p<polygonesPaires.size();p++) {
            painter.drawPolygon(polygonesPaires[p]);
     }
   numberofLine++;
   }

   else
   {
       for (int i=0;i<hexagonesImpaire.size();i++) {
           hexagonesImpaire[i].setCentre(Point(hexagonesImpaire[i].centre().x(),hexagones[i].centre().y()+135));
           hexagonesImpaire[i].calculeSommet3()=hexagones[i].calculeSommet1();
           // hexagonesImpaire[0].calculeSommet5()=hexagones[0+1].calculeSommet1();
           // hexagonesImpaire[0].calculeSommet4()=hexagones[0].calculeSommet6();
       }

    RemplirPolygonesImpaire();
    // dessin des polygones
     for (int p=0;p<polygonesImpaire.size();p++) {
            painter.drawPolygon(polygonesImpaire[p]);

   }
   numberofLine++;

   }



    /*Hexagone hpaire2;
    hpaire2.setCentre(Point(hexagones[0].centre().x(),360));
    QPolygon poly5;
    poly5 << QPoint(hpaire2.calculeSommet1().x(),hpaire2.calculeSommet1().y())
         << QPoint(hpaire2.calculeSommet2().x(),hpaire2.calculeSommet2().y())
         << QPoint(hpaire2.calculeSommet3().x(),hpaire2.calculeSommet3().y())
         << QPoint(hpaire2.calculeSommet4().x(),hpaire2.calculeSommet4().y())
         << QPoint(hpaire2.calculeSommet5().x(),hpaire2.calculeSommet5().y())
         << QPoint(hpaire2.calculeSommet6().x(),hpaire2.calculeSommet6().y());*/








    //remplir le tableau polygone





//painter.drawPolygon(poly5);



      //Make a pen
      QPen Linepen;
      Linepen.setWidth(1);
      Linepen.setColor(Qt::red);

      painter.setPen(Linepen);

}

