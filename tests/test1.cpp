#include "quick-ftxui.hpp"
#include <catch2/catch_test_macros.hpp>
#include <string>

auto parse_helper(std::string &&str) {
    return client::parse_numbers(str.begin(), str.end());
}

TEST_CASE("Parse Simple", "[double,double]") {
    REQUIRE(parse_helper("123,123.2"));
    REQUIRE(parse_helper("123.2,123.2"));
    REQUIRE(parse_helper("123,123"));
    REQUIRE(parse_helper("123"));
}