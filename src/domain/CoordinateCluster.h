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

};

float calculateDistance(const Coordinates *pointA, const Coordinates *pointB);

class CoordinateCluster {
public:
    void addCoordinates(float latitude, float longitude);
    void setCoordinates(std::size_t index, float latitude, float longitude);

    virtual ~CoordinateCluster();

    std::vector<Coordinates> calculateMiddlePointByOurAlgorithm();
private:
    std::vector<Coordinates*> coordinateList;
};
