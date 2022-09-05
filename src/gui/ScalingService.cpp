#include "ScalingService.h"

void ScalingService::scale(float scalePercentageDelta, float xScreen, float yScreen) {
    auto oldCoefficient =  scaleCoefficient;
    scaleCoefficient *= 1 + scalePercentageDelta;
    xOffset = xScreen * scaleCoefficient - (xScreen * oldCoefficient - xOffset) ;
    yOffset = yScreen * scaleCoefficient - (yScreen * oldCoefficient - yOffset);
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
