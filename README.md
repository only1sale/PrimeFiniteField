## Finite Field 

This class represents an implementation of a finite field over prime p (i.e. integer modulo $$p$$: $$\mathbb{Z}_p$$). It was written for use with [Eigen3](http://eigen.tuxfamily.org/index.php?title=Main_Page) library for linear algebra, so `GenericNumTraits` is defined for this class. 

### Tests

Unit tests are written using [catch2](https://github.com/catchorg/Catch2) testing framework, which is included in this project.  

### Use

To define a new field over prime p use:

```c++
const int p = 5;
FFp<p> x; //x = 0
FFp<p> y(4); // y = 4
FFp<p> z;

z = x + y;
z = x - y;
z = x * y;
z = x / y;

```

### To do:

1. Table of multiplicative inverses is generated using an exhaustive search (with complexity $$\mathcal{O}(p^2)$$). Instead of an exhaustive search an extended Euclid algorithm can be used to generate all multiplicative inverses. As this library is intended for use with relatively small  $$p$$ values, this is not a big priority. 

2. Assertion `isPrime<p>()`is done only in debug mode. 