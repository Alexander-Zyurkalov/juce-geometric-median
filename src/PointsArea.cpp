#include "PointsArea.h"
#include <iostream>
PointsArea::PointsArea(){
    point.setBounds(40, 30, 10, 10);
    point.addMouseListener(&pointsListener, false);
    addAndMakeVisible(point);
}

void PointsArea::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::lightgrey);
}


void PointsListener::mouseDrag(const juce::MouseEvent &event) {
    juce::Component *point = event.eventComponent;
    juce::Rectangle<int> bounds = point->getBoundsInParent();
    int x = event.getPosition().getX();
    int y = event.getPosition().getY();
    bounds.setX(bounds.getX() + x - 1);
    bounds.setY(bounds.getY() + y - 1);
    if (bounds.getX() < 0)
        bounds.setX(0);
    if (bounds.getY() < 0 )
        bounds.setY(0);
    if (bounds.getX() > point->getParentWidth() - bounds.getWidth())
        bounds.setX(point->getParentWidth() - bounds.getWidth());
    if (bounds.getY() > point->getParentHeight() - bounds.getHeight())
        bounds.setY(point->getParentHeight() - bounds.getHeight());
    point->setBounds(bounds);
}


void MyPoint::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::green);
    g.drawEllipse(10, 10, 10, 10,1.0f);
    g.fillAll(juce::Colours::white);
}