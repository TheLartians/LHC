#pragma once

namespace lars {
  
  class DummyClass{};
  template <typename D,typename T = void> struct DummyTemplate{ const static bool value = true; using type = T; };
  template <typename ... Args> void dummy_function(const Args & ... args){ }
  
}
