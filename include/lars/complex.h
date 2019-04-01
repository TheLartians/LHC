#pragma once

#include <ostream>
#include <complex>

namespace lars {
  
  // we create our own complex class since std::complex seems to be extremely slow (3x slower than the class below on our hardware, probably because operations are not inlined)
  
  template <class Real> struct Complex{
    using Scalar = Real;
    Scalar real,imag;
    
    Complex(Scalar r=0,Scalar i=0):real(r),imag(i){ }
    
    Complex(const Complex &) = default;
    Complex(Complex &&) = default;
    Complex &operator=(const Complex &) = default;
    Complex &operator=(Complex &&) = default;
    Complex(const std::complex<Real> &c):real(c.real()),imag(c.imag()){ }
    
    bool operator==(const Complex &other)const{ return real == other.real && imag == other.imag; }
    bool operator!=(const Complex &other)const{ return !(*this == other); }
    
    Complex &operator=(const Scalar &s){ real = s; imag = 0; return *this; }
    Complex &operator+=(const Complex &other){ real += other.real; imag += other.imag; return *this; }
    Complex &operator-=(const Complex &other){ real -= other.real; imag -= other.imag; return *this; }
    
    Complex operator+(const Complex &other)const{ return Complex(real + other.real, imag + other.imag ); }
    Complex operator-(const Complex &other)const{ return Complex(real - other.real, imag - other.imag ); }
    
    Complex operator*(const Scalar &other)const{ return Complex(real * other, imag * other ); }
    Complex operator/(const Scalar &other)const{ return Complex(real/other, imag/other ); }
    Complex operator*(const Complex &other)const{ return Complex(real * other.real - imag * other.imag,real * other.imag + imag * other.real ); }
    Complex operator/(const Complex &other)const{
      auto d = other.real * other.real + other.imag * other.imag;
      return Complex((real * other.real + imag * other.imag)/d,(-real * other.imag + imag * other.real)/d);
    }
    
    Complex operator-()const{ return Complex(-real,-imag); }
    
    operator std::complex<Real> () const { return std::complex<Real>(real,imag);  }
  };
  
  template <class Real> Complex<Real> operator+(const Real &s,const Complex<Real> &c){ return c+s; }
  template <class Real> Complex<Real>  operator-(const Real &s,const Complex<Real> &c){ return Complex<Real>(s,0)-c; }
  template <class Real> Complex<Real>  operator*(const Real &s,const Complex<Real> &c){ return c*s; }
  template <class Real> Complex<Real>  operator/(const Real &s,const Complex<Real> &c){ return Complex<Real>(s,0)/c; }
  
  template <class Real> Complex<Real> exp(const Complex<Real> &z){
    auto a = std::exp(z.real);
    return Complex<Real>(a*std::cos(z.imag),a*std::sin(z.imag));
  }
  
  template <class Real> Complex<Real> sqrt(const Complex<Real> &z){ return std::sqrt<Real>(z); }
  template <class Real> Complex<Real> pow(const Complex<Real> &z1,const Complex<Real> &z2){ return std::pow<Real>(z1,z2); }
  
  template <class Real> std::ostream & operator<<(std::ostream &stream,const Complex<Real> &c){
    stream << '(' << c.real << ',' << c.imag << ')';
    return stream;
  }
  
  template <class Real> std::wostream & operator<<(std::wostream &stream,const Complex<Real> &c){
    stream << '(' << c.real << ',' << c.imag << ')';
    return stream;
  }
  
  
}
