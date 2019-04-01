#pragma once

#include <memory>

namespace lars {
  
  struct DestructorBase{
    virtual ~DestructorBase(){}
  };
  
  template <class F> struct Destructor:public DestructorBase{
    F callback;
    Destructor(const F & f):callback(f){}
    ~Destructor(){ callback(); }
  };
  
  using SharedDestructor = std::shared_ptr<DestructorBase>;
  
  template <class F> std::shared_ptr<Destructor<F>> make_shared_destructor(const F &f){
    return std::make_shared<Destructor<F>>(f);
  }
  
}
