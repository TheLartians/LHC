#include <catch2/catch.hpp>
#include <vector>

#include <lars/iterators.h>

TEST_CASE("Range iteration 1") {
  auto current = 0;
  for (auto i : lars::range(10)) {
    REQUIRE(i == current++);
  }
  REQUIRE(current == 10);
}

TEST_CASE("Range iteration 2") {
  auto current = -4;
  for (auto i : lars::range(current, 7)) {
    REQUIRE(i == current++);
  }
  REQUIRE(current == 7);
}

TEST_CASE("Range iteration 3") {
  auto current = 12;
  for (auto i : lars::range(10, -10, -2)) {
    REQUIRE(i == (current -= 2));
  }
  REQUIRE(current == -8);
}

TEST_CASE("Enumerate") {
  std::vector<int> v(10, 0);
  REQUIRE(v.size() == 10);
  size_t current = 0;
  for (auto [i, o] : lars::enumerate(v)) {
    REQUIRE(i == current++);
    REQUIRE(&v[i] == &o);
  }
  REQUIRE(current == 10);
}

TEST_CASE("Reversed") {
  auto range = lars::range(10);
  std::vector<int> v(range.begin(), range.end());
  auto current = 10;
  for (auto i : lars::reversed(v)) {
    REQUIRE(i == --current);
  }
  REQUIRE(current == 0);
}

TEST_CASE("Slice") {
  auto range = lars::range(10);
  std::vector<int> v(range.begin(), range.end());
  auto current = 5;
  for (auto i : lars::slice(v.begin() + 5, v.end())) {
    REQUIRE(i == current++);
  }
  REQUIRE(current == 10);
}
