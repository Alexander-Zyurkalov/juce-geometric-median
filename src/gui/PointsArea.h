#include "juce_gui_basics/juce_gui_basics.h"
#include "../domain/CoordinateCluster.h"

class AttentionPoint: public juce::Component{
public:
    void paint(juce::Graphics &g) override;
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
    std::vector<Coordinates> bestPoints;
    std::vector<Coordinates> oldBestPoints;
    CoordinateCluster coordinateCluster;
};


