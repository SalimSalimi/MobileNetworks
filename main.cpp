#include "mainwindow.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QApplication>
#include<iostream>
#include<antenne.h>
#include<point.h>
#include<hexagone.h>
using namespace  std;
void testHexagone()
{
    //Antenne b(Point(1,2),"Mulhouse",12,24);
   // Antenne* bf;
    Hexagone h;
    h.calculeSommet1().x();
    h.calculeSommet1().y();
}
/*
void  testAntenne()
{
    Antenne a();
    Antenne b(Point(1,2),"Mulhouse",12,24);
    b.setNom("Belfort");
    b.afficherAntenne(cout);




}
*/
/*
void testPoint()
{
    Point p(12,9);
    p.afficherPoint(cout);
    p.setX(10);
    p.setY(10);
    Point p2(5,5);
    p.afficherPoint(cout);
    p2.afficherPoint(cout);
    cout<< "distance"<<p.distance(p2);

}
*/

int main(int argc, char *argv[]){

    //testPoint();
    /*testHexagone();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    */
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Hexagone hexagone;
    hexagone.calculerSommets();

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
