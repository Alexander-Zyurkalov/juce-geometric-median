#include "PointsArea.h"
#include <iostream>
PointsArea::PointsArea(){
    addPoint();
    addPoint();
}

void PointsArea::addPoint() {
    juce::Random random1;
    auto newPoint = new MyPoint(points.size());
    points.push_back(newPoint);
    int x = random1.nextInt(juce::Range{10, 580-10});
    int y = random1.nextInt(juce::Range{10,400-10});
    newPoint->setBounds(x,y, 10,10);
    newPoint->addMouseListener(&pointsListener, false);
    addAndMakeVisible(newPoint);
    coordinateCluster.addCoordinates((float)x, (float)y); // here we can do geo transformation
}

void PointsArea::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::black);
}

PointsArea::~PointsArea() {
    for (MyPoint* &point: points) {
        delete point;
    }
}


void PointsListener::mouseDrag(const juce::MouseEvent &event) {
    auto *point = (MyPoint*)event.eventComponent;
    juce::Rectangle<int> bounds = point->getBoundsInParent();
    int x = event.getPosition().getX();
    int y = event.getPosition().getY();
    bounds.setX(bounds.getX() + x - bounds.getWidth()/2);
    bounds.setY(bounds.getY() + y - bounds.getHeight()/2);
    if (bounds.getX() < 0)
        bounds.setX(0);
    if (bounds.getY() < 0 )
        bounds.setY(0);
    if (bounds.getX() > point->getParentWidth() - bounds.getWidth())
        bounds.setX(point->getParentWidth() - bounds.getWidth());
    if (bounds.getY() > point->getParentHeight() - bounds.getHeight())
        bounds.setY(point->getParentHeight() - bounds.getHeight());
    point->setBounds(bounds);
    coordinateCluster->setCoordinates(point->getIndex(), (float)bounds.getX(), (float)bounds.getY());

}

PointsListener::PointsListener(CoordinateCluster *coordinateCluster) : coordinateCluster(coordinateCluster) {}


void MyPoint::paint(juce::Graphics &g) {
    g.drawEllipse(10, 10, 10, 10,1.0f);
    g.fillAll(juce::Colours::white);
}

std::size_t MyPoint::getIndex() const {
    return index;
}

MyPoint::MyPoint(std::size_t index) : index(index) {}
