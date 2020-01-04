//
// Created by alex on 1/3/20.
//

#ifndef PRIMEFINITEFIELD_POLYNOMIAL_H
#define PRIMEFINITEFIELD_POLYNOMIAL_H

#include <vector>
#include <iostream>
#include <initializer_list>
#include "FFp.h"


namespace ffpp {

    using std::vector;

    template <typename T>
    class Polynomial {
        vector<T> _data;

    public:
        Polynomial() = default;

        explicit Polynomial(std::size_t N): _data(std::vector<T>(N)) {}

        explicit Polynomial(vector<T> data): _data(data) {}

        Polynomial(std::initializer_list<T> l): _data(l) {}

        size_t degree() const { return _data.size() - 1; }

        T at(size_t i) const { return _data[i]; } //dodaj proveru/zastitu!

        auto data() const { return _data.data(); }

        Polynomial operator+ () const {
            return *this;
        }

        Polynomial operator- ()
        {
            std::vector<T> b;
            b.reserve(_data.size());
            for(auto aa : _data)
                b.push_back(-aa);

            return Polynomial(b);
        }

        friend Polynomial operator+(Polynomial a, Polynomial b) {

            std::size_t len = 0;
            if (a._data.size() > b._data.size()) {
                len = a._data.size();
                b._data.resize(len);
            } else {
                len = b._data.size();
                a._data.resize(len);
            }

            std::vector<T> res(len);
            for (std::size_t i = 0; i < len; ++i)
                res[i] = a._data[i] + b._data[i];

            return Polynomial(res);
        }

        friend Polynomial operator+=(Polynomial &a, const Polynomial &b) {
            return a = a + b;
        }

        friend Polynomial operator+(Polynomial a, const T &b) {
            for (auto &aa : a._data) {
                aa += b;
            }

            return a;
        }

        friend Polynomial operator+(const T &b, const Polynomial &a) {
            return a + b;
        }

        friend Polynomial operator+=(Polynomial &a, const T &b) {
            return a = a + b;
        }

        friend Polynomial operator-(Polynomial a, Polynomial b) {
            std::size_t len = 0;
            if (a._data.size() > b._data.size()) {
                len = a._data.size();
                b._data.resize(len);
            } else {
                len = b._data.size();
                a._data.resize(len);
            }

            std::vector<T> res(len);
            for (std::size_t i = 0; i < len; ++i)
                res[i] = a._data[i] - b._data[i];

            return Polynomial(res);
        }

        friend Polynomial operator-=(Polynomial &a, const Polynomial &b) {
            return a = a - b;
        }

        friend Polynomial operator-(Polynomial a, const T &b) {
            for (auto &aa : a._data) {
                aa -= b;
            }

            return a;
        }

        friend Polynomial operator-(const T &b, const Polynomial &a) {
            return a - b;
        }

        friend Polynomial operator-=(Polynomial &a, const T &b) {
            return a = a - b;
        }

        //Convolution = polynomial multiplication
        friend Polynomial operator*(Polynomial &a, const Polynomial &b) {

            std::size_t length = a._data.size() + b._data.size() - 1;

            std::vector<T> res(length);

            for (std::size_t i = 0; i < a._data.size(); ++i) {
                for (std::size_t j = 0; j < b._data.size(); ++j) {
                    res[i + j] += a._data[i] * b._data[j];
                }
            }

            return Polynomial(res);
        }

        //Convolution = polynomial multiplication
        friend Polynomial operator*=(Polynomial &a, const Polynomial &b) {
            return a = a * b;
        }

        friend Polynomial operator*(Polynomial a, const T &b) {
            for (auto &aa : a._data) {
                aa *= b;
            }

            return a;
        }

        friend Polynomial operator*(const T &b, const Polynomial &a) {
            return a * b;
        }

        friend Polynomial operator*=(Polynomial &a, const T &b) {
            return a = a * b;
        }

        friend void poly_div(Polynomial a, Polynomial b, Polynomial &res, Polynomial &mod) {
            res = Polynomial(std::vector<T>(1));
            mod = a;

            Polynomial tmp;
            std::size_t size;

            if (a._data.size() < b._data.size())
                return;
            else {
                do {
                    size = a._data.size() - b._data.size() + 1;
                    tmp = Polynomial(std::vector<T>(size));
                    *(tmp._data.rbegin()) = (*(a._data.rbegin())) / (*(b._data.rbegin())); // monic polynomial
                    res += tmp;
                    tmp *= b;
                    a -= tmp;

                    while ((*(a._data.rbegin())) == 0 && a._data.size() > 1)
                        a._data.pop_back();

                } while (a._data.size() >= b._data.size());
            }
            mod = a;
            //return res;
        }

        friend Polynomial operator/(const Polynomial &a, const Polynomial &b) {
            Polynomial res;
            Polynomial mod;

            poly_div(a, b, res, mod);

            return res;
        }

        friend Polynomial operator/=(Polynomial &a, const Polynomial &b) {
            return a = a / b;
        }


        friend Polynomial operator/(Polynomial a, const T &b) {
            for (auto &aa : a._data) {
                aa /= b;
            }

            return a;
        }

        friend Polynomial operator/=(Polynomial &a, const T &b) {
            return a = a / b;
        }


        friend Polynomial operator%(const Polynomial &a, const Polynomial &b) {
            Polynomial res;
            Polynomial mod;

            poly_div(a, b, res, mod);

            return mod;
        }

        friend Polynomial operator%=(Polynomial &a, const Polynomial &b) {
            return a = a % b;
        }


        friend Polynomial operator%(Polynomial a, const T &b) {
            for (auto &aa : a._data) {
                aa %= b;
            }

            return a;
        }

        friend Polynomial operator%=(Polynomial &a, const T &b) {
            return a = a % b;
        }

        friend T operator>>(Polynomial &a, int b) {
            T carry;
            std::size_t length = a._data.size() - 1;

            for (std::size_t i = 0; i < b; ++i) {
                carry = a._data[length];
                for (std::size_t j = length; j > 0; --j) {
                    a._data[j] = a._data[j - 1];
                }
                a._data[0] = 0;
            }

            return carry;
        }

        friend T operator<<(Polynomial &a, int b) {
            T carry;
            std::size_t length = a._data.size() - 1;

            for (std::size_t i = 0; i < b; ++i) {
                carry = a._data[0];
                for (std::size_t j = 0; j < length; ++j) {
                    a._data[j] = a._data[j + 1];
                }
                a._data[length] = 0;
            }

            return carry;
        }

        friend std::ostream &operator<<(std::ostream &output, const Polynomial &a) {
            /*for (std::size_t i = a.size() - 1; i > 0; --i) {
                output << a[i] << "x^" << i << " + ";
            }
            output << a[0];*/

            for(auto x : a._data)
                output << x << " ";

            return output;
        }

    };

    template <int p>
    using PrimePolynomial = Polynomial<FFp<p> >;

} //::ffpp


#endif //PRIMEFINITEFIELD_POLYNOMIAL_H
