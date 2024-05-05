#include <iostream>
#include <vector>
#include <type_traits>


using false_t = std::integral_constant<bool, false>; 
using true_t = std::integral_constant<bool, true>; 

template <size_t n1, size_t n2>
struct is_prime_loop: std::conditional_t<(n1 % n2 != 0), is_prime_loop<n1, n2 - 1>, false_t> { };

template <size_t n1>
struct is_prime_loop<n1, 1>: true_t { };

template <size_t n>
struct is_prime: is_prime_loop<n, n - 1> { };

template <size_t n>
struct get_prime: std::conditional_t<is_prime<n>::value, std::integral_constant<size_t, n>, get_prime<n + 1>> { };

template <size_t n>
struct prime: get_prime<prime<n - 1>::value + 1> { };

template <>
struct prime<1>: std::integral_constant<size_t, 2> { };
