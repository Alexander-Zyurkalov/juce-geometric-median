#include "CoordinateCluster.h"
#include <cmath>
#include <juce_core/juce_core.h>

static float toRadians (float degrees) noexcept {
    return (juce::MathConstants<float>::pi / 180.0f) * degrees;
}

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

std::vector<Coordinates> CoordinateCluster::calculateMiddlePointByOurAlgorithm() {
    std::vector<Coordinates> bestCoordinates;
    if (coordinateList.empty()) {
        return bestCoordinates;
    }
//    float leastTotalDistance = 0;
//    Coordinates* finalCoordinateData = coordinateList[0];
//    std::vector<Coordinates*> conflictingCoordinates;
//
//    for (int i = 0; i < coordinateList.size(); i++) {
//        Coordinates* shopSpecificCoordinatesDataA = coordinateList[i];
//        float totalDistance = 0;
//        for (int j = 0; j < coordinateList.size(); j++) {
//            if (i == j)
//                continue;
//            Coordinates* shopSpecificCoordinatesDataB = coordinateList[j];
//            totalDistance += calculateDistance(shopSpecificCoordinatesDataA, shopSpecificCoordinatesDataB);
//        }
//        if (i == 0 || totalDistance < leastTotalDistance) {
//            leastTotalDistance = totalDistance;
//            finalCoordinateData = shopSpecificCoordinatesDataA;
//            conflictingCoordinates.clear();     //if there is a lesser distance value than current then conflict is resolved.
//            conflictingCoordinates.push_back(finalCoordinateData);
//        } else if (totalDistance == leastTotalDistance) {
//            // 2 points have same total distances. resolve it later
//            if (conflictingCoordinates.empty()) {
//
//                conflictingCoordinates.push_back(finalCoordinateData);
//            }
//            conflictingCoordinates.push_back(shopSpecificCoordinatesDataA);
//        }
//    }
//    for(Coordinates* coordinates: conflictingCoordinates){
//        bestCoordinates.push_back(*coordinates);
//    }
    return bestCoordinates;
}

float CoordinateCluster::calculateDistance(const Coordinates *pointA, const Coordinates *pointB) const {
    float lat1 = pointA->getLatitude();
    float lat2 = pointB->getLatitude();
    float long1 = pointA->getLongitude();
    float long2 = pointB->getLongitude();
    int radiusOfEarth = 6371;
    int dLat = toRadians(lat2 - lat1);
    float dLon = toRadians(long2 - long1);

    float a = sin(dLat / 2) * sin(dLat / 2) +
               cos(toRadians(lat1)) * cos(toRadians(lat2)) *
               sin(dLon / 2) * sin(dLon / 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return (float) radiusOfEarth * c;
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

