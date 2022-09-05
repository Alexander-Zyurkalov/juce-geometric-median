#include "ScalingService.h"

void ScalingService::scale(float scalePercentageDelta, float xScreenDelta, float yScreenDelta) {
    scaleCoefficient += scalePercentageDelta;

}

float ScalingService::xToDomainX(float x) const {
    return (x - xOffset) * scaleCoefficient;
}

float ScalingService::yToDomainY(float y) const {
    return (y - yOffset) * scaleCoefficient;
}

float ScalingService::xToScreenX(float x) const {
    return x  / scaleCoefficient + xOffset;
}

float ScalingService::yToScreenY(float y) const {
    return y / scaleCoefficient + yOffset;
}

void ScalingService::move(float xScreenDelta, float yScreenDelta) {
    xOffset += xScreenDelta;
    yOffset += yScreenDelta;
}
