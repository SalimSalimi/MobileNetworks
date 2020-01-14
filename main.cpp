#include "Utils.cpp";

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QApplication>
#include<iostream>
#include<antenne.h>
#include<point.h>
#include<hexagone.h>
#include<middlewareclass.h>
#include <QGeoPolygon>
#include <QQmlContext>
#include <QGeoCoordinate>
#include <QQmlListProperty>
#include <QQmlComponent>
#include <QDebug>
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>

using namespace std;

void writeJSONFile(vector<Antenne>);
vector<Antenne> generateListeAntennes(vector<Hexagone>);
vector<Antenne> readJSONFile();

int main(int argc, char *argv[]){

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    MiddlewareClass *middleware = new MiddlewareClass();
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent component(&engine, url);
    QObject *object = component.create();
    middleware->m_obect = object;
    engine.rootContext()->setContextProperty("middleware", middleware);

    QGeoPolygon polygon;
    QList<QGeoCoordinate> coordinateList;
    int numberOfHexagones = 20;

    vector<Hexagone> listHexagones;
    vector<Hexagone> listHexagonesImpaires;
    vector<Hexagone> listHeaxgonesPaires;

    Antenne antenne;
    listHexagones = remplirPaire(Point(7.3384, 47.746), numberOfHexagones);
    listHexagonesImpaires = remplirImpaire(listHexagones[0], numberOfHexagones);

    for (int i = 0; i < listHexagonesImpaires.size(); i++) {
        listHexagones.push_back(listHexagonesImpaires[i]);
    }
    for(int i=1 ;i<numberOfHexagones/2;i++) {
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
    QVariantList listLongitude;
    QVariantList listLatitude;

    for (int i = 0; i < listHexagones.size(); i++) {
        std::vector<Point> sommets = listHexagones[i].sommets();
        int r = 58, g=60, b= 36;
        double opacity = 0.75;
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
                                  Q_ARG(QVariant, QVariant::fromValue(listLatitude)),
                                  Q_ARG(QVariant, QVariant::fromValue(listLongitude)),
                                  Q_ARG(QVariant, QVariant::fromValue(r)),
                                  Q_ARG(QVariant, QVariant::fromValue(g)),
                                  Q_ARG(QVariant, QVariant::fromValue(b)),
                                  Q_ARG(QVariant, QVariant::fromValue(listHexagones[i].centre().x())),
                                  Q_ARG(QVariant, QVariant::fromValue(listHexagones[i].centre().y())));

        listLongitude.clear();
        listLatitude.clear();
        coordinateList.clear();
    }

    return app.exec();
}


void writeJSONFile(vector<Antenne> listAntenne){

    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        cout << "Can't open fild";
    }

    QJsonArray array;
    for (int i = 0; i < listAntenne.size(); i++) {

        array.push_back(listAntenne[i].writeAntenneToJSON());
    }

    QJsonDocument document = QJsonDocument(array);
    QJsonDocument saveDoc(document);
    saveFile.write(saveDoc.toJson());
    cout << "Successfull" << endl;
}

vector<Antenne> generateListeAntennes(vector<Hexagone> listHexagones){
    vector<Antenne> listAntennes;
    for (int i = 0; i < listHexagones.size(); i++) {
        if (i%30 == 0) {
            Point p = Point(listHexagones[i].centre().x(),listHexagones[i].centre().y());
            int r = rand()%100;
            int g = rand()%100;
            int b = rand()%100;
            Antenne antenne(p.x(), p.y(),"shit", 400, 400, r, g, b);
            listAntennes.push_back(antenne);

        }
    }

    return listAntennes;
}

