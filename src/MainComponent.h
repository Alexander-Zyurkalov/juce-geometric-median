#include <juce_gui_basics/juce_gui_basics.h>
class MainComponent: public juce::Component{
public:
    MainComponent();
private:
    juce::TextButton addNewPointButton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};


