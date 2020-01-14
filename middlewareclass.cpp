#include "middlewareclass.h"
#include <QGeoCoordinate>

MiddlewareClass::MiddlewareClass(QObject *parent) : QObject(parent) {

}

void MiddlewareClass::readAntennesFromFile(QString filePath) {
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
    this->m_listAntenne = listAntennes;
}

void MiddlewareClass::setListLongitude(QVariantList listLongitude)
{
 this->m_listLongitude = listLongitude;
}


void MiddlewareClass::setListLatitude(QVariantList listLatitude)
{
    this->m_listLatitude = listLatitude;
}

void MiddlewareClass::setListFrequence(QVariantList listFrequence)
{
    this->m_listFrequence = listFrequence;
}

void MiddlewareClass::setListPuissance(QVariantList listPuissance)
{
    this->m_listPuissance = listPuissance;
}

void MiddlewareClass::setListColor(QVariantList listColor)
{
    this->m_listColor = listColor;
}

QVariantList MiddlewareClass::listLatitude()
{
    return this->m_listLatitude;
}

QVariantList MiddlewareClass::listLongitude()
{
    return this->m_listLongitude;
}

QVariantList MiddlewareClass::listFrequence()
{
    return this->m_listFrequence;
}

QVariantList MiddlewareClass::listPuissance()
{
    return this->m_listPuissance;
}

QVariantList MiddlewareClass::listColor()
{
    return this->m_listColor;
}

void MiddlewareClass::showAntennes(QVector<Antenne> listAntenne){
    QVariantList listLatitude;
    QVariantList listLongitude;
    QVariantList listPuissance;
    QVariantList listFrequence;
    QVariantList listColor;
    std::cout << "listAntenne " << listAntenne.size() << std::endl;
    for (int i = 0; i < listAntenne.size(); i++) {
        QVariant latitude;
        QVariant longitude;
        QGeoCoordinate coordinate;

        QColor color;
        coordinate.setLatitude(listAntenne[i].y());
        coordinate.setLongitude(listAntenne[i].x());

        latitude = coordinate.latitude();
        longitude = coordinate.longitude();

        color.setRed(listAntenne[i].r());
        color.setBlue(listAntenne[i].b());
        color.setGreen(listAntenne[i].g());

        listLatitude.push_back(latitude);
        listLongitude.push_back(longitude);
        listFrequence.push_back(listAntenne[i].frequence());
        listPuissance.push_back(listAntenne[i].puissance());
        listColor.push_back(color);
       // coordinateList.clear();*/
    }
    this->setListLatitude(listLatitude);
    this->setListLongitude(listLongitude);
    this->setListPuissance(listPuissance);
    this->setListFrequence(listFrequence);
    this->setListColor(listColor);

    qDebug("hehehe %d", listLatitude.size());
    QMetaObject::invokeMethod(this->m_obect, "addAntenne");

}
