#ifndef MIDDLEWARECLASS_H
#define MIDDLEWARECLASS_H

#include <QObject>
#include <QDebug>
#include <antenne.h>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVariantList>
#include <QColor>

class MiddlewareClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList listLongitude READ listLongitude WRITE setListLongitude)
    Q_PROPERTY(QVariantList listLatitude READ listLatitude WRITE setListLatitude)
    Q_PROPERTY(QVariantList listFrequence READ listFrequence WRITE setListFrequence)
    Q_PROPERTY(QVariantList listPuissance READ listPuissance WRITE setListPuissance)
    Q_PROPERTY(QVariantList listColor READ listColor WRITE setListColor)

public:
    explicit MiddlewareClass(QObject *parent = nullptr);

    QObject* m_obect;

    Q_INVOKABLE void saveAntennesToFile(QString filePath);
    Q_INVOKABLE void readAntennesFromFile(QString filePath);
    Q_INVOKABLE void constructListAntennes(QVariant puissance, QVariant frequence,
                                        QVariant coordinateLatitude, QVariant coordinateLongitude,
                                        QVariant couleur, QVariant nom);


    void setListLongitude(QVariantList listLongitude);
    void setListLatitude(QVariantList listLatitude);
    void setListFrequence(QVariantList listFrequence);
    void setListPuissance(QVariantList listPuissance);
    void setListColor(QVariantList listColor);

    QVariantList listLatitude();
    QVariantList listLongitude();
    QVariantList listFrequence();
    QVariantList listPuissance();
    QVariantList listColor();


    void showAntennes(QVector<Antenne> listAntenne);
signals:

private:
    QVariantList m_listLongitude;
    QVariantList m_listLatitude;
    QVector<Antenne> m_listAntenne;
    QVariantList m_listFrequence;
    QVariantList m_listPuissance;
    QVariantList m_listColor;
};

#endif // MIDDLEWARECLASS_H
