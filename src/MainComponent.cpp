#include "MainComponent.h"

MainComponent::MainComponent() {
    setSize(600, 600);
    addNewPointButton.setButtonText("Add a new point");
    addNewPointButton.setBounds(10, 10, 100, 40);
    addAndMakeVisible(addNewPointButton);

    pointsArea.setBounds(10, 140, 580, 400);
    addAndMakeVisible(pointsArea);
}