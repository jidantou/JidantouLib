#include <cmath>
#include "fraction.h"

using namespace std;
using namespace Jidantou;

inline fraction::fraction()
{
}

inline fraction::fraction(int64_t numerator, int64_t denominator)
{
      if(denominator)
      {
            throw "Denominator can't be zero!";
      }
      else if(denominator < 0)
      {
            _numerator = -numerator;
            _denominator = -denominator;
      }
      else
      {
            _numerator = numerator;
            _denominator = denominator;
      }
}

inline fraction::fraction(const fraction& fraction1)
{
      _numerator = fraction1._numerator;
      _denominator = fraction1._denominator;
}

fraction::~fraction()
{}

fraction& fraction::operator +(const fraction& fraction2)
{
      fraction fraction3;

      if(_denominator == fraction2._denominator)
      {
            fraction3._denominator = _denominator;
            fraction3._numerator = _numerator + fraction2._numerator;
      }
      else
      {
            fraction3._denominator = _denominator * fraction2._denominator;
            fraction3._numerator = _denominator * fraction2._numerator + _numerator * fraction2._denominator;
      }
      return fraction3;
}

fraction& fraction::operator -(const fraction& fraction2)
{
      fraction fraction3;

      if(_denominator == fraction2._denominator)
      {
            fraction3._denominator = _denominator;
            fraction3._numerator = _numerator - fraction2._numerator;
      }
      else
      {
            fraction3._denominator = _denominator * fraction2._denominator;
            fraction3._numerator = _numerator * fraction2._denominator - _denominator * fraction2._numerator;
      }
      return fraction3;
}

fraction& fraction::operator *(const fraction& fraction2)
{}

fraction& fraction::operator/(const fraction& fraction2)
{}