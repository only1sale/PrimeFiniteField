//
// Created by alex on 1/3/20.
//

#ifndef PRIMEFINITEFIELD_FFP_H
#define PRIMEFINITEFIELD_FFP_H

#include <iostream>
#include <cmath>
#include <array>
#include <Eigen/Core>


namespace ffpp {

    template <unsigned num>
    constexpr bool isPrime() {
        if(num <= 3) // 2 and 3 are prime
            return num > 1; // 1 is not prime by definition

        if(num % 2 == 0 || num % 3 == 0) // eliminate multiples of 2 and 3
            return false;

        unsigned t = sqrt(num);

        if(t*t == num)
            return false;

        for(size_t i = 5; i <= t; i += 6) //start from 5 with a step of 6, until sqrt(num)
            if( num % i == 0 || num % (i+2) == 0)
                return false;

        return true;
    }

    template<int p = 2>
    class FFp {

#ifndef NDEBUG
        static_assert(isPrime<p>(), "Error: Not a prime!");
#endif

        static int mod(int a) { return (p + (a % p)) % p; }

        static std::array<unsigned, p> initTable() {
            std::array<unsigned, p> LTMP = {};
            LTMP[0] = 0;
            LTMP[1] = 1;

            for (unsigned i = 2; i < p; ++i) {
                for(unsigned j = 2; j < p; ++j)
                    if( mod(i*j) == 1) {
                        LTMP[i] = j;
                        break;
                    }
            }

            return LTMP;
        }

        static inline const std::array<unsigned, p> pMinv = initTable(); // prime multiplicative inverse
        int _val;

    public:

        static int order() {
            return p;
        }

        static void printTable()
        {
            for(std::size_t i = 0; i < p; ++i)
                std::cout << i <<"^(-1) = " << pMinv[i] << std::endl;
        }

        FFp(int a = 0) : _val(mod(a)) {}

        explicit operator int() const { return _val; }
        explicit operator bool()const { return _val != 0; }

        FFp minv() const {
            int tmp = pMinv[_val];
            return FFp(tmp);
        }

        FFp pow(int pp) const
        {
            auto tmp = _val;
            if(pp < 0) {
                pp = abs(pp);
                tmp = mod(-tmp);
            }

            return FFp(static_cast<int>(std::pow(tmp,pp)));
        }

        friend FFp operator+ (const FFp &a, const FFp &b) {
            return FFp(a._val + b._val);
        }

        friend FFp operator- (const FFp &a, const FFp &b) {
            return FFp(a._val - b._val);
        }

        friend FFp operator* (const FFp &a, const FFp &b) {
            return FFp(a._val * b._val);
        }

        friend FFp operator/ (const FFp &a, const FFp &b) {
            assert(b != 0 && "Divide by zero!");
            return a * (b.minv());
        }

        friend FFp operator+= (FFp &a, const FFp &b) {
            return a = a + b;
        }

        friend FFp operator-= (FFp &a, const FFp &b) {
            return a = a - b;
        }

        friend FFp operator*= (FFp &a, const FFp &b) {
            return a = a * b;
        }

        friend FFp operator/= (FFp &a, const FFp &b) {
            return a = a / b;
        }

        friend FFp operator% (const FFp &a, const FFp &b) {
            return a - b * (a / b);
        }

        friend FFp operator%= (FFp &a, const FFp &b) {
            return a = a % b;
        }

        friend bool operator== (const FFp &a, const FFp &b) {
            return a._val == b._val;
        }

        friend bool operator!= (const FFp &a, const FFp &b) {
            return !(a == b);
        }

        friend bool operator> (const FFp &a, const FFp &b) {
            return a._val > b._val;
        }

        friend bool operator< (const FFp &a, const FFp &b) {
            return a._val < b._val;
        }

        friend bool operator>= (const FFp &a, const FFp &b) {
            return !(a < b);
        }

        friend bool operator<= (const FFp &a, const FFp &b) {
            return !(a > b);
        }

        FFp operator+ () const {
            return *this;
        }

        FFp operator- () {
            return FFp(-_val);
        }

        FFp operator++ () {
            return (*this += FFp(1));
        }

        const FFp operator++(int) {
            FFp tmp = *this;
            *this += FFp(1);
            return tmp;
        }

        FFp operator-- () {
            return (*this -= FFp(1));
        }

        const FFp operator--(int) {
            FFp tmp = *this;
            *this -= FFp(1);
            return tmp;
        }

        friend std::ostream & operator<< (std::ostream &out, const FFp &a) {
            out << a._val;
            return out;
        }

        friend std::istream & operator>> (std::istream &in, FFp &a) {
            int tmp;
            in >> tmp;
            a._val = mod(tmp);
            return in;
        }

    };

    using GF2 = FFp<2>;

} //::ffpp


namespace Eigen {

    using ffpp::FFp;

    template<int p> struct NumTraits<FFp<p>> : GenericNumTraits<FFp<p>> {
        typedef FFp<p> Real;
        typedef int Nested;
        typedef FFp<p> NonInteger;
        typedef int Literal;

        enum {
            IsComplex = 0,
            IsInteger = 1,
            IsSigned = 0,
            RequireInitialization = 0,
            ReadCost = 1,
            AddCost = 2,
            MulCost = 2
        };

        static Real epsilon() {
            return 1;
        }

        static Real dummy_precision() {
            return 1;
        }

        static FFp<p> highest() {
            return ffpp::FFp<p>::order();
        }

        static FFp<p> lowest() {
            return 0;
        }

        static int digits10() {
            return 0;
        }
    };

    template<int p>
    inline const FFp<p> pow(const FFp<p>& a, int pp) { return a.pow(pp); }

    template<int p>
    inline FFp<p> abs(const FFp<p>&  x)  { return x; }

    template<int p>
    inline FFp<p> abs2(const FFp<p>& x)  { return x*x; }

} //Eigen::



#endif //PRIMEFINITEFIELD_FFP_H
