#include "CoordinateCluster.h"
#include <cmath>

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

std::vector<Coordinates> CoordinateCluster::calculateMiddlePointByOurAlgorithm() const {
    std::vector<Coordinates> bestCoordinates;
    if (coordinateList.empty()) {
        return bestCoordinates;
    }
    float leastTotalDistance = 0;
    Coordinates* finalCoordinateData = coordinateList[0];
    std::vector<Coordinates*> conflictingCoordinates;

    for (int i = 0; i < coordinateList.size(); i++) {
        Coordinates* shopSpecificCoordinatesDataA = coordinateList[i];
        float totalDistance = 0;
        for (int j = 0; j < coordinateList.size(); j++) {
            if (i == j)
                continue;
            Coordinates* shopSpecificCoordinatesDataB = coordinateList[j];
            totalDistance += calculateDistance(shopSpecificCoordinatesDataA, shopSpecificCoordinatesDataB);
        }
        if (i == 0 || totalDistance < leastTotalDistance) {
            leastTotalDistance = totalDistance;
            finalCoordinateData = shopSpecificCoordinatesDataA;
            conflictingCoordinates.clear();     //if there is a lesser distance value than current then conflict is resolved.
            conflictingCoordinates.push_back(finalCoordinateData);
        } else if (totalDistance == leastTotalDistance) {
            // 2 points have same total distances. resolve it later
            if (conflictingCoordinates.empty()) {

                conflictingCoordinates.push_back(finalCoordinateData);
            }
            conflictingCoordinates.push_back(shopSpecificCoordinatesDataA);
        }
    }
    for(Coordinates* coordinates: conflictingCoordinates){
        bestCoordinates.push_back(*coordinates);
    }
    return bestCoordinates;
}

std::vector<Coordinates> CoordinateCluster::calculateMiddlePointByAverageMassSpread() const {
    return calculateMiddlePointByOurAlgorithm();
}


float calculateDistance(const Coordinates *pointA, const Coordinates *pointB)  {
    float lat1 = pointA->getLatitude();
    float lat2 = pointB->getLatitude();
    float long1 = pointA->getLongitude();
    float long2 = pointB->getLongitude();
    float a = lat1 - lat2;
    float b = long1 - long2;
    float c = sqrt(a * a + b * b);
    return c;
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

