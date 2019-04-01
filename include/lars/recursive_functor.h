#pragma once
// inspired by https://stackoverflow.com/questions/18085331/recursive-lambda-functions-in-c14/18085333#18085333

#include <type_traits>

namespace lars {
  
  
  template <class Functor> struct RecursiveFunctor{
    Functor functor;
    
    template<typename... Args> decltype(auto) operator()(Args&&... args) &{ return functor(*this, std::forward<Args>(args)...); }
    template<typename... Args> decltype(auto) operator()(Args&&... args) const&{ return functor(*this, std::forward<Args>(args)...); }
    template<typename... Args> decltype(auto) operator()(Args&&... args) &&{ return std::move(functor)(std::move(*this), std::forward<Args>(args)...); }
  };
  
  template<typename Functor> RecursiveFunctor<typename std::decay<Functor>::type> make_recursice_functor(Functor&& functor){
    return { std::forward<Functor>(functor) };
  }

  
}
