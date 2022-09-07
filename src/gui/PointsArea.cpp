#include "PointsArea.h"
#include <iostream>
#include <functional>
PointsArea::PointsArea(juce::ScrollBar& verticalScrollBar,
                       juce::ScrollBar& horizontalScrollBar): verticalScrollBar(verticalScrollBar),
                                                              horizontalScrollBar(horizontalScrollBar){
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
    coordinateCluster.addCoordinates(scalingService.xToDomainX((float)x),
                                     scalingService.yToDomainY((float)y));
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
    coordinateCluster.setCoordinates(
            point->getIndex(),
            scalingService.xToDomainX((float)bounds.getX()),
            scalingService.yToDomainY((float)bounds.getY()));
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
        int newX = (int)scalingService.xToScreenX(coordinates.getLatitude());
        int newY = (int)scalingService.yToScreenY(coordinates.getLongitude());
        attentionPoint->setBounds(
                newX - (int)(size - 10) / 2,
                newY - (int)(size - 10) / 2,
                size, size);
        if (!attentionPoint->isVisible()){
            addAndMakeVisible(attentionPoint, 0);
        }
    }
}

void PointsArea::mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) {
    if (event.mods.isCommandDown()) {
        scalingService.scale(-wheel.deltaY, event.getMouseDownX(), event.getMouseDownY());
        updateVerticalScrollBarPosition();
        updateHorizontalScrollBarPosition();
    } else {
        scalingService.move(wheel.deltaX * 2.5f, wheel.deltaY * 2);
        if (wheel.deltaX != 0.0f)
            updateHorizontalScrollBarPosition();
        if (wheel.deltaY != 0.0f)
            updateVerticalScrollBarPosition();
    }
    updatePositionOfAllPoints();
}

void PointsArea::updatePositionOfAllPoints() {
    for (MyPoint *&point: points) {
        juce::Rectangle<int> bounds = point->getBoundsInParent();
        auto coordinates = coordinateCluster.getCoordinates(point->getIndex());
        int newX = (int) scalingService.xToScreenX(coordinates.getLatitude());
        int newY = (int) scalingService.yToScreenY(coordinates.getLongitude());
        bounds.setX(newX);
        bounds.setY(newY);
        point->setBounds(bounds);
    }
    recalculateAttentionPointsPosition();
}

void PointsArea::updateVerticalScrollBarPosition() {
    auto getY = [](juce::Rectangle<int> bounds){return bounds.getY();};
    reflectMovesToAScrollBar(verticalScrollBar, getY, getHeight() - 1);
}

void PointsArea::updateHorizontalScrollBarPosition() {
    auto getX = [](juce::Rectangle<int> bounds){return bounds.getX();};
    reflectMovesToAScrollBar(horizontalScrollBar, getX, getWidth() - 1);
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

void PointsArea::reflectMovesToAScrollBar(
        juce::ScrollBar &scrollBar,
        const std::function<const int(juce::Rectangle<int>)>& getValueOfACoordinate,
        int areaSize) {

    auto compByDimension = [&getValueOfACoordinate](MyPoint* const& a, MyPoint* const& b){
        return getValueOfACoordinate(a->getBounds()) < getValueOfACoordinate(b->getBounds());
    };

    auto minAndMaxByADimension = std::minmax_element(std::begin(points), std::end(points), compByDimension);
    int getMinDimension = getValueOfACoordinate(minAndMaxByADimension.first[0]->getBounds()) - 15;
    int dimensionMin = getMinDimension > 0 ? 0 : getMinDimension;
    int getMaxDimension = getValueOfACoordinate(minAndMaxByADimension.second[0]->getBounds()) + 15;
    int dimensionMax = getMaxDimension < areaSize ? areaSize : getMaxDimension;
    scrollBar.setRangeLimits(dimensionMin, dimensionMax);
}


void PointsArea::scrollBarMoved(juce::ScrollBar *scrollBarThatHasMoved, double newRangeStart) {
    if (scrollBarThatHasMoved == &verticalScrollBar) {
        scalingService.move(0, -newRangeStart);
        updatePositionOfAllPoints();
        updateVerticalScrollBarPosition();
    }
    if (scrollBarThatHasMoved == &horizontalScrollBar) {
        scalingService.move(-newRangeStart, 0);
        updatePositionOfAllPoints();
        updateHorizontalScrollBarPosition();
    }

}
