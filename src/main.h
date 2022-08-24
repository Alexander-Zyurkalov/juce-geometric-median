#include <juce_gui_basics/juce_gui_basics.h>
class GeometricMedianApplication: public juce::JUCEApplication {
public:
    const juce::String getApplicationName() override;

    const juce::String getApplicationVersion() override;

    void initialise(const juce::String &commandLineParameters) override;

    void shutdown() override;
};