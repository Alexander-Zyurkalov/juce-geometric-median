#include <juce_gui_basics/juce_gui_basics.h>
#include "PointsArea.h"
class MainComponent: public juce::Component,
                     public juce::Button::Listener {
public:
    MainComponent();

    void buttonClicked(juce::Button *button) override;

private:
    juce::TextButton addNewPointButton;
    PointsArea pointsArea;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};


