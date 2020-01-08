#include "mainwindow.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QApplication>
#include<iostream>
#include<antenne.h>
#include<point.h>
#include<hexagone.h>
#include <QGeoPolygon>
#include <QQmlContext>
#include <QGeoCoordinate>
#include <QQmlListProperty>
#include <QQmlComponent>

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
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QGeoPolygon polygon;

    Hexagone hexagone;
    hexagone.setCentre(Point(47.746, 7.3384));
    hexagone.setRayon(0.0025);
    hexagone.calculerSommets();
    QList<QGeoCoordinate> coordinateList;
    std::vector<Point> sommets = hexagone.sommets();
    for (int i = 0; i < sommets.size(); i++){
        QGeoCoordinate coordinate;
        coordinate.setLatitude(sommets[i].x());
        coordinate.setLongitude(sommets[i].y());

        coordinateList.push_front(coordinate);

    }
    polygon.setPath(coordinateList);

    /*polygon.setPath({{47.746, 7.3383},
                     {47.74571, 7.33659},
                     {47.74452, 7.33662},
                     {47.74453, 7.33821},
                     {47.74605, 7.33718},
                     {47.74578,  7.33652}});*/

    engine.rootContext()->setContextProperty("poly", QVariant::fromValue(polygon));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
