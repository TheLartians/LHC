
#pragma once

#include <chrono>
#include <iostream>
#include <cmath>
#include <string>
#include <lars/to_string.h>

namespace lars {
  
  template <class Rep,class I> std::string duration_to_string(const std::chrono::duration<Rep,I> &dur){
    using namespace std::chrono;
    
    auto h = duration_cast<hours>(dur);
    auto m = duration_cast<minutes>(dur);
    auto s = duration_cast<seconds>(dur);
    auto ms = duration_cast<milliseconds>(dur);
    auto us = duration_cast<microseconds>(dur);
    auto ns = duration_cast<nanoseconds>(dur);
    
    if(h.count() > 1) return lars::stream_to_string(h.count()) + " h";
    if(m.count() > 1) return lars::stream_to_string(m.count()) + " m";
    if(s.count() > 1) return lars::stream_to_string(s.count()) + " s";
    if(ms.count() > 1) return lars::stream_to_string(ms.count()) + " ms";
    if(us.count() > 1) return lars::stream_to_string(us.count()) + " us";
    return lars::stream_to_string(ns.count()) + " ns";
  }
  
  struct TimeItResult{
    std::chrono::high_resolution_clock::duration duration;
    size_t repititions = 0;
    
    std::chrono::high_resolution_clock::duration average_duration()const{
      return duration/repititions;
    }
  };
  
  struct ExtendedTimeItResult{
    TimeItResult best,worst,most_repititions;
  };
  
  template <class Char> std::basic_ostream<Char> &operator<<(std::basic_ostream<Char> &stream,const TimeItResult &result){
    stream << "average of " << result.repititions << ": " << duration_to_string(result.average_duration());
    return stream;
  }
  
  template <class Char> std::basic_ostream<Char> &operator<<(std::basic_ostream<Char> &stream,const ExtendedTimeItResult &result){
    stream << '[';
    stream << "worst: " << result.worst << ", ";
    stream << "best: " << result.best << ", ";
    stream << "most: " << result.most_repititions;
    stream << ']';
    return stream;
  }
  
  template <typename F> TimeItResult time_it(const F &f,size_t repititions){
    int idx = 0;
    std::chrono::high_resolution_clock::time_point begin,end;
    begin = std::chrono::high_resolution_clock::now();
    for(;idx < repititions;++idx) f();
    end = std::chrono::high_resolution_clock::now();
    TimeItResult result;
    result.duration = end - begin;
    result.repititions = repititions;
    return result;
  }
  
  template <typename F> ExtendedTimeItResult time_it(const F &f,std::chrono::high_resolution_clock::duration timeout = std::chrono::seconds(1)){
    ExtendedTimeItResult result;
    size_t repititions = 1;
    
    std::chrono::high_resolution_clock::time_point begin,end;
    end = begin = std::chrono::high_resolution_clock::now();
    
    result.worst = result.best = result.most_repititions = time_it(f,repititions);
    repititions *= 2;
    end  = std::chrono::high_resolution_clock::now();
    
    while(end - begin < timeout){
      result.most_repititions = time_it(f,repititions);
      if(result.most_repititions.average_duration() > result.worst.average_duration()) result.worst = result.most_repititions;
      if(result.most_repititions.average_duration() < result.best.average_duration()) result.best = result.most_repititions;
      if(repititions * 2 < repititions) break;
      repititions *= 2;
      end  = std::chrono::high_resolution_clock::now();
    }
    return result;
  }
  
}

