#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include <string>
#include "hash.h"

TEST_CASE("Initial test")
{
    SECTION("always true")
    {
            REQUIRE(true);
            REQUIRE_FALSE(false);
    }
}

#endif // CATCH_CONFIG_MAIN
