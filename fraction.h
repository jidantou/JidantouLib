#pragma once

#include <iostream>
using std::istream;
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

        /*    Special situation
        NaN(Not a Number) : _numerator == 0 && _denominator == 0
        Infinity : _numerator != 0 && _denominator == 0
        _sign == 0 for positive , _sign == 1 for negative
        */

        // reduction of a fraction
        void reduction();

    public:
        // default constructor
        fraction();

        // Not recommended, because it maybe overflow and cause unexpected error 
        // turn double to fraction
        __attribute__((deprecated)) fraction(const double num);

        // turn int8_t to fraction
        fraction(const int8_t num);

        // turn int16_t to fraction
        fraction(const int16_t num);

        // turn int32_t to fraction
        fraction(const int32_t num);

        // turn int64_t to fraction
        fraction(const int64_t num);

        // Highly recommened
        // set numerator, denominator, and sign(default 0)
        fraction(const uint64_t numerator, const uint64_t denominator, const bool sign = 0);

        // copy constructor
        fraction(const fraction &fraction1);

        // destructor
        ~fraction();

        // format output, numerator/denominator
        friend ostream &operator<<(ostream &output, const fraction fraction1);
        friend istream &operator>>(istream &input, fraction &fraction1);

        bool isNaN() const;
        bool isInfinify() const;

        void reciprocal();
        operator double() const;
        operator int64_t() const;
        fraction operator-() const;
        fraction operator+(const fraction &fraction2) const;
        fraction operator-(const fraction &fraction2) const;
        fraction operator*(const fraction &fraction2) const;
        fraction operator/(const fraction &fraction2) const;
        fraction &operator+=(const fraction &fraction2);
        fraction &operator-=(const fraction &fraction2);
        fraction &operator*=(const fraction &fraction2);
        fraction &operator/=(const fraction &fraction2);

        bool operator<(const fraction fraction1) const;
        bool operator>(const fraction fraction1) const;
        bool operator<=(const fraction fraction1) const;
        bool operator>=(const fraction fraction1) const;
        bool operator!=(const fraction fraction1) const;
        bool operator==(const fraction fraction1) const;
    };

}