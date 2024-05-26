#pragma once
#include <iostream>
#include <type_traits>

template <typename... Args>
constexpr bool is_copy_constructible = (std::is_constructible<Args>::value && ...);

template <size_t SIZE, size_t ALLOCATED>
constexpr bool is_enough_memory = SIZE >= ALLOCATED;

template <typename... Args>
constexpr size_t get_size = sizeof...(Args) == 0 ? 0 : (sizeof(Args) + ...);

template <typename T>
constexpr char* tiny_allocator(char* ptr, T&& arg) {
    using T_WITHOUT_REF = typename std::remove_reference<T>::type;
    ::new(ptr) T_WITHOUT_REF(std::forward<T>(arg));
    ptr += sizeof(T);
    return ptr;
}

template <size_t SIZE, typename... Types>
void allocate(void* memory, Types&&... args) requires (is_copy_constructible<Types...>,
                                                       is_enough_memory<SIZE, get_size<Types...>> ) {
    auto* ptr = static_cast<char*>(memory);
    ((ptr = tiny_allocator(ptr, std::forward<Types>(args))), ...);
}
