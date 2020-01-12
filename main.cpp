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
#include <QJsonDocument>
#include <QFile>

using namespace std;

void writeJSONFile(QVariantList);
vector<Antenne> generateListeAntennes(vector<Hexagone>);

int main(int argc, char *argv[]){

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QQmlComponent component(&engine, url);
    QObject *object = component.create();

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

    vector<Antenne> listAntenne;
    listAntenne = generateListeAntennes(listHexagones);

    for (int i = 0; i < listAntenne.size(); i++) {
        QVariant latitude;
        QVariant longitude;
        QGeoCoordinate coordinate;
        coordinate.setLatitude(listAntenne[i].y());
        coordinate.setLongitude(listAntenne[i].x());

        latitude = coordinate.latitude();
        longitude = coordinate.longitude();

        QMetaObject::invokeMethod(object, "addAntenne",
                                  Q_ARG(QVariant, QVariant::fromValue(latitude)), Q_ARG(QVariant, QVariant::fromValue(longitude)));

        //writeJSONFile(listLatitude);
        listLongitude.clear();
        listLatitude.clear();
        coordinateList.clear();
    }

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

        for (int var = 0; var < listAntenne.size(); ++var) {

            if (i > 0) {

                double puissanceRecue = listHexagones[0].puissanceRecue(listAntenne[var]) * 100;
                int puissance = puissanceRecue;

                if (puissance >= 100) {
                    opacity = 0.75;
                } else if (puissance < 100 && puissance >= 50) {
                    opacity = 0.65;
                }else if (puissance < 50 && puissance >= 20) {

                    opacity = 0.55;
                } else if (puissance < 20 && puissance >=0) {
                    opacity = 0.1;
                }


                cout << "opacity c++" << opacity << endl;
                cout << "puissance c++" << puissance<< endl;

            }

            if (listHexagones[i].centre().x() == listAntenne[var].x() && listHexagones[i].centre().y() == listAntenne[var].y()) {
                r = 88;
                b = 20;
                g = 32;
            }
        }
        QVariant qOpacity = opacity;
        QMetaObject::invokeMethod(object, "addHexagone",
                                  Q_ARG(QVariant, QVariant::fromValue(listLatitude)),
                                  Q_ARG(QVariant, QVariant::fromValue(listLongitude)),
                                  Q_ARG(QVariant, QVariant::fromValue(r)),
                                  Q_ARG(QVariant, QVariant::fromValue(g)),
                                  Q_ARG(QVariant, QVariant::fromValue(b)),
                                  Q_ARG(QVariant, QVariant::fromValue(qOpacity)));

        //writeJSONFile(listLatitude);
        listLongitude.clear();
        listLatitude.clear();
        coordinateList.clear();
    }

    return app.exec();
}


/*void writeJSONFile(QVariantList data){
    QFile saveFile(QStringLiteral("save.json"));

        if (!saveFile.open(QIODevice::WriteOnly)) {
            cout << "Can't opend fild";
        }
        QJsonDocument document = QJsonDocument::fromVariant(data);
        QJsonDocument saveDoc(document);
        saveFile.write(saveDoc.toJson());
        cout << "Successfull" << endl;
}

void readJSONFile() {

}*/
vector<Antenne> generateListeAntennes(vector<Hexagone> listHexagones){
    vector<Antenne> listAntennes;
    for (int i = 0; i < listHexagones.size(); i++) {
        if (i%30 == 0) {
            Point p = Point(listHexagones[i].centre().x(),listHexagones[i].centre().y());
            Antenne antenne(p.x(), p.y(),"shit", 400, 50, 86,38);
            listAntennes.push_back(antenne);

        }
    }

    return listAntennes;
}

