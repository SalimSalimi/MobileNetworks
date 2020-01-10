#include "Utils.cpp";

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

int main(int argc, char *argv[]){

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent component(&engine, url);
    QObject *object = component.create();

    QGeoPolygon polygon;
    QList<QGeoCoordinate> coordinateList;
    int numberOfHexagones = 6;

    vector<Hexagone> listHexagones;
    vector<Hexagone> listHexagonesImpaires;
    vector<Hexagone> listHeaxgonesPaires;

    listHexagones = remplirPaire(Point(7.3384, 47.746), numberOfHexagones);
    listHexagonesImpaires = remplirImpaire(listHexagones[0], numberOfHexagones);

    for (int i = 0; i < listHexagonesImpaires.size(); i++) {
        listHexagones.push_back(listHexagonesImpaires[i]);
    }
    for(int i=1 ;i<numberOfHexagones/2;i++)
    {
        Point firstPointPaire ;

        firstPointPaire.setX(listHexagones[0].centre().x());
        firstPointPaire.setY(listHexagones[0].centre().y()-(3*i*listHexagones[0].rayon()));
        remplirPaire(firstPointPaire, numberOfHexagones);
         remplirImpaire(remplirPaire(firstPointPaire, numberOfHexagones)[0], numberOfHexagones);
         for (int i = 0; i < remplirPaire(firstPointPaire, numberOfHexagones).size(); i++) {
             listHexagones.push_back(remplirPaire(firstPointPaire, numberOfHexagones)[i]);
              listHexagones.push_back(remplirImpaire(remplirPaire(firstPointPaire, numberOfHexagones)[0], numberOfHexagones)[i]);
         }



    }
    /*for (int i = 0; i < 5; i++) {
        listHexagones = remplirPaire(listHexagones[i])
    }*/
    cout << "Taille" <<listHexagones.size() << endl;
    QVariantList listLongitude;
    QVariantList listLatitude;

    for (int i = 0; i < listHexagones.size(); i++) {
        std::vector<Point> sommets = listHexagones[i].sommets();

        for (int i = 0; i < sommets.size(); i++){
            QGeoCoordinate coordinate;
            coordinate.setLatitude(sommets[i].y());
            coordinate.setLongitude(sommets[i].x());
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

    return app.exec();
}
