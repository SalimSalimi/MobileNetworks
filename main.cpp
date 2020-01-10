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
#include <QDebug>

using namespace std;
/*void generateHexagones(QList<QGeoCoordinate> coordinateList){
    double add = 0;
    for (int j = 0; j < 4; j++) {
        Hexagone hexagone;
        hexagone.setCentre(Point(47.746, 7.3384 + add));
        hexagone.setRayon(0.0025);
        hexagone.calculerSommets();
        std::vector<Point> sommets = hexagone.sommets();

        for (int i = 0; i < sommets.size(); i++){
            QGeoCoordinate coordinate;
            coordinate.setLatitude(sommets[i].x());
            coordinate.setLongitude(sommets[i].y());
            coordinateList.push_back(coordinate);

        }
        add += hexagone.rayon()*2;
    }

}
*/
std::vector<Hexagone> generateHexagones(int number){
    std::vector<Hexagone> listHexagones;
    double add = 0;
    for (int i = 0; i < number; i++) {
        Hexagone hexagone;
        hexagone.setCentre(Point(47.746, 7.3384 + add));
        hexagone.setRayon(0.0025);
        hexagone.calculerSommets();

        listHexagones.push_back(hexagone);
        add += hexagone.rayon()*2;
    }

    return listHexagones;
}

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
    QList<QGeoCoordinate> coordinateList;

    vector<Hexagone> listHexagones;
    listHexagones = generateHexagones(4);
    //generateHexagones(coordinateList);
    //polygon.setPath(coordinateList);

    /*polygon.setPath({{47.746, 7.3383},
                     {47.74571, 7.33659},
                     {47.74452, 7.33662},
                     {47.74453, 7.33821},
                     {47.74605, 7.33718},
                     {47.74578,  7.33652}});*/

    /*engine.rootContext()->setContextProperty("poly", QVariant::fromValue(polygon));
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);*/
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent component(&engine,
            url);
    QObject *object = component.create();
    QVariant result;
    QVariant pointC = 47.746;
    QVariant pointA = 7.3384;
    QVariantList listLongitude;
    QVariantList listLatitude;


    for (int i = 0; i < 4 ; i++) {
        std::vector<Point> sommets = listHexagones[i].sommets();

        for (int i = 0; i < sommets.size(); i++){
            QGeoCoordinate coordinate;
            coordinate.setLatitude(sommets[i].x());
            coordinate.setLongitude(sommets[i].y());
            coordinateList.push_back(coordinate);

        }

        for(int i = 0 ; i < coordinateList.size(); i++){
            listLatitude.push_back(coordinateList[i].latitude());
            listLongitude.push_back(coordinateList[i].longitude());
        }

        QMetaObject::invokeMethod(object, "addHexagone",
                                   Q_ARG(QVariant, QVariant::fromValue(listLatitude)), Q_ARG(QVariant, QVariant::fromValue(listLongitude)));
        listLongitude.clear();
        listLatitude.clear();
        coordinateList.clear();
    }



    //QString results = result.toString();
    //cout << "QML return " << results.toStdString();

    /*for (int i=0; i < listLatitude.size() ; i++){
        QMetaObject::invokeMethod(object, "addMarker",
                                      Q_ARG(QVariant, listLatitude[i]), Q_ARG(QVariant, listLongitude[i]), Q_ARG(QVariant, listLatitude.size()));
    }*/
    return app.exec();
}
