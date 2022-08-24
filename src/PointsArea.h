#include <juce_gui_basics/juce_gui_basics.h>
class PointsArea: public juce::DrawableComposite{
public:
    PointsArea();
    void mouseMove(const juce::MouseEvent &event) override;

    void mouseDrag(const juce::MouseEvent &event) override;


private:
    juce::DrawablePath point;
};

