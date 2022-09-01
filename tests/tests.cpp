#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "../src/domain/CoordinateCluster.h"
TEST_CASE("Coordinate distances"){

    SECTION("Simple test with Y coordinate") {
        auto pointA = Coordinates{0, 0};
        auto pointB = Coordinates{0, 10};
        float distance = calculateDistance(&pointA, &pointB);
        REQUIRE(distance == 10.0f);

        pointA = Coordinates{0, 5};
        pointB = Coordinates{0, 10};
        distance = calculateDistance(&pointA, &pointB);
        REQUIRE(distance == 5.0f);
    }

    SECTION("Simple test with X coordinates") {
        auto pointA = Coordinates{0, 0};
        auto pointB = Coordinates{10, 0};
        float distance = calculateDistance(&pointA, &pointB);
        REQUIRE(distance == 10.0f);

        pointA = Coordinates{5, 0};
        pointB = Coordinates{10, 0};
        distance = calculateDistance(&pointA, &pointB);
        REQUIRE(distance == 5.0f);
    }
    SECTION("Simple test with XY coordinates") {
        auto pointA = Coordinates{0, 0};
        auto pointB = Coordinates{10, 10};
        float distance = calculateDistance(&pointA, &pointB);
        using namespace Catch::literals;
        REQUIRE(distance == 14.14214_a);
    }

}

TEST_CASE("The median algorithm"){
    SECTION("even number of elements") {
        CoordinateCluster cluster;
        cluster.addCoordinates(11.0, 11.0);
        cluster.addCoordinates(10.0, 10.0);
        cluster.addCoordinates(12.0, 12.0);
        auto result = cluster.calculateMiddlePointByMedianMassSpread();
        std::vector<Coordinates> expected;
        expected.emplace_back(11.0, 11.0);
        REQUIRE(result == expected);
    }
    SECTION("odd number of elements") {
        CoordinateCluster cluster;
        cluster.addCoordinates(11.0, 11.0);
        cluster.addCoordinates(10.0, 10.0);
        auto result = cluster.calculateMiddlePointByMedianMassSpread();
        std::vector<Coordinates> expected;
        expected.emplace_back(11.0, 11.0);
        expected.emplace_back(10.0, 10.0);
        REQUIRE(result == expected);
    }
}