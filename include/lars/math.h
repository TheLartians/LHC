#pragma once

#include <limits>
#include <cmath>

namespace lars {
  
  template <typename T> inline T abs(const T& v) {
    return v < 0 ? -v : v;
  }
  
  template <typename T> inline T max(const T& a,const T& b) {
    return a < b ? b : a;
  }
  
  template <typename T> inline T min(const T& a,const T& b) {
    return a < b ? a : b;
  }
  
  template<class T> inline constexpr T pow(const T base, const unsigned exponent) {
    return (exponent == 0) ? 1 : (exponent % 2 == 0) ? pow(base, exponent/2)*pow(base, exponent/2) : base * pow(base, (exponent-1)/2) * pow(base, (exponent-1)/2);
  }
  
  template<unsigned exponent,class T> inline constexpr T pow(const T base) {
    return (exponent == 0) ? 1 : (exponent % 2 == 0) ? pow<exponent/2>(base)*pow<exponent/2>(base) : base * pow<(exponent-1)/2>(base) * pow<(exponent-1)/2>(base);
  }

  template <typename T> static int sign(T val) {
    return (T(0) < val) - (val < T(0));
  }
  
  template <typename T> bool are_approximately_equal(T a, T b, T epsilon = std::numeric_limits<T>::epsilon()){
    if(!std::isfinite(a) || !std::isfinite(b)) return a == b;
    return lars::abs(a - b) <= ( lars::max(lars::abs(a),lars::abs(b)) * epsilon);
  }

}
