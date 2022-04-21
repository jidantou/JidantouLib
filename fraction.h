#pragma once

#include <iostream>

namespace Jidantou
{
      class fraction
      {
      private:
            int64_t _numerator;
            int64_t _denominator;

            void reduction();

      public:
            fraction();
            fraction(const int64_t numerator, const int64_t denominator);
            fraction(const fraction& fraction1);
            ~fraction();

            friend ostream& operator<<(ostream& out,const fraction fraction1);
            
            fraction& operator +(const fraction& fraction2);
            fraction& operator -(const fraction& fraction2);
            fraction& operator *(const fraction& fraction2);
            fraction& operator /(const fraction& fraction2);
            fraction& operator +=(const fraction& fraction2);
            fraction& operator -=(const fraction& fraction2);
            fraction& operator *=(const fraction& fraction2);
            fraction& operator /=(const fraction& fraction2);
      };

}