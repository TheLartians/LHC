#pragma once

#include <memory>

namespace lars {
  
  template <class T> std::weak_ptr<T> to_weak_ptr(const std::shared_ptr<T> &ptr){
    return std::weak_ptr<T>(ptr);
  }
  
}
