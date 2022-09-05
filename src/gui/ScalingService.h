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

/*
 * x = (xs - oldOffset)*oldC
 * x = (xs - newOffset)*newC
 *
 * newC = x/(xs - newOffset)
 * newC = (xs - oldOffset)*oldC/(xs - newOffset)
 *
 *
 *
 * xs = x /scaleCoefficient + xOffset;
 * xs - xOffSet = x /scaleCoefficient
 * x = (xs-OldxOffset)*OldscaleCoefficient
 * x = (xs-newxOffset)*newscaleCoefficient
 * (xs-newxOffset)*newscaleCoefficient = (xs-OldxOffset)*OldscaleCoefficient
 * newscaleCoefficient = (xs-OldxOffset)*OldscaleCoefficient / (xs-newxOffset)
 */