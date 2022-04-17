#include <cmath>
#include "fraction.h"

using namespace std;
using namespace Jidantou;

template <class Type>
inline fraction<Type>::fraction()
{
}

template <class Type>
inline fraction<Type>::fraction(Type numerator, Type denominator)
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

template <class Type>
inline fraction<Type>::fraction(const fraction<Type>& fraction1)
{
      _numerator = fraction1._numerator;
      _denominator = fraction1._denominator;
}

template <class Type>
fraction<Type>::~fraction()
{}

template <class Type>
fraction<Type>& fraction<Type>::operator +(const fraction<Type>& fraction2)
{
      fraction<Type> fraction3;

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

template <class Type>
fraction<Type>& fraction<Type>::operator -(const fraction<Type>& fraction2)
{
      fraction<Type> fraction3;

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

template <class Type>
fraction<Type>& fraction<Type>::operator *(const fraction<Type>& fraction2)
{}

template <class Type>
fraction<Type>& fraction<Type>::operator/(const fraction<Type>& fraction2)
{}