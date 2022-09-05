#include <catch2/catch_test_macros.hpp>
#include "../src/gui/ScalingService.h"

TEST_CASE("offset without scaling"){
    ScalingService scalingService;

    SECTION("screen to domain coordinates"){
        scalingService.move(1, 2);
        REQUIRE(scalingService.xToDomainX(10.0f) == 9.0f);
        REQUIRE(scalingService.yToDomainY(5.0f) == 3.0f);

        scalingService.move(-1, -2);
        REQUIRE(scalingService.xToDomainX(10.0f) == 10.0f);
        REQUIRE(scalingService.yToDomainY(5.0f) == 5.0f);

        scalingService.move(-1, -2);
        REQUIRE(scalingService.xToDomainX(10.0f) == 11.0f);
        REQUIRE(scalingService.yToDomainY(5.0f) == 7.0f);
    }

    SECTION("domain to screen"){
        scalingService.move(1, 2);
        REQUIRE(scalingService.xToScreenX(11.0f) == 12.0f);
        REQUIRE(scalingService.yToScreenY(7.0f) == 9.0f);

        scalingService.move(-1, -2);
        REQUIRE(scalingService.xToScreenX(10.0f) == 10.0f);
        REQUIRE(scalingService.yToScreenY(5.0f) == 5.0f);

        scalingService.move(-1, -2);
        REQUIRE(scalingService.xToScreenX(9.0f) == 8.0f);
        REQUIRE(scalingService.yToScreenY(3.0f) == 1.0f);
    }
}

TEST_CASE("offset with scaling"){
    ScalingService scalingService;
    SECTION("screen to domain coordinates"){
        scalingService.scale(1.0, 0, 0);
        REQUIRE(scalingService.xToDomainX(10.0f) == 20.0f);
        REQUIRE(scalingService.yToDomainY(5.0f) == 10.0f);

        scalingService.scale(-1.5, 0, 0);
        REQUIRE(scalingService.xToDomainX(10.0f) == 5.0f);
        REQUIRE(scalingService.yToDomainY(5.0f) == 2.5f);

        scalingService.move(4, 4);
        REQUIRE(scalingService.xToDomainX(10.0f) == 1.0f);
        REQUIRE(scalingService.yToDomainY(5.0f) == -1.5f);
    };
    SECTION("domain coordinates to screen") {
        scalingService.scale(1.0, 0, 0);
        REQUIRE(scalingService.xToScreenX(20.0f) == 10.0f);
        REQUIRE(scalingService.yToScreenY(10.0f) == 5.0f);

        scalingService.scale(-1.5, 0, 0);
        REQUIRE(scalingService.xToScreenX(5.0f) == 10.0f);
        REQUIRE(scalingService.yToScreenY(2.5f) == 5.0f);

        scalingService.move( 4, 4);
        REQUIRE(scalingService.xToScreenX(1.0f) == 10.0f);
        REQUIRE(scalingService.yToScreenY(-1.5f) == 5.0f);

    }

}