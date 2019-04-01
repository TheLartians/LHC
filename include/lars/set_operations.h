

#pragma once

#include <unordered_set>
#include <iterator>
#include <algorithm>

namespace lars {
  
  template <typename InIt1, typename InIt2, typename OutIt> OutIt unordered_set_intersection(InIt1 b1, InIt1 e1, InIt2 b2, InIt2 e2, OutIt out) {
    while (!(b1 == e1)) {
      if (!(std::find(b2, e2, *b1) == e2)) {
        *out = *b1;
        ++out;
      }
      ++b1;
    }
    return out;
  }
  
  template <class T> std::unordered_set<T> set_intersection(const std::unordered_set<T> &x,const std::unordered_set<T> &y){
    std::unordered_set<T> z;
    unordered_set_intersection(x.begin(), x.end(),y.begin(), y.end(),std::inserter(z, z.begin()));
    return z;
  }
  
  template <class T> std::unordered_set<T> set_union(const std::unordered_set<T> &x,const std::unordered_set<T> &y){
    std::unordered_set<T> z = x;
    std::copy( std::begin(y), std::end(y), std::inserter( z, std::end(z) ) );
    return z;
  }
  
  template <class T1,class T2> T1 set_intersection(const T1 &x,const T2 &y){
    T1 z;
    std::set_intersection(x.begin(), x.end(),y.begin(), y.end(),std::inserter(z, z.begin()));
    return std::move(z);
  }
  
  template <class T1,class T2> T1 set_difference(const T1 &x,const T2 &y){
    T1 z;
    std::set_difference(x.begin(), x.end(),y.begin(), y.end(),std::inserter(z, z.begin()));
    return std::move(z);
  }
  
  template <class T1,class T2> T1 set_union(const T1 &x,const T2 &y){
    T1 z;
    std::set_union(x.begin(), x.end(),y.begin(), y.end(),std::inserter(z, z.begin()));
    return std::move(z);
  }
  
  
  template <class T1,class T2,class C> T1 set_intersection(const T1 &x,const T2 &y,C c){
    T1 z;
    std::set_intersection(x.begin(), x.end(),y.begin(), y.end(),std::inserter(z, z.begin()),c);
    return std::move(z);
  }
  
  template <class T1,class T2,class C> T1 set_difference(const T1 &x,const T2 &y,C c){
    T1 z;
    std::set_difference(x.begin(), x.end(),y.begin(), y.end(),std::inserter(z, z.begin()),c);
    return std::move(z);
  }
  
  template <class T1,class T2,class C> T1 set_union(const T1 &x,const T2 &y,C c){
    T1 z;
    std::set_union(x.begin(), x.end(),y.begin(), y.end(),std::inserter(z, z.begin()),c);
    return std::move(z);
  }
  
  
}
