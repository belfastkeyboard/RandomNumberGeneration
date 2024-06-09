#pragma once

#include    <random>
#include    <chrono>

/**
 * 
 * @brief Very basic implementation of 128-bit int.
 *        Intended purely for UUID purposes.
 *        Therefore only equality comparison operators are implemented.
 * 
 */

namespace rng
{
    /**
     * 
     * @brief   Get a rng number between __min and __max.
     * 
     */
    template <typename T>
    inline T number(T _min, T _max)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_arithmetic<T>::value, "must be an arithmetic type");
        if (std::is_integral<T>::value)
        { std::uniform_int_distribution<int> dist(_min, _max); return static_cast<T>(dist(gen)); } else
        { std::uniform_real_distribution<double> dist(_min, _max); return static_cast<T>(dist(gen)); }
    }
    /**
     * 
     * @brief   Get a rng number from a normal distribution.
     *          __mean specifies the peak of the bell-curve.
     *          Optional standard deviation, default = 10.0.
     * 
     */
    template <typename T>
    inline T weighted_number(T _mean, double _std_dev)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_arithmetic<T>::value, "must be an arithmetic type");
        std::normal_distribution<double> dist(_mean, _std_dev);
        return static_cast<T>(dist(gen));
    }
    /**
     * 
     * @brief   Get a rng number from a normal distribution between __min and __max.
     *          __mean specifies the  peak of the bell-curve.
     *          Optional standard deviation, default = 10.0.
     * 
     * @warning This function can enter an infinite loop as a result of its parameters.
     * 
     */
    template <typename T>
    inline T weighted_number(T _min, T _max, double _mean, double _std_dev)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_arithmetic<T>::value, "must be an arithmetic type");
        std::normal_distribution<double> dist(_mean, _std_dev);
        T v;
        do {
            v = static_cast<T>(dist(gen));
        } while (v < _min || v > _max); // we use a do-while loop here to ensure that the number returned is within the range without clamping
        return v;                         // clamping tends to cluster numbers artificially around the clamp
    }                                     // this is an imperfect work-around
    /**
     * 
     * @brief   Roll a rng number against a percentage.
     *          __x is clamped to 0, 100 if outside this range.
     * 
     */
    template <typename T>
    inline bool percentage(T _x)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_arithmetic<T>::value, "percentage must be an arithmetic type");
        std::max(T(0), std::min(T(100), _x));
        return number(0, 100) < _x;
    }
    /**
     * 
     * @brief   Generates a rng 64-bit UUID.
     * 
     */
    inline uint64_t UUID()
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<uint64_t> dist(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
        return dist(gen);
    }
    /**
     * 
     * @brief   Generates a rng 128-bit UUID.
     * 
     */
    inline __uint128_t UUID128()
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<uint64_t> dist(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
        uint64_t a = dist(gen);
        uint64_t b = dist(gen);
        return ((__uint128_t)a << 64) | b;
    }
    /**
     * 
     * @brief   Get a rng index from a vector.
     * 
     */
    template <typename T>
    inline size_t index(std::vector<T> _vec)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> dist(0, _vec.size() - 1);
        return static_cast<size_t>(dist(gen));
    }
    /**
     * 
     * @brief   Get a rng index from a vector, using a normal distribution.
     *          Optional standard deviation, default = 10.0.
     * 
     * @warning This function can enter an infinite loop as a result of its parameters.
     * 
     */
    template <typename T>
    inline size_t weighted_index(std::vector<T> _v, size_t _mean, size_t _std_dev)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        std::normal_distribution<double> dist((double)(_mean), (double)(_std_dev));
        size_t v;
        do {
            v = static_cast<size_t>(dist(gen));
        } while (v > _v.size() - 1);
        return  v;
    }
    /**
     * 
     * @brief   Get a rng index from a vector, where the vector is an list of indices.
     * 
     */
    template <typename T>
    inline size_t weighted_index(std::vector<T> _vec)
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static_assert(std::is_integral<T>::value, "weights vector must be an integral type");
        std::uniform_int_distribution<size_t> dist(0, _vec.size());
        return static_cast<size_t>(_vec[dist(gen)]);
    }
    /**
     * 
     * @brief Get a Mersenne twister generator object. Used in algorithms like std::shuffle.
     * 
     */
    inline std::mt19937 gen()
    {
        static std::mt19937 gen(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        return gen;
    }
}
