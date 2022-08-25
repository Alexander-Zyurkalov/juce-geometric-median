#include "CoordinateCluster.h"

void CoordinateCluster::addCoordinates(float latitude, float longitude) {
    coordinateList.push_back(new Coordinates{latitude, longitude});
}

CoordinateCluster::~CoordinateCluster() {
    for (Coordinates *&coordinates: coordinateList) {
        delete coordinates;
    }
}

void CoordinateCluster::setCoordinates(std::size_t index, float latitude, float longitude) {
    if (index < coordinateList.size()) {
        coordinateList[index]->setLatitude(latitude);
        coordinateList[index]->setLongitude(longitude);
    }
}

std::vector<Coordinates> CoordinateCluster::calculateMiddlePointByOurAlgorithm() { // temporary code
    std::vector<Coordinates> bestCoordinates;
    Coordinates coordinates = *coordinateList[0];
    coordinates.setLongitude(coordinates.getLongitude() + 3);
    coordinates.setLatitude(coordinates.getLatitude() + 2);
    bestCoordinates.push_back(coordinates);
    if (coordinateList.size() > 1) {
        coordinates = *coordinateList[1];
        coordinates.setLongitude(coordinates.getLongitude() + 3);
        coordinates.setLatitude(coordinates.getLatitude() + 2);
        bestCoordinates.push_back(coordinates);
    }
    return bestCoordinates;
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

