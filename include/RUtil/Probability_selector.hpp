#pragma once

#include <utility>

#include "RUtil/Weighted_index_picker.hpp"

namespace RUtil{
template <typename T, int N>
class Probability_selector
{
public:
    explicit constexpr Probability_selector(const std::array<T, N> &result, const std::array<float, N>& weights)
        :result(result),
        weight_picker(weights){}
    ~Probability_selector()=default;
    T operator()(const RUtil::Random &rng)const{
        return result[weight_picker.NextIndex(rng)];
    }
private:
    std::array<T, N> result;
    Weighted_index_picker<N> weight_picker;
};

template <typename T1, typename T2, typename F, size_t...Is>
static constexpr auto GetArrayFromPair(const std::array<std::pair<T1, T2>, sizeof...(Is)>&pair_arr, F fun, std::index_sequence<Is...>){
    return std::array{fun(pair_arr[Is])...};
}

template <typename T1, typename T2, typename F, size_t N>
static constexpr auto GetArrayFromPair(const std::array<std::pair<T1, T2>, N>&pair_arr, F fun){
    return GetArrayFromPair(pair_arr, fun, std::make_index_sequence<N>{});
}

template <typename T, size_t N>
inline constexpr auto make_probability_selector(const std::array<std::pair<T, float>, N>& result_weight_pairs){
    return Probability_selector<T, (static_cast<int>(N))>(GetArrayFromPair(result_weight_pairs, [](auto pair)constexpr{return pair.first;}), GetArrayFromPair(result_weight_pairs, [](auto pair)constexpr{return pair.second;}));
}
}