#include "ScalingService.h"

void ScalingService::scale(float scalePercentageDelta, float xScreen, float yScreen) {
    float oldX = xToDomainX(xScreen);
    float oldY = yToDomainY(yScreen);
    scaleCoefficient += scalePercentageDelta;
    float newX = xToDomainX(xScreen);
    float newY = yToDomainY(yScreen);
//    xOffset += newX - oldX;
//    yOffset += newY - oldY;
}

float ScalingService::xToDomainX(float x) const {
    return x * scaleCoefficient - xOffset;
}

float ScalingService::yToDomainY(float y) const {
    return y * scaleCoefficient - yOffset;
}

float ScalingService::xToScreenX(float x) const {
    return (x  + xOffset) / scaleCoefficient ;
}

float ScalingService::yToScreenY(float y) const {
    return (y + yOffset) / scaleCoefficient ;
}

void ScalingService::move(float xScreenDelta, float yScreenDelta) {
    xOffset += xScreenDelta;
    yOffset += yScreenDelta;
}
