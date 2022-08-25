#include "GeometricMedianWindow.h"
#include "MainComponent.h"

void GeometricMedianWindow::closeButtonPressed() {
    juce::JUCEApplication::getInstance()->systemRequestedQuit();
}

GeometricMedianWindow::GeometricMedianWindow(const juce::String &name) : DocumentWindow(name,
                                                                                        juce::Colours::darkgrey,
                                                                                        juce::DocumentWindow::TitleBarButtons::allButtons) {
    setUsingNativeTitleBar(true);
    centreWithSize(400, 400);
    setContentOwned(new MainComponent(), true);
    setResizable(false, false);
    setVisible(true);
}
