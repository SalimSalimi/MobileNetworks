#ifndef MIDDLEWARECLASS_H
#define MIDDLEWARECLASS_H

#include <QObject>
#include <QDebug>
#include <antenne.h>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>

class MiddlewareClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList listLongitude READ listLongitude WRITE setListLongitude)
    Q_PROPERTY(QVariantList listLatitude READ listLatitude WRITE setListLatitude)

public:
    explicit MiddlewareClass(QObject *parent = nullptr);

    QObject* m_obect;
    Q_INVOKABLE void readAntennesFromFile(QString filePath);

    void setListLongitude(QVariantList listLongitude);
    void setListLatitude(QVariantList listLatitude);


    QVariantList listLatitude();
    QVariantList listLongitude();

    void showAntennes(QVector<Antenne> listAntenne);
signals:

private:
    QVariantList m_listLongitude;
    QVariantList m_listLatitude;

};

#endif // MIDDLEWARECLASS_H
