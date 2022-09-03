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
    newPoint->addMouseListener(this, false);
    addAndMakeVisible(newPoint);
    coordinateCluster.addCoordinates((float)x, (float)y); // here we can do geo transformation
    recalculateAttentionPointsPosition();
}

void PointsArea::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::black);
}

PointsArea::~PointsArea() {
    for (MyPoint* &point: points)
        delete point;
    for(auto &attentionPoint:redAttentionPoints)
        delete attentionPoint;
    for(auto &attentionPoint:greenAttentionPoints)
        delete attentionPoint;
    for(auto &attentionPoint:blueAttentionPoints)
        delete attentionPoint;
}


void PointsArea::mouseDrag(const juce::MouseEvent &event) {
    if (event.eventComponent == this) {
        return;
    }
    auto *point = (MyPoint*)event.eventComponent;
    juce::Rectangle<int> bounds = point->getBoundsInParent();
    int x = event.getPosition().getX();
    int y = event.getPosition().getY();
    int newX = bounds.getX() + x - bounds.getWidth() / 2;
    int newY = bounds.getY() + y - bounds.getHeight() / 2;
    if (newX < 0)
        newX = 0;
    if (newY < 0 )
        newY = 0;
    if (newX > point->getParentWidth() - bounds.getWidth())
        newX = point->getParentWidth() - bounds.getWidth();
    if (newY > point->getParentHeight() - bounds.getHeight())
        newY = point->getParentHeight() - bounds.getHeight();

    bounds.setX(newX);
    bounds.setY(newY);
    point->setBounds(bounds);
    coordinateCluster.setCoordinates(point->getIndex(), (float)bounds.getX(), (float)bounds.getY());

    recalculateAttentionPointsPosition();

}

void PointsArea::recalculateAttentionPointsPosition() {
    recalculateAnyAttentionPointsPosition(coordinateCluster.calculateMiddlePointByOurAlgorithm(),
                                          redAttentionPoints, juce::Colours::red, 16.0);
    recalculateAnyAttentionPointsPosition(coordinateCluster.calculateMiddlePointByAverageMassSpread(),
                                          greenAttentionPoints, juce::Colours::green, 20.0);
    recalculateAnyAttentionPointsPosition(coordinateCluster.calculateMiddlePointByMedianMassSpread(),
                                          blueAttentionPoints, juce::Colours::blue, 24.0);

}

void PointsArea::recalculateAnyAttentionPointsPosition(const std::vector<Coordinates> &coordinateList,
                                                       std::vector<AttentionPoint*> &attentionPoints,
                                                       juce::Colour pointColour, const float size) {
    if (attentionPoints.size() > coordinateList.size() )
        for (size_t i = attentionPoints.size() - 1; i > coordinateList.size() - 1; --i) {
            removeChildComponent(attentionPoints[i]);
            delete attentionPoints[i];
            attentionPoints.pop_back();
        }
    for (size_t i = 0; i < coordinateList.size(); ++i) {
        if (attentionPoints.size() <= i) {
            attentionPoints.push_back(new AttentionPoint(pointColour, size));
        }
        AttentionPoint *attentionPoint{attentionPoints[i]};
        Coordinates coordinates = coordinateList[i];
        attentionPoint->setBounds(
                (int)coordinates.getLatitude() - (int)(size-10)/2,
                (int)coordinates.getLongitude() - (int)(size-10)/2,
                size, size);
        if (!attentionPoint->isVisible()){
            addAndMakeVisible(attentionPoint, 0);
        }
    }
}

void MyPoint::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::white);
}

std::size_t MyPoint::getIndex() const {
    return index;
}

MyPoint::MyPoint(std::size_t index) : index(index) {}

void AttentionPoint::paint(juce::Graphics &g) {
    g.setColour(pointColour);
    g.drawRect(0.0,0.0,size,size, 1.0f);
}

AttentionPoint::AttentionPoint(const juce::Colour &pointColour, const float size) : pointColour(pointColour), size(size) {}
