#pragma once

#include <functional>

namespace lars {
  
  template <class T> inline void hash_combine(std::size_t& seed, T const& v) {
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
  }
  
  struct ArrayHasher {
    template <class Array> std::size_t operator()(const Array& a) const {
      using ScalarHasher = std::hash<decltype(a.front())>;
      ScalarHasher scalar_hasher;
      size_t seed = 0;
      for(auto &v:a) hash_combine(seed,scalar_hasher(v));
      return seed;
    }
  };

  namespace{
    
  // Recursive template code derived from Matthieu M.
  template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1> struct HashValueImpl{
    static void apply(size_t& seed, Tuple const& tuple){
      HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
      hash_combine(seed, std::get<Index>(tuple));
      }
    };
  
    template <class Tuple> struct HashValueImpl<Tuple,0>{
      static void apply(size_t& seed, Tuple const& tuple){
        hash_combine(seed, std::get<0>(tuple));
      }
    };
  }
  
  template <typename ... TT> struct TupleHasher;
  
  template <typename ... TT> struct TupleHasher<std::tuple<TT...>> {
    size_t operator()(std::tuple<TT...> const& tt) const{
      size_t seed = 0;
      HashValueImpl<std::tuple<TT...> >::apply(seed, tt);
      return seed;
    }
  };
  
  template <typename T,typename ... TT> struct TupleHasher<T,TT...> {
    size_t operator()(std::tuple<T,TT...> const& tt) const{
      size_t seed = 0;
      HashValueImpl<std::tuple<T,TT...> >::apply(seed, tt);
      return seed;
    }
  };

  
  struct FloatHasher {
    size_t operator()(const float & f) const{
      return (unsigned&)f;
    }
  };
  
  template <class Array,class ScalarHasher = std::hash<typename Array::Scalar>> struct NDArrayHasher {
    ScalarHasher scalar_hasher;
    std::size_t operator()(const Array& a) const {
      size_t seed = 0;
      a.for_all_values([&](const typename Array::Scalar &s){ seed ^= scalar_hasher(s) + 0x9e3779b9 + (seed<<6) + (seed>>2); });
      return seed;
    }
  };
  

  
}
