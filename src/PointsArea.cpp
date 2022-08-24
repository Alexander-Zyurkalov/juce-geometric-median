#include "PointsArea.h"

PointsArea::PointsArea(){
    juce::Path path;
    path.addEllipse(0, 0, 10, 10);
    point.setPath(path);
    point.setBounds(40, 30, 10, 10);
    addAndMakeVisible(point);
//    addMouseListener(this, true);
}

void PointsArea::mouseMove(const juce::MouseEvent &event) {
    PointsArea::mouseMove(event);
}

void PointsArea::mouseDrag(const juce::MouseEvent &event) {
    Component::mouseDrag(event);
}

