#ifndef _FRACTION_H_
#define _FRACTION_H_

namespace Jidantou
{
      template <class Type>
      class fraction
      {
      private:
            Type _numerator;
            Type _denominator;


      public:
            fraction();
            fraction(const Type numerator, const Type denominator);
            fraction(const fraction<Type>& fraction1);
            ~fraction();

            fraction<Type>& operator +(const fraction<Type>& fraction2);
            fraction<Type>& operator -(const fraction<Type>& fraction2);
            fraction<Type>& operator *(const fraction<Type>& fraction2);
            fraction<Type>& operator /(const fraction<Type>& fraction2);
      };
}

#endif