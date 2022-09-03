#include <catch2/catch_test_macros.hpp>
#include "../src/gui/ScalingService.h"
#include "catch2/catch_approx.hpp"

TEST_CASE("offset without scaling"){
    ScalingService scalingService;
    SECTION("screen to domain coordinates"){
        using namespace Catch::literals;
        scalingService.scale(0.0, 1, 2);
        REQUIRE(scalingService.xToDomainX(10) == 11.0_a);
        REQUIRE(scalingService.yToDomainY(5) == 7.0_a);

        scalingService.scale(0.0, -1, -2);
        REQUIRE(scalingService.xToDomainX(10) == 10.0_a);
        REQUIRE(scalingService.yToDomainY(5) == 5.0_a);

        scalingService.scale(0.0, -1, -2);
        REQUIRE(scalingService.xToDomainX(10) == 9.0_a);
        REQUIRE(scalingService.yToDomainY(5) == 3.0_a);
    }
    SECTION("domain to screen"){

    }
}