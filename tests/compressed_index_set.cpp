#include <catch2/catch.hpp>

#include <lars/compressed_index_set.h>
#include <lars/to_string.h>

TEST_CASE("CompressedIndexSet") {
  auto indices = lars::CompressedIndexSet<int>();
  indices.insert_index_range(-10, 10);
  REQUIRE(lars::stream_to_string(indices) == "{[-10,10]}");
  indices.remove_index(-3);
  indices.remove_index(10);
  auto current = -10;
  for (auto index: indices) {
    if (current == -3) {
      current++;
    }
    REQUIRE(index == current++);
  }
  REQUIRE(current == 10);
  REQUIRE(lars::stream_to_string(indices) == "{[-10,-4],[-2,9]}");
}

