#pragma once

#include <type_traits>

template <typename... Args>
constexpr bool is_copy_constructible(){
    return (std::is_constructible<Args, const Args&>::value && ...);
} 

template <size_t SIZE, size_t ALLOCATED>
constexpr bool is_enough_memory() { return SIZE >= ALLOCATED; }

template <typename... Args>
constexpr size_t get_size() {
    if (sizeof...(Args) == 0) return 0;
    return (sizeof(Args) + ...);
}

template <size_t SIZE, typename... Types>
void allocate(void* memory, Types... args) {
    static_assert(is_copy_constructible<Types...>());
    constexpr size_t allocated_mem = get_size<Types...>();
    static_assert(is_enough_memory<SIZE, allocated_mem>);

    // TODO: use placement new
    auto* ptr = static_cast<char*>(memory);
    std::ptrdiff_t i = 0;
    (::new(ptr++) Types(), ...);
}