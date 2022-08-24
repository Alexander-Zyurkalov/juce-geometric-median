#include <juce_gui_basics/juce_gui_basics.h>
class GeometricMedianWindow: public juce::DocumentWindow{
public:
    GeometricMedianWindow(const juce::String &name);


    void closeButtonPressed() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GeometricMedianWindow)
};
