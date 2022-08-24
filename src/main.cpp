#include "main.h"

const juce::String GeometricMedianApplication::getApplicationName() {
    return JUCE_APPLICATION_NAME_STRING;
}

const juce::String GeometricMedianApplication::getApplicationVersion() {
    return JUCE_APPLICATION_VERSION;
}

void GeometricMedianApplication::initialise(const juce::String &commandLineParameters) {
    geometricMedianWindow.reset(new GeometricMedianWindow(getApplicationName()));
}

void GeometricMedianApplication::shutdown() {
    geometricMedianWindow = nullptr;
}

START_JUCE_APPLICATION(GeometricMedianApplication)
