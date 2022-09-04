#pragma once
#include <vector>


class Coordinates{
private:
    float latitude;
    float longitude;

public:
    Coordinates(float latitude, float longitude);

    float getLatitude() const;

    void setLatitude(float latitude);

    float getLongitude() const;

    void setLongitude(float longitude);

    bool operator==(const Coordinates &rhs) const;

    bool operator!=(const Coordinates &rhs) const;

    bool operator<(const Coordinates &rhs) const;

    bool operator>(const Coordinates &rhs) const;

    bool operator<=(const Coordinates &rhs) const;

    bool operator>=(const Coordinates &rhs) const;
};

float calculateDistance(const Coordinates *pointA, const Coordinates *pointB);

class CoordinateCluster {
public:
    void addCoordinates(float latitude, float longitude);
    void setCoordinates(std::size_t index, float latitude, float longitude);
    Coordinates getCoordinates(std::size_t index) const;

    virtual ~CoordinateCluster();

    std::vector<Coordinates> calculateMiddlePointByOurAlgorithm() const;
    std::vector<Coordinates> calculateMiddlePointByAverageMassSpread();
    std::vector<Coordinates> calculateMiddlePointByMedianMassSpread() const;
private:
    std::vector<Coordinates*> coordinateList;

    std::vector<Coordinates> findTheNearestToThePoint(Coordinates &thePoint) const;
};
