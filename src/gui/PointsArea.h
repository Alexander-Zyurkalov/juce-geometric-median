#include "juce_gui_basics/juce_gui_basics.h"
#include "../domain/CoordinateCluster.h"

class AttentionPoint: public juce::Component{
public:
    void paint(juce::Graphics &g) override;
};

class PointsListener: public juce::MouseListener{
public:
    void mouseDrag(const juce::MouseEvent &event) override;

    PointsListener(CoordinateCluster *coordinateCluster, std::vector<AttentionPoint*>& attentionPoints);

private:
    CoordinateCluster* coordinateCluster;
    std::vector<AttentionPoint*>& attentionPoints;
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
    std::vector<AttentionPoint*> attentionPoints;
    CoordinateCluster coordinateCluster;
    PointsListener pointsListener{&coordinateCluster, attentionPoints};
};


