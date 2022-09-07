#include "juce_gui_basics/juce_gui_basics.h"
#include "../domain/CoordinateCluster.h"
#include "ScalingService.h"

class AttentionPoint: public juce::Component{
public:
    explicit AttentionPoint(const juce::Colour &pointColour, const float size);

    void paint(juce::Graphics &g) override;
private:
    juce::Colour pointColour;
    float size;
};

class MyPoint: public  juce::Component{
public:
    explicit MyPoint(std::size_t index);

    void paint(juce::Graphics &g) override;

    std::size_t getIndex() const;

private:
    std::size_t index;
};

class PointsArea: public juce::Component, public juce::ScrollBar::Listener
        {
public:
    PointsArea(juce::ScrollBar& verticalScrollBar, juce::ScrollBar& horizontalScrollBar);
    ~PointsArea();
    void paint(juce::Graphics &g) override;
    void addPoint();
    void mouseDrag(const juce::MouseEvent &event) override;

    void mouseWheelMove(const juce::MouseEvent &event, const juce::MouseWheelDetails &wheel) override;
    void reflectMovesToVerticalScrollBar(const std::function<const int(juce::Rectangle<int>)>& getValueOfACoordinate);
    void reflectMovesToHorizontalScrollBar();

    void scrollBarMoved(juce::ScrollBar *scrollBarThatHasMoved, double newRangeStart) override;

private:
    std::vector<MyPoint*> points;
    CoordinateCluster coordinateCluster;
    std::vector<AttentionPoint*> redAttentionPoints;
    std::vector<AttentionPoint*> greenAttentionPoints;
    std::vector<AttentionPoint*> blueAttentionPoints;
    ScalingService scalingService;
    juce::ScrollBar &verticalScrollBar;
    juce::ScrollBar &horizontalScrollBar;


    void recalculateAttentionPointsPosition();

    void recalculateAnyAttentionPointsPosition(const std::vector<Coordinates> &coordinateList,
                                               std::vector<AttentionPoint*> &attentionPoints,
                                               juce::Colour pointColour, const float size);

    void updatePositionOfAllPoints();
};


