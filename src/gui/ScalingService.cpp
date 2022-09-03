#include "ScalingService.h"

void ScalingService::scale(float scalePercentageDelta, float xScreen, float yScreen) {
    xOffset += xScreen;
    yOffset += yScreen;
}

float ScalingService::xToDomainX(float x) {
    return x + xOffset;
}

float ScalingService::yToDomainY(float y) {
    return y + yOffset;
}

float ScalingService::xToScreenX(float x) {
    return 0;
}

float ScalingService::yToScreenY(float y) {
    return 0;
}
