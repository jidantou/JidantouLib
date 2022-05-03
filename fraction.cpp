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

      reduction();
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

void fraction::reciprocal()
{
      int64_t temp;
      temp = _numerator;
      _numerator = _denominator;
      _denominator = temp;
}

fraction& fraction::operator -()
{
      _sign = ~ _sign;
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
            fraction3._numerator = _sign ^ fraction2._sign != 0? _numerator + fraction2._numerator : (_numerator > fraction2._numerator)? _numerator - fraction2._numerator : fraction2._numerator - _numerator;
            fraction3._sign = fraction3._numerator == 0? 0 : (_numerator > fraction2._numerator? _sign : fraction2._sign);
      }
      else
      {
            fraction3._denominator = _denominator * fraction2._denominator;
            fraction3._numerator = _sign ^ fraction2._sign != 0? _numerator * fraction2._denominator + fraction2._numerator * _denominator : (_numerator * fraction2._denominator > fraction2._numerator * _denominator)? _numerator * fraction2._denominator - fraction2._numerator * _denominator : fraction2._numerator * _denominator - _numerator * fraction2._denominator;
            fraction3._sign = fraction3._numerator == 0? 0 : (_numerator * fraction2._denominator > fraction2._numerator * _denominator? _sign : fraction2._sign);
      }

      fraction3.reduction();

      return fraction3;
}

fraction fraction::operator *(const fraction& fraction2)
{
      fraction fraction3;

      fraction3._sign = _sign ^ fraction2._sign == 0? 0 : 1;
      fraction3._numerator = _numerator * fraction2._numerator;
      fraction3._denominator = _denominator * fraction2._denominator;

      return fraction3;
}

fraction fraction::operator /(const fraction& fraction2)
{
      fraction fraction3;

      fraction3._sign = _sign ^ fraction2._sign == 0? 0 : 1;
      fraction3._numerator = _numerator * fraction2._denominator;
      fraction3._denominator = _denominator * fraction2._numerator;

      return fraction3;
}

fraction& fraction::operator +=(const fraction& fraction2)
{
      if(_denominator == fraction2._denominator)
      {
            _numerator = _sign ^ fraction2._sign == 0? _numerator + fraction2._numerator : (_numerator > fraction2._numerator)? _numerator - fraction2._numerator : fraction2._numerator - _numerator;
            _sign = _numerator == 0? 0 : (_numerator > fraction2._numerator? _sign : fraction2._sign);
      }
      else
      {
            _denominator = _denominator * fraction2._denominator;
            _numerator = _sign ^ fraction2._sign == 0? _numerator * fraction2._denominator + fraction2._numerator * _denominator : (_numerator * fraction2._denominator > fraction2._numerator * _denominator)? _numerator * fraction2._denominator - fraction2._numerator * _denominator : fraction2._numerator * _denominator - _numerator * fraction2._denominator;
            _sign = _numerator == 0? 0 : (_numerator * fraction2._denominator > fraction2._numerator * _denominator? _sign : fraction2._sign);
      }

      reduction();

      return *this;
}

fraction& fraction::operator -=(const fraction& fraction2)
{
      if(_denominator == fraction2._denominator)
      {
            _numerator = _sign ^ fraction2._sign != 0? _numerator + fraction2._numerator : (_numerator > fraction2._numerator)? _numerator - fraction2._numerator : fraction2._numerator - _numerator;
            _sign = _numerator == 0? 0 : (_numerator > fraction2._numerator? _sign : fraction2._sign);
      }
      else
      {
            _denominator = _denominator * fraction2._denominator;
            _numerator = _sign ^ fraction2._sign != 0? _numerator * fraction2._denominator + fraction2._numerator * _denominator : (_numerator * fraction2._denominator > fraction2._numerator * _denominator)? _numerator * fraction2._denominator - fraction2._numerator * _denominator : fraction2._numerator * _denominator - _numerator * fraction2._denominator;
            _sign = _numerator == 0? 0 : (_numerator * fraction2._denominator > fraction2._numerator * _denominator? _sign : fraction2._sign);
      }

      reduction();

      return *this;

}

fraction& fraction::operator *=(const fraction& fraction2)
{
      _sign = _sign ^ fraction2._sign == 0? 0 : 1;
      _numerator = _numerator * fraction2._numerator;
      _denominator = _denominator * fraction2._denominator;

      return *this;
}

fraction& fraction::operator /=(const fraction& fraction2)
{
      _sign = _sign ^ fraction2._sign == 0? 0 : 1;
      _numerator = _numerator * fraction2._denominator;
      _denominator = _denominator * fraction2._numerator;

      return *this;
}
