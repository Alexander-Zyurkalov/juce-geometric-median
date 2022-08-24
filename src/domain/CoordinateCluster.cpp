#include "CoordinateCluster.h"

void CoordinateCluster::addCoordinates(float latitude, float longitude) {
    coordinateList.push_back(new Coordinates{latitude, longitude});
}

CoordinateCluster::~CoordinateCluster() {
    for (Coordinates *&coordinates: coordinateList) {
        delete coordinates;
    }
}


float Coordinates::getLatitude() const {
    return latitude;
}

void Coordinates::setLatitude(float latitude) {
    Coordinates::latitude = latitude;
}

float Coordinates::getLongitude() const {
    return longitude;
}

void Coordinates::setLongitude(float longitude) {
    Coordinates::longitude = longitude;
}

Coordinates::Coordinates(float latitude, float longitude) : latitude(latitude), longitude(longitude) {}

