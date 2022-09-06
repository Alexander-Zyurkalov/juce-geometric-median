#include "MainComponent.h"

MainComponent::MainComponent() {
    setSize(600, 600);
    addNewPointButton.setButtonText("Add a new point");
    addNewPointButton.setBounds(10, 10, 100, 40);
    addAndMakeVisible(addNewPointButton);

    pointsArea.setBounds(10, 140, 580, 400);
    addAndMakeVisible(pointsArea);

    addNewPointButton.addListener(this);

    verticalScrollBar.setBounds(575, 140, 15, 400);
    verticalScrollBar.setAutoHide(true);
    verticalScrollBar.setRangeLimits(0,pointsArea.getBounds().getHeight()-1);
    verticalScrollBar.setCurrentRange(0,pointsArea.getBounds().getHeight()-1);
    addAndMakeVisible(verticalScrollBar);
}

void MainComponent::buttonClicked(juce::Button *button) {
    pointsArea.addPoint();
}
