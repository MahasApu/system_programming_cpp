# The 6th NSTT:

Implement a class to work with `square matrices`.
In this class you should have:

- Fully correct work with memory (ctr/dstr/assignment etc)

- Constructor from 1D `std::vector `of doubles (elements of it
will be placed on main diagonal)

- `explicit` type conversion operator to double (returns `sum` of
all elements, or `det` if you really want)

- Overloaded operators for +, +=, *, *= (for 2 matrices and
with scalar), ==, !=

- Double indexing! Matrix m(10); m[5][5] = 42;