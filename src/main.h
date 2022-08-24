#include <juce_gui_basics/juce_gui_basics.h>
#include "MainComponent.h"
#include "GeometricMedianWindow.h"

class GeometricMedianApplication: public juce::JUCEApplication {
public:
    const juce::String getApplicationName() override;

    const juce::String getApplicationVersion() override;

    void initialise(const juce::String &commandLineParameters) override;

    void shutdown() override;
private:
    std::unique_ptr<GeometricMedianWindow> geometricMedianWindow;
};