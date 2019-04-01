

#pragma once

#include <memory>
#include <ostream>
#include <functional>


namespace lars {
  
  template <class T> class shared_object{
    std::shared_ptr<T> data;
    
    mutable typename std::hash<T>::result_type cached_hash;
    mutable bool hash_valid = false;
    
    void invalidate_hash(){ hash_valid = false; }
    void take_hash(const shared_object &other){ hash_valid = other.hash_valid; cached_hash = other.cached_hash; }
    
    friend std::hash<lars::shared_object<T>>;
    
  public:
    template <typename ... Args> shared_object(Args... args):data(std::make_shared<T>(args...)){}
    shared_object(const shared_object &other):data(other.data){ take_hash(other); }
    shared_object(shared_object &&other):data(other.data){ take_hash(other); }
    
    shared_object &operator=(const shared_object &other){ data = other.data; take_hash(other); return *this; }
    shared_object &operator=(shared_object &&other){ data = other.data; take_hash(other); return *this; }
    template <typename Other> shared_object & operator=(Other other){ *data = other; return *this; }
    
    bool operator!=(const T &other) const { return *data != other; }
    bool operator==(const T &other) const { return *data == other; }
    
    bool operator!=(const shared_object &other) const {
      if(hash_valid && other.hash_valid) if(cached_hash != other.cached_hash) return true;
      return *data != T(other);
    }
    
    bool operator==(const shared_object &other) const {
      if(hash_valid && other.hash_valid) if(cached_hash != other.cached_hash) return false;
      return *data == T(other);
    }
    
    template <typename Other> bool operator==(const Other &other) const { return *data == T(other); }
    template <typename Other> bool operator!=(const Other &other) const { return *data != T(other); }
    template <typename Other> bool operator>=(const Other &other) const { return *data >= T(other); }
    template <typename Other> bool operator<=(const Other &other) const { return *data <= T(other); }
    template <typename Other> bool operator>(const Other &other) const { return *data > T(other); }
    template <typename Other> bool operator<(const Other &other) const { return *data < T(other); }
    
    template <typename Other> shared_object & operator+=(const Other &other){ *data += T(other); return *this; }
    template <typename Other> shared_object & operator*=(const Other &other){ *data += T(other); return *this; }
    template <typename Other> shared_object & operator-=(const Other &other){ *data += T(other); return *this; }
    template <typename Other> shared_object & operator/=(const Other &other){ *data += T(other); return *this; }
    
    T & operator->(){ invalidate_hash(); return data->operator->(); }
    const T & operator->()const { return data->operator->(); }
    T & operator*(){ invalidate_hash(); return *data; }
    const T & operator*()const{ return *data; }
    
    operator T&(){ invalidate_hash(); return *data; }
    operator const T &()const{ return *data; }
  };
  
  template <class T> shared_object<T> operator+(const shared_object<T> &lhs,const shared_object<T> &rhs){ return shared_object<T>((*lhs) + (*rhs)); }
  template <class T> shared_object<T> operator-(const shared_object<T> &lhs,const shared_object<T> &rhs){ return shared_object<T>((*lhs) - (*rhs)); }
  template <class T> shared_object<T> operator*(const shared_object<T> &lhs,const shared_object<T> &rhs){ return shared_object<T>((*lhs) * (*rhs)); }
  template <class T> shared_object<T> operator/(const shared_object<T> &lhs,const shared_object<T> &rhs){ return shared_object<T>((*lhs) / (*rhs)); }
 
  template <class T> std::ostream & operator<<(std::ostream &stream,const shared_object<T> &obj){
    return stream << *obj;
  }
  
}

namespace std {
  
  template <class T> struct hash<lars::shared_object<T>> {
    
    typedef lars::shared_object<T> argument_type;
    typedef std::size_t result_type;
    
    result_type operator()(argument_type const& s) const{
      if(!s.hash_valid){
        s.cached_hash = std::hash<T>()(*s);
        s.hash_valid = true;
      }
      return s.cached_hash;
    }
    
  };

}
