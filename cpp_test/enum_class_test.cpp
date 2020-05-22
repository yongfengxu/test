#include <iostream>
#include <type_traits>

// To get the integral value for strongly typed enums (enum class)
// This is useful where the value is part of calculation etc
template <typename E>
constexpr auto toIntegral(E e) -> typename std::underlying_type<E>::type {
  return static_cast<typename std::underlying_type<E>::type>(e);
}

#define VARIADIC_SIZE(...)                                                     \
  VARIADIC_SIZE_I(                                                             \
      __VA_ARGS__, 128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, \
      116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103,    \
      102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86,   \
      85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68,  \
      67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,  \
      49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32,  \
      31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14,  \
      13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, )
#define VARIADIC_SIZE_I(                                                       \
    e0, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, \
    e17, e18, e19, e20, e21, e22, e23, e24, e25, e26, e27, e28, e29, e30, e31, \
    e32, e33, e34, e35, e36, e37, e38, e39, e40, e41, e42, e43, e44, e45, e46, \
    e47, e48, e49, e50, e51, e52, e53, e54, e55, e56, e57, e58, e59, e60, e61, \
    e62, e63, e64, e65, e66, e67, e68, e69, e70, e71, e72, e73, e74, e75, e76, \
    e77, e78, e79, e80, e81, e82, e83, e84, e85, e86, e87, e88, e89, e90, e91, \
    e92, e93, e94, e95, e96, e97, e98, e99, e100, e101, e102, e103, e104,      \
    e105, e106, e107, e108, e109, e110, e111, e112, e113, e114, e115, e116,    \
    e117, e118, e119, e120, e121, e122, e123, e124, e125, e126, e127, size,    \
    ...)  size

#define ENUM_FLAG(Name, Type, ...) \
    enum class Name : Type { __VA_ARGS__ }; \
    constexpr auto FLAG_SIZE(Name) { return VARIADIC_SIZE(__VA_ARGS__); } \
    constexpr Type FLAG_MASK(Name) \
    { \
        static_assert(std::is_unsigned<Type>::value, "The Flag class type must be an unsigned type"); \
        constexpr const struct { MAKE_STRING_VAR(VARIADIC_SIZE(__VA_ARGS__), Type, __VA_ARGS__) } values; \
        Type                                                                                      mask = 0; \
        for (size_t i = 0; i < VARIADIC_SIZE(__VA_ARGS__); ++i) \
        { \
            mask |= reinterpret_cast<const Type*>(&values)[i]; \
        } \
        return mask; \
    } \
    inline void toScopedFlags(Name & dest, Type input) \
    { \
        input &= FLAG_MASK(Name()); \
        dest   = static_cast<Name>(input); \
    } \
    inline constexpr Name operator |(const Name a, const Name b) \
    { \
        return static_cast<Name>(toIntegral(a) | toIntegral(b)); \
    } \
    inline Name& operator |=(Name& a, const Name b) \
    { \
        a = static_cast<Name>(toIntegral(a) | toIntegral(b)); \
        return a; \
    } \
    inline constexpr Name operator &(const Name a, const Name b) \
    { \
        return static_cast<Name>(toIntegral(a) & toIntegral(b)); \
    } \
    inline Name& operator &=(Name& a, const Name b) \
    { \
        a = static_cast<Name>(toIntegral(a) & toIntegral(b)); \
        return a; \
    } \
    inline constexpr Name operator ~(const Name a) \
    { \
        return static_cast<Name>(~toIntegral(a)); \
    } \
    inline constexpr bool EnumFlag_isFlagSet(Name flags, Name flag) \
    { \
        return flag == (flags & flag); \
    } \
    inline constexpr bool EnumFlag_isAnyFlagSet(Name flags, Name flag) \
    { \
        return 0 != toIntegral(flags & flag); \
    } \
    inline bool EnumFlag_isAnyFlagSet(Name flags) \
    { \
        return 0 != (toIntegral(flags) & FLAG_MASK(Name())); \
    } \
    inline void EnumFlag_setFlag(Name & flags, Name flag) \
    { \
        flags |= flag; \
    } \
    inline void EnumFlag_clearFlag(Name & flags, Name flag) \
    { \
        flags &= ~flag; \
    } \
    inline void EnumFlag_clearFlag(Name & flags) \
    { \
        flags = static_cast<Name>(0); \
    } 


enum class Web_color : int
{
    red = 0,
    purple = 1,
    blue = 2
};

ENUM_FLAG(UpdateBearerFlags, uint32_t,
        None                  = 0x00000000u,
        SgsnDataChanged       = 0x00000001u,
        QosChanged            = 0x00000002u,
        TftChanged            = 0x00000004u
    );


int main()
{
    Web_color c1 = Web_color::red;

    Web_color c2;
    Web_color c3 = Web_color::purple;

    std::cout << static_cast<int>(c1) << std::endl;
    std::cout << static_cast<int>(c2) << std::endl;
    std::cout << static_cast<int>(c3) << std::endl;


    UpdateBearerFlags flags;
}
