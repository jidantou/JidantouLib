#pragma once

#include <iostream>
using std::ostream;

namespace Jidantou
{
      class fraction
      {
      private:

            // numerator, must be positive
            uint64_t _numerator;

            // denominator, must be positive
            uint64_t _denominator;

            // 0 for positive, 1 for negative
            bool _sign;

            void reduction();

      public:
            fraction();
            fraction(double data_double);
            fraction(int64_t data_int);
            fraction(const uint64_t numerator, const uint64_t denominator, const bool sign = 0);
            fraction(const fraction& fraction1);
            ~fraction();

            friend ostream& operator<<(ostream& out,const fraction fraction1);

            double to_double();
            int64_t to_int64();
            
            void reciprocal();
            fraction& operator -();
            fraction operator +(const fraction& fraction2);
            fraction operator -(const fraction& fraction2);
            fraction operator *(const fraction& fraction2);
            fraction operator /(const fraction& fraction2);
            fraction& operator +=(const fraction& fraction2);
            fraction& operator -=(const fraction& fraction2);
            fraction& operator *=(const fraction& fraction2);
            fraction& operator /=(const fraction& fraction2);
      };

}