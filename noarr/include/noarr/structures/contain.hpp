#ifndef NOARR_STRUCTURES_CONTAIN_HPP
#define NOARR_STRUCTURES_CONTAIN_HPP

#include <type_traits>

namespace noarr {

namespace helpers {

/**
 * @brief see `contain`. This is a helper structure implementing its functionality
 * 
 * @tparam typename: placeholder type
 * @tparam ...TS: contained fields
 */
template<typename, typename... TS>
struct contain_impl;

/**
 * @brief structure that facilitates `.get` method of the `contain` structure
 * 
 * @tparam T: the `contain` structure
 * @tparam I: the index of the desired field
 */
template<typename T, std::size_t I>
struct contain_get {
    static constexpr decltype(auto) get(const T &t) {
        return t.template _get_next<I>();
    }
};

template<typename T>
struct contain_get<T, 0> {
    static constexpr decltype(auto) get(const T &t) {
        return t._get();
    }
};

template<typename T, typename... TS>
struct contain_impl<std::enable_if_t<!std::is_empty<T>::value && !std::is_empty<contain_impl<void, TS...>>::value && (sizeof...(TS) > 0)>, T, TS...> {
    template<typename, std::size_t>
    friend struct contain_get;

    T t;
    contain_impl<void, TS...> ts;

    constexpr contain_impl() = default;
    explicit constexpr contain_impl(T t, TS... ts) : t(t), ts(ts...) {}

    template<std::size_t I>
    constexpr decltype(auto) get() const {
        return contain_get<contain_impl, I>::get(*this);
    }

private:
    template<std::size_t I>
    constexpr decltype(auto) _get_next() const {
        return ts.template get<I - 1>();
    }

    constexpr auto _get() const {
        return t;
    }
};

template<typename T, typename... TS>
struct contain_impl<std::enable_if_t<!std::is_empty<T>::value && std::is_empty<contain_impl<void, TS...>>::value && (sizeof...(TS) > 0)>, T, TS...> : private contain_impl<void, TS...> {
    template<typename, std::size_t>
    friend struct contain_get;

    T t;

    constexpr contain_impl() = default;
    explicit constexpr contain_impl(T t) : t(t) {}
    explicit constexpr contain_impl(T t, TS...) : t(t) {}

    template<std::size_t I>
    constexpr decltype(auto) get() const {
        return contain_get<contain_impl, I>::get(*this);
    }

private:
    template<std::size_t I>
    constexpr decltype(auto) _get_next() const {
        return contain_impl<void, TS...>::template get<I - 1>();
    }

    constexpr auto _get() const {
        return t;
    }
};

template<typename T, typename... TS>
struct contain_impl<std::enable_if_t<std::is_empty<T>::value && (sizeof...(TS) > 0)>, T, TS...> : private contain_impl<void, TS...> {
    template<typename, std::size_t>
    friend struct contain_get;

    constexpr contain_impl() = default;
    explicit constexpr contain_impl(TS... ts) : contain_impl<void, TS...>(ts...) {}
    explicit constexpr contain_impl(T, TS... ts) : contain_impl<void, TS...>(ts...) {}

    template<std::size_t I>
    constexpr decltype(auto) get() const {
        return contain_get<contain_impl, I>::get(*this);
    }

private:
    template<std::size_t I>
    constexpr decltype(auto) _get_next() const {
        return contain_impl<void, TS...>::template get<I - 1>();
    }

    constexpr auto _get() const {
        return T();
    }
};

template<typename T>
struct contain_impl<std::enable_if_t<std::is_empty<T>::value>, T> {
    template<typename, std::size_t>
    friend struct contain_get;

    constexpr contain_impl() = default;
    explicit constexpr contain_impl(T) {}

    template<std::size_t I>
    constexpr decltype(auto) get() const {
        return contain_get<contain_impl, I>::get(*this);
    }

private:
    constexpr auto _get() const {
        return T();
    }
};

template<typename T>
struct contain_impl<std::enable_if_t<!std::is_empty<T>::value>, T> {
    template<typename, std::size_t>
    friend struct contain_get;

    T t;

    constexpr contain_impl() = default;
    explicit constexpr contain_impl(T t) : t(t) {}

    template<std::size_t I>
    constexpr decltype(auto) get() const {
        return contain_get<contain_impl, I>::get(*this);
    }

private:
    constexpr auto _get() const {
        return t;
    }
};

template<>
struct contain_impl<void> {};

}

/**
 * @brief A base class that contains the fields given as template arguments. It is similar to a tuple but it is a standard layout.
 * 
 * @tparam TS the contained fields
 */
template<typename... TS>
using contain = helpers::contain_impl<void, TS...>;

} // namespace noarr

#endif // NOARR_STRUCTURES_CONTAIN_HPP