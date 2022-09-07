#include "../domain/CoordinateCluster.h"

class ScalingService { // TODO: rename to zoomer
public:
    float xToDomainX(float x) const;
    float yToDomainY(float y) const;

    float xToScreenX(float x) const;
    float yToScreenY(float y) const;

    void scale(float scalePercentageDelta, float xScreen, float yScreen);  //TODO: rename to zoom
    void move(float xScreenDelta, float yScreenDelta);

private:
    float xOffset{0}, yOffset{0};
    float scaleCoefficient{1};
};

