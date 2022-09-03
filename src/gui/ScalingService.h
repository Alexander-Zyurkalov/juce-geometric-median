#include "../domain/CoordinateCluster.h"

class ScalingService {
public:
    float xToDomainX(float x);
    float yToDomainY(float y);

    float xToScreenX(float x);
    float yToScreenY(float y);

    void scale(float scalePercentageDelta, float xScreen, float yScreen);

private:
    float xOffset{0}, yOffset{0};
    float scaleCoefficient{1};
};

