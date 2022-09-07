#include "MainComponent.h"

MainComponent::MainComponent() {
    setSize(600, 600);
    addNewPointButton.setButtonText("Add a new point");
    addNewPointButton.setBounds(10, 10, 100, 40);
    addAndMakeVisible(addNewPointButton);

    pointsArea.setBounds(10, 140, 580, 400);
    addAndMakeVisible(pointsArea);

    addNewPointButton.addListener(this);

    verticalScrollBar.setBounds(575, 140, 15, 385);
    verticalScrollBar.setAutoHide(true);
    verticalScrollBar.setRangeLimits(0,pointsArea.getBounds().getHeight()-1);
    verticalScrollBar.setCurrentRange(0,pointsArea.getBounds().getHeight()-1);
    addAndMakeVisible(verticalScrollBar);
    verticalScrollBar.addListener(&pointsArea);
    verticalScrollBar.addMouseListener(&myScrollBarMouseListener, false);

    horizontalScrollBar.setBounds(10, 525, 565, 15);
    horizontalScrollBar.setAutoHide(true);
    horizontalScrollBar.setRangeLimits(0, pointsArea.getBounds().getWidth() - 1);
    horizontalScrollBar.setCurrentRange(0, pointsArea.getBounds().getWidth() - 1);
    addAndMakeVisible(horizontalScrollBar);
    horizontalScrollBar.addListener(&pointsArea);
    horizontalScrollBar.addMouseListener(&myScrollBarMouseListener, false);

}

void MainComponent::buttonClicked(juce::Button *button) {
    pointsArea.addPoint();
}
