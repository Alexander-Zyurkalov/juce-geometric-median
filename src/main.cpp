#include "main.h"

const juce::String GeometricMedianApplication::getApplicationName() {
    return JUCE_APPLICATION_NAME_STRING;
}

const juce::String GeometricMedianApplication::getApplicationVersion() {
    return JUCE_APPLICATION_VERSION;
}

void GeometricMedianApplication::initialise(const juce::String &commandLineParameters) {

}

void GeometricMedianApplication::shutdown() {

}

START_JUCE_APPLICATION(GeometricMedianApplication)
