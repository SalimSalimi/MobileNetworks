#include<iostream>
#include<cmath>
#include "point.h"

const static double EarthRadiusKm = 6372.8;

Point::Point():d_x(0), d_y(0){}
Point::Point(double x, double y):d_x(x), d_y(y){}

double Point::distance(const Point& p) {
    double dx= p.d_x-d_x;
    double dy=p.d_y-d_y;
    return std::sqrt(dx*dx +dy*dy);

}

double Point::x(){
    return d_x;
}
double Point::y(){
    return d_y;
}
void Point::setX(double x){
    d_x = x;
}
void Point::setY(double y){
    d_y = y;
}

inline double degreeToRadian(double angle) {
    return M_PI * angle / 180.0;
}


double Point::haversineDistance(Point p1) {
    double latRad1 = degreeToRadian(this->x());
    double latRad2 = degreeToRadian(p1.x());
    double lonRad1 = degreeToRadian(this->y());
    double lonRad2 = degreeToRadian(p1.y());

    double diffLa = latRad2 - latRad1;
    double doffLo = lonRad2 - lonRad1;
    double computation = asin(sqrt(sin(diffLa / 2) * sin(diffLa / 2) + cos(latRad1) * cos(latRad2) * sin(doffLo / 2) * sin(doffLo / 2)));

    return 2 * EarthRadiusKm * computation;
}


QJsonObject Point::writePointToJSON() {
    QJsonObject json;
    json["x"] = QJsonValue(this->d_x);
    json["y"] = QJsonValue(this->d_y);
    return json;
}

Point Point::readPointFromJSON(QJsonObject json) {
    double x, y;
    if (json.contains("x") && json["x"].isDouble())
        x = json["x"].toDouble();

    if (json.contains("y") && json["y"].isDouble())
        y = json["y"].toDouble();

    return Point(x,y);
}
