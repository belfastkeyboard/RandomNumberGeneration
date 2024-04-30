#ifndef     RANDOM_NUMBER_GENERATION
#define     RANDOM_NUMBER_GENERATION 1

#include    <random>
#include    <chrono>

/**
 * 
 * @brief Very basic implementation of 128-bit int.
 *        Intended purely for UUID purposes.
 *        Therefore only equality comparison operators are implemented.
 * 
 */

namespace random
{
    /**
     * 
     * @brief   Get a random number between __min and __max.
     * 
     */
    template <typename T>
    T number(T __min, T __max)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_arithmetic<T>::value, "must be an arithmetic type");
        if (std::is_integral<T>::value)
        { std::uniform_int_distribution<int> dist(__min, __max); return static_cast<T>(dist(gen)); } else
        { std::uniform_real_distribution<double> dist(__min, __max); return static_cast<T>(dist(gen)); }
    }
    /**
     * 
     * @brief   Get a random number from a normal distribution.
     *          __mean specifies the peak of the bell-curve.
     *          Optional standard deviation, default = 10.0.
     * 
     */
    template <typename T>
    T weighted_number(T __mean, double __std_dev)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_arithmetic<T>::value, "must be an arithmetic type");
        std::normal_distribution<double> dist(__mean, __std_dev);
        return static_cast<T>(dist(gen));
    }
    /**
     * 
     * @brief   Get a random number from a normal distribution between __min and __max.
     *          __mean specifies the  peak of the bell-curve.
     *          Optional standard deviation, default = 10.0.
     * 
     * @warning This function can enter an infinite loop as a result of its parameters.
     * 
     */
    template <typename T>
    T weighted_number(T __min, T __max, double __mean, double __std_dev)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_arithmetic<T>::value, "must be an arithmetic type");
        std::normal_distribution<double> dist(__mean, __std_dev);
        T v;
        do {
            v = static_cast<T>(dist(gen));
        } while (v < __min || v > __max); // we use a do-while loop here to ensure that the number returned is within the range without clamping
        return v;                         // clamping tends to cluster numbers artificially around the clamp
    }                                     // this is an imperfect work-around
    /**
     * 
     * @brief   Roll a random number against a percentage.
     *          __x is clamped to 0, 100 if outside this range.
     * 
     */
    template <typename T>
    bool percentage(T __x)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_arithmetic<T>::value, "percentage must be an arithmetic type");
        std::max(T(0), std::min(T(100), __x));
        return number(0, 100) < __x;
    }
    /**
     * 
     * @brief   Generates a random 64-bit UUID.
     * 
     */
    uint64_t UUID()
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<uint64_t> dist(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
        return dist(gen);
    }
    /**
     * 
     * @brief   Generates a random 128-bit UUID.
     * 
     */
    __uint128_t UUID128()
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<uint64_t> dist(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
        uint64_t a = dist(gen);
        uint64_t b = dist(gen);
        return ((__uint128_t)a << 64) | b;
    }
    /**
     * 
     * @brief   Get a random index from a vector.
     * 
     */
    template <typename T>
    size_t index(std::vector<T> __vec)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(0, __vec.size() - 1);
        return static_cast<size_t>(dist(gen));
    }
    /**
     * 
     * @brief   Get a random index from a vector, using a normal distribution.
     *          Optional standard deviation, default = 10.0.
     * 
     * @warning This function can enter an infinite loop as a result of its parameters.
     * 
     */
    template <typename T>
    size_t weighted_index(std::vector<T> __v, size_t __mean, size_t __std_dev)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::normal_distribution<double> dist(__mean, __std_dev);
        size_t v;
        do {
            v = static_cast<size_t>(dist(gen));
        } while (v < 0 || v > __v.size() - 1);
        return  v;
    }
    /**
     * 
     * @brief   Get a random index from a vector, where the vector is an list of indices.
     * 
     */
    template <typename T>
    size_t weighted_index(std::vector<T> __vec)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_integral<T>::value, "weights vector must be an integral type");
        std::uniform_int_distribution<size_t> dist(0, __vec.size());
        return static_cast<size_t>(__vec[dist(gen)]);
    }
    /**
     * 
     * @brief Get a Mersenne twister generator object. Used in algorithms like std::shuffle.
     * 
     */
    std::mt19937 gen()
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        return gen;
    }
}


#endif