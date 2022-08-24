#include "MainComponent.h"

MainComponent::MainComponent() {
    setSize(600, 400);
    addNewPointButton.setButtonText("Add a new point");
    addNewPointButton.setBounds(10, 10, 100, 40);
    addAndMakeVisible(addNewPointButton);
}