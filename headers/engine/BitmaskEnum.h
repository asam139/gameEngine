//
// Created by Saul Moreno Abril on 25/01/2018.
//

#ifndef GAMEENGINE_BITMASKENUM_H
#define GAMEENGINE_BITMASKENUM_H

template<typename Enum>
struct EnableBitMaskOperators
{
    static const bool enable = false;
};

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator|(Enum lhs, Enum rhs) {
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator &(Enum lhs, Enum rhs) {
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ^(Enum lhs, Enum rhs) {
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ~(Enum rhs) {
    using underlying = typename std::underlying_type<Enum>::type;
    return static_cast<Enum> (~static_cast<underlying>(rhs));
}


template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator |=(Enum &lhs, Enum rhs) {
    using underlying = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum> (static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
    return lhs;
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator &=(Enum &lhs, Enum rhs) {
    using underlying = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum> (static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
    return lhs;
}

template<typename Enum>
typename std::enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type
operator ^=(Enum &lhs, Enum rhs) {
    using underlying = typename std::underlying_type<Enum>::type;
    lhs = static_cast<Enum> (static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
    return lhs;
}


#define ENABLE_BITMASK_OPERATORS(x)  \
template<>\
struct EnableBitMaskOperators<x>     \
{                                    \
    static const bool enable = true; \
};

#endif //GAMEENGINE_BITMASKENUM_H
