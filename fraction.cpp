#include "fraction.h"

using std::ostream;
using std::istream;

namespace Jidantou
{
    fraction::fraction()
    {
        _numerator = 0;
        _denominator = 1;
        _sign = 0;
    }

    fraction::fraction(const double num)
    {
        // cout << hex;
        int64_t temp;
        uint16_t exp;

        _sign = num < 0 ? 1 : 0;
        temp = *((int64_t *)&num);
        // cout << "temp:0x" << temp << endl;

        exp = temp >> 52;
        exp &= 0x07FF;
        // cout << hex << "exp:0x" << exp << endl;

        _numerator = temp & 0x000FFFFFFFFFFFFF;
        // cout << hex << "_numerator:0x" << temp << endl;

        switch (exp)
        {
        case 0x0000:
            // cout << "case 0x0000" << endl;
            if (_numerator == 0)
                _denominator = 1;
            else
                _denominator = 0x0010000000000000;
            break;

        case 0xFFFF:
            // cout << "case 0xFFFF" << endl;
            if (_numerator == 0)
            {
                _denominator = 0;
                _numerator = 1;
            }
            else
            {
                _numerator = 0;
                _denominator = 0;
            }
            break;

        default:
            // cout << "default" << endl;
            _denominator = 0x0010000000000000;
            _denominator = exp < 1023 ? _denominator << 1023 - exp : _denominator >> exp - 1023;
            // cout << hex << "0x" << _denominator << endl;
            _numerator |= 0x0010000000000000;
            break;
        }
        // cout << "switch finish" << endl;
        reduction();
        // cout << dec;
    }

    fraction::fraction(const int8_t num)
    {
        _sign = num < 0 ? 1 : 0;
        _numerator = num < 0 ? -num : num;
        _denominator = 1;
    }

    fraction::fraction(const int16_t num)
    {
        _sign = num < 0 ? 1 : 0;
        _numerator = num < 0 ? -num : num;
        _denominator = 1;
    }

    fraction::fraction(const int32_t num)
    {
        _sign = num < 0 ? 1 : 0;
        _numerator = num < 0 ? -num : num;
        _denominator = 1;
    }

    fraction::fraction(const int64_t num)
    {
        _sign = num < 0 ? 1 : 0;
        _numerator = num < 0 ? -num : num;
        _denominator = 1;
    }

    fraction::fraction(const uint64_t numerator, const uint64_t denominator, const bool sign)
    {
        _sign = sign;
        _numerator = numerator;
        _denominator = denominator;

        reduction();
    }

    fraction::fraction(const fraction &fraction1)
    {
        _numerator = fraction1._numerator;
        _denominator = fraction1._denominator;
        _sign = fraction1._sign;
    }

    fraction::~fraction() {}

    ostream &operator<<(ostream &output, const fraction fraction1)
    {
        if (fraction1._sign != 0)
            output << "-";

        output << fraction1._numerator << "/" << fraction1._denominator;
        return output;
    }

    istream &operator>>(istream &input, fraction &fraction1)
    {
        char c;
        int64_t numerator, denominator;

        input >> numerator >> c;

        if (c == '/')
        {
            input >> denominator;
        }
        else
            denominator = 1;

        fraction1.reduction();

        if (numerator == 0)
            fraction1._sign = 0;
        else
            fraction1._sign = (numerator < 0 && denominator < 0) || (numerator > 0 && denominator > 0) ? 0 : 1;

        fraction1._numerator = numerator >= 0 ? numerator : -numerator;
        fraction1._denominator = denominator >= 0 ? denominator : -denominator;

        return input;
    }

    inline bool fraction::isNaN() const { return _numerator == 0 && _denominator == 0; }

    inline bool fraction::isInfinify() const { return _numerator != 0 && _denominator == 0; }

    inline void fraction::reduction()
    {
        if (_denominator == 0 || _numerator == 0)
            return;
        else
        {
            uint64_t a, b, c;

            while (_numerator & 0x01 == 0 && _denominator & 0x01 == 0)
            {
                _numerator >>= 1;
                _denominator >>= 1;
            }

            a = _numerator > _denominator ? _numerator : _denominator;
            b = _numerator > _denominator ? _denominator : _numerator;
            // cout << "a:" << a << endl;
            // cout << "b:" << b << endl;

            /*
            更相减损术
            while (a != b)
            {
                c = a - b;
                a = c > b? c: b;
                b = c > b? b: c;
                 cout << "a:" << a << "b:" << b << endl;
            }
            */

            // Rolling phase division
            c = a % b;
            // cout << "c:" << c << endl;
            while (c != 0)
            {
                a = b;
                b = c;
                c = a % b;
                // cout << "c:" << c << endl;
            }

            _numerator /= b;
            _denominator /= b;
        }
    }

    void fraction::reciprocal()
    {
        int64_t temp;
        temp = _numerator;
        _numerator = _denominator;
        _denominator = temp;
    }

    fraction fraction::operator-() const
    {
        fraction fraction1;
        fraction1._numerator = _numerator;
        fraction1._denominator = _denominator;
        fraction1._sign = ~_sign;

        return fraction1;
    }

    fraction fraction::operator+(const fraction &fraction2) const
    {
        fraction fraction3;

        if (_denominator == 0 || fraction2._denominator == 0)
        {
            fraction3._numerator = 0;
            fraction3._denominator = 0;
            fraction3._sign = 0;

            return fraction3;
        }
        else if (_denominator == fraction2._denominator)
        {
            fraction3._denominator = _denominator;
            fraction3._numerator = _sign ^ fraction2._sign == 0 ? _numerator + fraction2._numerator : (_numerator > fraction2._numerator) ? _numerator - fraction2._numerator
                                                                                                                                          : fraction2._numerator - _numerator;
            fraction3._sign = fraction3._numerator == 0 ? 0 : (_numerator > fraction2._numerator ? _sign : fraction2._sign);
        }
        else
        {
            fraction3._denominator = _denominator * fraction2._denominator;
            fraction3._numerator = _sign ^ fraction2._sign == 0 ? _numerator * fraction2._denominator + fraction2._numerator * _denominator : (_numerator * fraction2._denominator > fraction2._numerator * _denominator) ? _numerator * fraction2._denominator - fraction2._numerator * _denominator
                                                                                                                                                                                                                          : fraction2._numerator * _denominator - _numerator * fraction2._denominator;
            fraction3._sign = fraction3._numerator == 0 ? 0 : (_numerator * fraction2._denominator > fraction2._numerator * _denominator ? _sign : fraction2._sign);
        }

        fraction3.reduction();

        return fraction3;
    }

    fraction fraction::operator-(const fraction &fraction2) const
    {
        fraction fraction3;

        if (_denominator == 0 || fraction2._denominator == 0)
        {
            fraction3._numerator = 0;
            fraction3._denominator = 0;
            fraction3._sign = 0;

            return fraction3;
        }
        else if (_denominator == fraction2._denominator)
        {
            fraction3._denominator = _denominator;
            fraction3._numerator = _sign ^ fraction2._sign != 0 ? _numerator + fraction2._numerator : (_numerator > fraction2._numerator) ? _numerator - fraction2._numerator
                                                                                                                                          : fraction2._numerator - _numerator;
            fraction3._sign = fraction3._numerator == 0 ? 0 : (_numerator > fraction2._numerator ? _sign : fraction2._sign);
        }
        else
        {
            fraction3._denominator = _denominator * fraction2._denominator;
            fraction3._numerator = _sign ^ fraction2._sign != 0 ? _numerator * fraction2._denominator + fraction2._numerator * _denominator : (_numerator * fraction2._denominator > fraction2._numerator * _denominator) ? _numerator * fraction2._denominator - fraction2._numerator * _denominator
                                                                                                                                                                                                                          : fraction2._numerator * _denominator - _numerator * fraction2._denominator;
            fraction3._sign = fraction3._numerator == 0 ? 0 : (_numerator * fraction2._denominator > fraction2._numerator * _denominator ? _sign : fraction2._sign);
        }

        fraction3.reduction();

        return fraction3;
    }

    fraction fraction::operator*(const fraction &fraction2) const
    {
        fraction fraction3;

        if (_denominator == 0 || fraction2._denominator == 0)
        {
            fraction3._numerator = 0;
            fraction3._denominator = 0;
            fraction3._sign = 0;

            return fraction3;
        }

        fraction3._sign = _sign ^ fraction2._sign == 0 ? 0 : 1;
        fraction3._numerator = _numerator * fraction2._numerator;
        fraction3._denominator = _denominator * fraction2._denominator;

        return fraction3;
    }

    fraction fraction::operator/(const fraction &fraction2) const
    {
        fraction fraction3;

        if (_denominator == 0 || fraction2._denominator == 0)
        {
            fraction3._numerator = 0;
            fraction3._denominator = 0;
            fraction3._sign = 0;
        }

        fraction3._sign = _sign ^ fraction2._sign == 0 ? 0 : 1;
        fraction3._numerator = _numerator * fraction2._denominator;
        fraction3._denominator = _denominator * fraction2._numerator;

        return fraction3;
    }

    fraction &fraction::operator+=(const fraction &fraction2)
    {
        if (_denominator == 0 || fraction2._denominator == 0)
        {
            _numerator = 0;
            _denominator = 0;
            _sign = 0;

            return *this;
        }

        if (_denominator == fraction2._denominator)
        {
            _numerator = _sign ^ fraction2._sign == 0 ? _numerator + fraction2._numerator : (_numerator > fraction2._numerator) ? _numerator - fraction2._numerator
                                                                                                                                : fraction2._numerator - _numerator;
            _sign = _numerator == 0 ? 0 : (_numerator > fraction2._numerator ? _sign : fraction2._sign);
        }
        else
        {
            _denominator = _denominator * fraction2._denominator;
            _numerator = _sign ^ fraction2._sign == 0 ? _numerator * fraction2._denominator + fraction2._numerator * _denominator : (_numerator * fraction2._denominator > fraction2._numerator * _denominator) ? _numerator * fraction2._denominator - fraction2._numerator * _denominator
                                                                                                                                                                                                                : fraction2._numerator * _denominator - _numerator * fraction2._denominator;
            _sign = _numerator == 0 ? 0 : (_numerator * fraction2._denominator > fraction2._numerator * _denominator ? _sign : fraction2._sign);
        }

        reduction();

        return *this;
    }

    fraction &fraction::operator-=(const fraction &fraction2)
    {
        if (_denominator == 0 || fraction2._denominator == 0)
        {
            _numerator = 0;
            _denominator = 0;
            _sign = 0;

            return *this;
        }

        if (_denominator == fraction2._denominator)
        {
            _numerator = _sign ^ fraction2._sign != 0 ? _numerator + fraction2._numerator : (_numerator > fraction2._numerator) ? _numerator - fraction2._numerator
                                                                                                                                : fraction2._numerator - _numerator;
            _sign = _numerator == 0 ? 0 : (_numerator > fraction2._numerator ? _sign : fraction2._sign);
        }
        else
        {
            _denominator = _denominator * fraction2._denominator;
            _numerator = _sign ^ fraction2._sign != 0 ? _numerator * fraction2._denominator + fraction2._numerator * _denominator : (_numerator * fraction2._denominator > fraction2._numerator * _denominator) ? _numerator * fraction2._denominator - fraction2._numerator * _denominator
                                                                                                                                                                                                                : fraction2._numerator * _denominator - _numerator * fraction2._denominator;
            _sign = _numerator == 0 ? 0 : (_numerator * fraction2._denominator > fraction2._numerator * _denominator ? _sign : fraction2._sign);
        }

        reduction();

        return *this;
    }

    fraction &fraction::operator*=(const fraction &fraction2)
    {
        if (_denominator == 0 || fraction2._denominator == 0)
        {
            _numerator = 0;
            _denominator = 0;
            _sign = 0;

            return *this;
        }

        _sign = _sign ^ fraction2._sign == 0 ? 0 : 1;
        _numerator = _numerator * fraction2._numerator;
        _denominator = _denominator * fraction2._denominator;

        return *this;
    }

    fraction &fraction::operator/=(const fraction &fraction2)
    {
        if (_denominator == 0 || fraction2._denominator == 0)
        {
            _numerator = 0;
            _denominator = 0;
            _sign = 0;

            return *this;
        }

        _sign = _sign ^ fraction2._sign == 0 ? 0 : 1;
        _numerator = _numerator * fraction2._denominator;
        _denominator = _denominator * fraction2._numerator;

        return *this;
    }

    bool fraction::operator<(const fraction fraction1) const
    {
        if (_sign > fraction1._sign)
            return true;
        else if (_sign < fraction1._sign)
            return false;
        else if (_denominator == fraction1._denominator)
            return _numerator < fraction1._numerator;
        else
            return _numerator * fraction1._denominator < fraction1._numerator * _denominator;
    }

    bool fraction::operator>(const fraction fraction1) const
    {
        if (_sign < fraction1._sign)
            return true;
        else if (_sign > fraction1._sign)
            return false;
        else if (_denominator == fraction1._denominator)
            return _numerator > fraction1._numerator;
        else
            return _numerator * fraction1._denominator > fraction1._numerator * _denominator;
    }

    bool fraction::operator<=(const fraction fraction1) const
    {
        if (_sign > fraction1._sign)
            return true;
        else if (_sign < fraction1._sign)
            return false;
        else if (_denominator == fraction1._denominator)
            return _numerator <= fraction1._numerator;
        else
            return _numerator * fraction1._denominator <= fraction1._numerator * _denominator;
    }

    bool fraction::operator>=(const fraction fraction1) const
    {
        if (_sign < fraction1._sign)
            return true;
        else if (_sign > fraction1._sign)
            return false;
        else if (_denominator == fraction1._denominator)
            return _numerator >= fraction1._numerator;
        else
            return _numerator * fraction1._denominator >= fraction1._numerator * _denominator;
    }

    bool fraction::operator!=(const fraction fraction1) const
    {
        return (_denominator != fraction1._denominator) || (_numerator != fraction1._numerator) || (_sign != fraction1._sign);
    }

    bool fraction::operator==(const fraction fraction1) const
    {
        return (_numerator == fraction1._numerator) &&
               (_denominator == fraction1._denominator) &&
               (_sign == fraction1._sign);
    }

}