#include <catch2/catch.hpp>

#include <lars/mutator.h>

namespace {
class A {
  MUTATOR_MEMBER_PRIVATE(int, changes, = 0, );
  MUTATOR_MEMBER_PROTECTED(int, inherited, = 0, );
  MUTATOR_MEMBER_PUBLIC(int, data, = 1, set_changes(changes() + 1));
};

struct B : public A {
  B() { set_inherited(inherited() + 1); }
};
} // namespace

TEST_CASE("MUTATORS") {

  A a;
  REQUIRE(a.data() == 1);
  REQUIRE(a.changes() == 0);
  REQUIRE(a.inherited() == 0);

  a.set_data(42);
  REQUIRE(a.data() == 42);
  REQUIRE(a.changes() == 1);

  B b;
  REQUIRE(b.inherited() == 1);
}