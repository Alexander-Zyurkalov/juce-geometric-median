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
}


void PointsArea::mouseDrag(const juce::MouseEvent &event) {
    if (event.eventComponent == this) {
        return;
    }
    auto *point = (MyPoint*)event.eventComponent;
    juce::Rectangle<int> bounds = point->getBoundsInParent();
    int x = event.getPosition().getX();
    int y = event.getPosition().getY();
    bounds.setX(bounds.getX() + x - bounds.getWidth()/2);
    bounds.setY(bounds.getY() + y - bounds.getHeight()/2);

    point->setBounds(bounds);
    coordinateCluster.setCoordinates(point->getIndex(), (float)bounds.getX(), (float)bounds.getY());

    recalculateAttentionPointsPosition();

}

void PointsArea::recalculateAttentionPointsPosition() {
    recalculateAnyAttentionPointsPosition(coordinateCluster.calculateMiddlePointByOurAlgorithm(),
                                          redAttentionPoints, juce::Colours::red);
    recalculateAnyAttentionPointsPosition(coordinateCluster.calculateMiddlePointByAverageMassSpread(),
                                          greenAttentionPoints, juce::Colours::green);

}

void PointsArea::recalculateAnyAttentionPointsPosition(const std::vector<Coordinates> &coordinateList,
                                                       std::vector<AttentionPoint*> &attentionPoints,
                                                       juce::Colour pointColour) {
    if (attentionPoints.size() > coordinateList.size() )
        for (size_t i = attentionPoints.size() - 1; i > coordinateList.size() - 1; --i) {
            removeChildComponent(attentionPoints[i]);
            delete attentionPoints[i];
            attentionPoints.pop_back();
        }
    for (size_t i = 0; i < coordinateList.size(); ++i) {
        if (attentionPoints.size() <= i) {
            attentionPoints.push_back(new AttentionPoint(pointColour));
        }
        AttentionPoint *attentionPoint{attentionPoints[i]};
        Coordinates coordinates = coordinateList[i];
        attentionPoint->setBounds(
                (int)coordinates.getLatitude() - 5,
                (int)coordinates.getLongitude() - 5,
                20, 20);
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
    g.drawEllipse(0,0,20,20, 1.0f);
}

AttentionPoint::AttentionPoint(const juce::Colour &pointColour) : pointColour(pointColour) {}
