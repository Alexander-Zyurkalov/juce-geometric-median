#include "juce_gui_basics/juce_gui_basics.h"

class PointsListener: public juce::MouseListener{
    void mouseDrag(const juce::MouseEvent &event) override;
};
class MyPoint: public  juce::Component{
  void paint(juce::Graphics &g) override;
};

class PointsArea: public juce::Component{
public:
    PointsArea();
    ~PointsArea();
    void paint(juce::Graphics &g) override;

    void addPoint();
private:
    PointsListener pointsListener;
    std::vector<MyPoint*> points;
};

