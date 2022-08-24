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

class CoordinateCluster {
public:
    void addCoordinates(float latitude, float longitude);

    virtual ~CoordinateCluster();

private:
    std::vector<Coordinates*> coordinateList;
};
