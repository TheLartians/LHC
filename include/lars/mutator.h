#pragma once

#include <utility>

namespace lars{
  namespace mutator_helper{
    template <class T,typename ... Args> T initialize(Args && ... args){
      return T(args...);
    }
  }
}

#define MUTATOR_MEMBER_VISIBILITY(TYPE,NAME,DEFAULT,CODE,GETTER_VISIBILITY,SETTER_VISIBILITY) private: TYPE _ ## NAME DEFAULT; GETTER_VISIBILITY TYPE const &NAME()const{ return _ ## NAME; } SETTER_VISIBILITY template <typename ... Args> auto &set_ ## NAME(const Args & ... args){ auto previous_ ## NAME = ::lars::mutator_helper::initialize<TYPE>(args...); std::swap(previous_ ## NAME, _ ## NAME ); CODE; return *this; }

#define MUTABLE_MUTATOR_MEMBER_VISIBILITY(TYPE,NAME,DEFAULT,CODE,GETTER_VISIBILITY,SETTER_VISIBILITY) private: mutable TYPE _ ## NAME DEFAULT; GETTER_VISIBILITY TYPE const &NAME()const{ return _ ## NAME; } SETTER_VISIBILITY template <typename ... Args> auto &set_ ## NAME(const Args & ... args)const{ auto previous_ ## NAME = ::lars::mutator_helper::initialize<TYPE>(args...); std::swap(previous_ ## NAME, _ ## NAME ); CODE; return *this; }

#define REFERENCE_MUTATOR_MEMBER_VISIBILITY(TYPE,NAME,DEFAULT,CODE,GETTER_VISIBILITY,SETTER_VISIBILITY) private: TYPE * _ ## NAME DEFAULT; GETTER_VISIBILITY TYPE &NAME()const{ return * _ ## NAME; } SETTER_VISIBILITY auto &set_ ## NAME(TYPE &t){ _ ## NAME = &t; CODE; return *this; }

#define MUTATOR_MEMBER_PRIVATE(TYPE,NAME,DEFAULT,CODE) MUTATOR_MEMBER_VISIBILITY(TYPE,NAME,DEFAULT,CODE,public:,private:);
#define MUTATOR_MEMBER_PROTECTED(TYPE,NAME,DEFAULT,CODE) MUTATOR_MEMBER_VISIBILITY(TYPE,NAME,DEFAULT,CODE,public:,protected:);
#define MUTATOR_MEMBER_PUBLIC(TYPE,NAME,DEFAULT,CODE) MUTATOR_MEMBER_VISIBILITY(TYPE,NAME,DEFAULT,CODE,public:,public:);

#define MUTATOR_MEMBER(TYPE,NAME,DEFAULT,CODE) MUTATOR_MEMBER_PUBLIC(TYPE,NAME,DEFAULT,CODE);

#define REFERENCE_MUTATOR_MEMBER(TYPE,NAME,DEFAULT,CODE) REFERENCE_MUTATOR_MEMBER_VISIBILITY(TYPE,NAME,DEFAULT,CODE,public:,public:);

#define MUTABLE_MUTATOR_MEMBER(TYPE,NAME,DEFAULT,CODE) MUTABLE_MUTATOR_MEMBER_VISIBILITY(TYPE,NAME,DEFAULT,CODE,public:,public:);
