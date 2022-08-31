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
    std::vector<Coordinates> coordinateList = coordinateCluster.calculateMiddlePointByOurAlgorithm();
    if (redAttentionPoints.size() > coordinateList.size() )
        for (size_t i = redAttentionPoints.size() - 1; i > coordinateList.size() - 1; --i) {
            removeChildComponent(redAttentionPoints[i]);
            delete redAttentionPoints[i];
            redAttentionPoints.pop_back();
        }
    for (size_t i = 0; i < coordinateList.size(); ++i) {
        if (redAttentionPoints.size() <= i) {
            redAttentionPoints.push_back(new AttentionPoint);
        }
        AttentionPoint *attentionPoint = redAttentionPoints[i];
        Coordinates coordinates = coordinateList[i];
        attentionPoint->setBounds((int)coordinates.getLatitude() - 5, (int)coordinates.getLongitude() - 5, 20, 20);
        if (!attentionPoint->isVisible()){
            addAndMakeVisible(attentionPoint, 0);
        }
    }

}

void MyPoint::paint(juce::Graphics &g) {
    g.fillAll(juce::Colours::green);
}

std::size_t MyPoint::getIndex() const {
    return index;
}

MyPoint::MyPoint(std::size_t index) : index(index) {}

void AttentionPoint::paint(juce::Graphics &g) {
    g.setColour(juce::Colours::red);
    g.drawEllipse(0,0,15,15, 1.0f);
}
