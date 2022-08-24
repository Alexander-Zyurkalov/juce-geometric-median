#include "PointsArea.h"
#include <iostream>
PointsArea::PointsArea(){
    addPoint();
    addPoint();
}

void PointsArea::addPoint() {
    juce::Random random1;
    auto newPoint = new MyPoint();
    points.push_back(newPoint);

    int x = random1.nextInt(juce::Range{10, 600-10});
    int y = random1.nextInt(juce::Range{10,600-10});
    newPoint->setBounds(x,y, 10,10);
    newPoint->addMouseListener(&pointsListener, false);
    addAndMakeVisible(newPoint);
}

void PointsArea::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::lightgrey);
}

PointsArea::~PointsArea() {
    for (MyPoint* &point: points) {
        delete point;
    }
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