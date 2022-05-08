#pragma once

#include <iostream>
using std::ostream;
using std::istream;

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

            /*    Special situation
            NaN(Not a Number) : _numerator == 0 && _denominator == 0
            Infinity : _numerator != 0 && _denominator == 0
            _sign == 0 for positive , _sign == 1 for negative
            */

            void reduction();

      public:
            fraction();
            fraction(const double num);
            fraction(const int64_t num);
            fraction(const uint64_t numerator, const uint64_t denominator, const bool sign = 0);
            fraction(const fraction& fraction1);
            ~fraction();

            friend ostream& operator<<(ostream& output, const fraction fraction1);
            friend istream& operator>>(istream& input, fraction fraction1);

            double to_double();
            int64_t to_int64();

            bool isNaN();
            bool isInfinify();
            
            void reciprocal();
            fraction operator -();
            fraction operator +(const fraction& fraction2);
            fraction operator -(const fraction& fraction2);
            fraction operator *(const fraction& fraction2);
            fraction operator /(const fraction& fraction2);
            fraction& operator +=(const fraction& fraction2);
            fraction& operator -=(const fraction& fraction2);
            fraction& operator *=(const fraction& fraction2);
            fraction& operator /=(const fraction& fraction2);

            bool operator < (fraction fraction1);
            bool operator > (fraction fraction1);
            bool operator <= (fraction fraction1);
            bool operator >= (fraction fraction1);
            bool operator != (fraction fraction1);
            bool operator == (fraction fraction1);
      };

}