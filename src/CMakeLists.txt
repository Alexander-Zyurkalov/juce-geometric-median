target_sources(JuceGeometricMedian
    PRIVATE
        main.cpp
        gui/MainComponent.cpp
        gui/GeometricMedianWindow.cpp
        gui/PointsArea.cpp
        domain/CoordinateCluster.cpp
)
target_sources(JuceGeometricMedianTests
    PRIVATE
        domain/CoordinateCluster.cpp
        )
