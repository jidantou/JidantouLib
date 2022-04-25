#include <cmath>
#include "fraction.h"

using namespace std;
using namespace Jidantou;

inline fraction::fraction()
{
      _sign = 0;
}

inline fraction::fraction(const uint64_t numerator, const uint64_t denominator, const bool sign)
{
      if(denominator == 0)
      {
            _sign = 0;
            throw "Denominator can't be zero!";
      }
      else
      {
            _numerator = numerator;
            _denominator = denominator;
            _sign = sign;
      }
}

inline fraction::fraction(const fraction& fraction1)
{
      _numerator = fraction1._numerator;
      _denominator = fraction1._denominator;
      _sign = fraction1._sign;
}

inline fraction::~fraction()
{}

inline void fraction::reduction()
{
      uint64_t a, b, c;

      while (_numerator & 0x01 == 0 && _denominator & 0x01 == 0)
      {
            _numerator >>= 1;
            _denominator >>= 1;
      }

      a = _numerator > _denominator? _numerator: _denominator;
      b = _numerator > _denominator? _denominator: _numerator;
      
      while (a != b)
      {
            c = a - b;
            a = c > b? c: b;
            b = c > b? b: c;
      }

      _numerator /= a;
      _denominator /= a;
      
}

fraction fraction::operator +(const fraction& fraction2)
{
      fraction fraction3;

      if(_denominator == fraction2._denominator)
      {
            fraction3._denominator = _denominator;
            fraction3._numerator = _sign ^ fraction2._sign == 0? _numerator + fraction2._numerator : (_numerator > fraction2._numerator)? _numerator - fraction2._numerator : fraction2._numerator - _numerator;
            fraction3._sign = fraction3._numerator == 0? 0 : (_numerator > fraction2._numerator? _sign : fraction2._sign);
      }
      else
      {
            fraction3._denominator = _denominator * fraction2._denominator;
            fraction3._numerator = _sign ^ fraction2._sign == 0? _numerator * fraction2._denominator + fraction2._numerator * _denominator : (_numerator * fraction2._denominator > fraction2._numerator * _denominator)? _numerator * fraction2._denominator - fraction2._numerator * _denominator : fraction2._numerator * _denominator - _numerator * fraction2._denominator;
            fraction3._sign = fraction3._numerator == 0? 0 : (_numerator * fraction2._denominator > fraction2._numerator * _denominator? _sign : fraction2._sign);
      }

      fraction3.reduction();

      return fraction3;
}

fraction fraction::operator -(const fraction& fraction2)
{
      fraction fraction3;

      if(_denominator == fraction2._denominator)
      {
            fraction3._denominator = _denominator;
            if(_numerator > fraction2._numerator)
            {
                  fraction3._numerator = _numerator - fraction2._numerator;
                  fraction3._sign = 0;
            }
            else
            {
                  fraction3._numerator = fraction2._numerator - _numerator;
                  fraction3._sign = 1;
            }
      }
      else
      {
            fraction3._denominator = _denominator * fraction2._denominator;
            fraction3._numerator = _numerator * fraction2._denominator - _denominator * fraction2._numerator;
      }
      return fraction3;
}

fraction fraction::operator *(const fraction& fraction2)
{}

fraction fraction::operator/(const fraction& fraction2)
{}