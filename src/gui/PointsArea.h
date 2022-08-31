#include "juce_gui_basics/juce_gui_basics.h"
#include "../domain/CoordinateCluster.h"

class AttentionPoint: public juce::Component{
public:
    explicit AttentionPoint(const juce::Colour &pointColour);

    void paint(juce::Graphics &g) override;
private:
    juce::Colour pointColour;
};

class MyPoint: public  juce::Component{
public:
    explicit MyPoint(std::size_t index);

    void paint(juce::Graphics &g) override;

    std::size_t getIndex() const;

private:
    std::size_t index;
};

class PointsArea: public juce::Component{
public:
    PointsArea();
    ~PointsArea();
    void paint(juce::Graphics &g) override;
    void addPoint();
    void mouseDrag(const juce::MouseEvent &event) override;
private:
    std::vector<MyPoint*> points;
    CoordinateCluster coordinateCluster;
    std::vector<AttentionPoint*> redAttentionPoints;
    std::vector<AttentionPoint*> greenAttentionPoints;

    void recalculateAttentionPointsPosition();

    void recalculateAnyAttentionPointsPosition(const std::vector<Coordinates> &coordinateList,
                                               std::vector<AttentionPoint*> &attentionPoints,
                                               juce::Colour pointColour);
};


