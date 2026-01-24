#ifndef _COMPLEX_ //标准头文件防御式声明
#define _COMPLEX_
#include<cmath>

class complex
{
  public:
  complex (double r= 0, double i = 0)
  :re(r),im(i)
  {}

  complex& operator+=(const complex&);

  double real() const {return re;}
  double imag() const {return im;}
  

  private:
  double re,im;
  friend complex& _doapl(complex*,const complex&);
};

//complex::function
inline complex& complex::operator+=(const complex& r)
{
    return _doapl(this,r);
}

inline complex& _doapl(complex* ths,const complex& r)//* ths -> 指针
{
    ths->re += r.re;
    ths->im += r.im;
    return *ths;// *ths 解指针 对象本身
}
inline double imag(const complex& x)
{
    return x.imag();
}
inline double real(const complex& x)
{
    return x.real();
}

//非成员函数
inline complex operator + (const complex& x, const complex& y)
{
    return complex (real(x)+real(y),imag(x)+imag(y));//->临时对象
}//return by value

inline complex operator + (const complex& x)
{
    return x;
}

inline complex operator - (const complex& x)
{
    return (-real(x),-imag(x));
}

inline bool operator == (const complex&x,const complex&y)
{
    return real(x) == real(y) && imag(x) == imag(y);
}

#include<iostream>
std::ostream& operator << (std::ostream& os,const complex&x)
{
    return os <<'('<<real(x)<<','<<imag(x)<<')';
} 

#endif