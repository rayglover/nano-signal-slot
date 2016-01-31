#ifndef NANO_TUPLE_HPP
#define NANO_TUPLE_HPP

#include <tuple>

namespace Nano {

template <typename F, typename Tuple, size_t... I>
auto apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>) {
    return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
}

template <typename T, typename F, typename Tuple, size_t... I>
auto apply_impl(T* this_ptr, F&& f, Tuple&& t, std::index_sequence<I...>) {
    return ((this_ptr->*std::forward<F>(f))(std::get<I>(std::forward<Tuple>(t))...));
}

/**
 * Applies a tuple to a function.
 *
 * From C++ standard proposal [N3915](http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n3915.pdf).
 */
template <typename F, typename Tuple>
auto apply_tuple(F&& f, Tuple&& t) {
    using Indices = std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>;
    return apply_impl(std::forward<F>(f), std::forward<Tuple>(t), Indices{});
}

template <typename T, typename F, typename Tuple>
auto apply_tuple(T* this_ptr, F&& f, Tuple&& t) {
    using Indices = std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>;
    return apply_impl(this_ptr, std::forward<F>(f), std::forward<Tuple>(t), Indices{});
}

}

#endif
