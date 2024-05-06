#include <iostream>
#include <type_traits>

using false_t = std::integral_constant<bool, false>; 
using true_t = std::integral_constant<bool, true>;

template <size_t x, size_t y>
struct has_divisor: std::conditional_t<(x % y == 0), true_t, has_divisor<x, y + 1>> { };

template <size_t x>
struct has_divisor<x, x>: false_t { };

template <size_t n>
struct is_prime: std::conditional_t<has_divisor<n, 2>{}, false_t, true_t> { };

template <size_t n>
struct get_prime: std::conditional_t<is_prime<n>{}, std::integral_constant<size_t, n>, get_prime<n + 1>> { };

template <size_t n>
struct prime: get_prime<prime<n - 1>{} + 1> { };

template <>
struct prime<1>: std::integral_constant<size_t, 2> { };
