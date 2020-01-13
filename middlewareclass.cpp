#include "middlewareclass.h"
#include <QGeoCoordinate>

MiddlewareClass::MiddlewareClass(QObject *parent) : QObject(parent)
{

}

void MiddlewareClass::readAntennesFromFile(QString filePath)
{
    filePath.remove(0,8);
    filePath.replace("\N","/");
    QVector<Antenne> listAntennes;
    QFile loadFile(filePath);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
    }

    QByteArray saveData = loadFile.readAll();
    qWarning("reading");
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonArray array = loadDoc.array();
    for (int i; i < array.size(); i++) {
        Antenne antenne;
        antenne = antenne.readAntenneFromJSON(array.takeAt(i).toObject());
        listAntennes.push_back(antenne);

    }
    qWarning("Finish Loading");
    showAntennes(listAntennes);

}

void MiddlewareClass::setListLongitude(QVariantList listLongitude)
{
 this->m_listLongitude = listLongitude;
}


void MiddlewareClass::setListLatitude(QVariantList listLatitude)
{
    this->m_listLatitude = listLatitude;
}

QVariantList MiddlewareClass::listLatitude()
{
    return this->m_listLatitude;
}

QVariantList MiddlewareClass::listLongitude()
{
    return this->m_listLongitude;
}

void MiddlewareClass::showAntennes(QVector<Antenne> listAntenne){
    QVariantList listLatitude;
    QVariantList listLongitude;

    for (int i = 0; i < listAntenne.size(); i++) {
        QVariant latitude;
        QVariant longitude;
        QGeoCoordinate coordinate;
        coordinate.setLatitude(listAntenne[i].y());
        coordinate.setLongitude(listAntenne[i].x());

        latitude = coordinate.latitude();
        longitude = coordinate.longitude();

        listLatitude.push_back(latitude);
        listLongitude.push_back(longitude);

       // coordinateList.clear();*/
    }
    this->setListLatitude(listLatitude);
    this->setListLongitude(listLongitude);

    qDebug("hehehe %d", listLatitude.size());
    QMetaObject::invokeMethod(this->m_obect, "addAntenne");

}
