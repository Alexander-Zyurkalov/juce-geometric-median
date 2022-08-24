#include "juce_gui_basics/juce_gui_basics.h"
#include "../domain/CoordinateCluster.h"

class PointsListener: public juce::MouseListener{
public:
    void mouseDrag(const juce::MouseEvent &event) override;

    explicit PointsListener(CoordinateCluster *coordinateCluster);

private:
    CoordinateCluster* coordinateCluster;
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
private:
    std::vector<MyPoint*> points;
    CoordinateCluster coordinateCluster;
    PointsListener pointsListener{&coordinateCluster};
};


