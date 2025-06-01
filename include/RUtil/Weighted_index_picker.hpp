#pragma once

#include <array>
#include <algorithm>

#include "RUtil/Random.hpp"

namespace RUtil{
template <int N>
class Weighted_index_picker
{
static_assert(N > 0, "Weighted_index_picker requires N > 0");
public:
    explicit constexpr Weighted_index_picker(const std::array<float, N>& weights)
        :pmf_arr(weights),
        cdf_arr()
    {
        float total = cdf_arr[0] = weights[0];
        for(int i=1;i<N;i++){
            total+=weights[i];
            cdf_arr[i]=cdf_arr[i-1]+weights[i];
        }
        if(total!=0.0F)
            for(int i=0;i<N;i++){
                pmf_arr[i]/=total;
                cdf_arr[i]/=total;
            }
    }
    ~Weighted_index_picker()=default;
    int NextIndex(const RUtil::Random &rng)const{
        const float val = rng.GetRandomFloat(0.0F, 1.0F);
        if constexpr(N<10){
            for(int i=0;i<N-1;i++)
                if(val<cdf_arr[i]) return i;
            return N-1;
        }else{
            const auto it = std::upper_bound(cdf_arr.begin(), cdf_arr.end(), val);
            return static_cast<int>(std::distance(cdf_arr.begin(), it));
        }
    }
    int NextIndexWithOut(int excluded_index, const RUtil::Random &rng)const{
        const float total = 1.0F-pmf_arr[excluded_index];
        if(total<=0.0F) return excluded_index;
        const float val = rng.GetRandomFloat(0.0F, 1.0F)*total;
        float now_cdf_val = 0.0F;
        for(int i=0;i<N;i++){
            if(i==excluded_index) continue;
            now_cdf_val+=pmf_arr[i];
            if(val<now_cdf_val) return i;
        }
        return excluded_index;
    }
private:
    std::array<float, N> pmf_arr;
    std::array<float, N> cdf_arr;
};

template <size_t N>
inline constexpr auto make_weighted_index_picker(const std::array<float, N>& weights){
    return Weighted_index_picker<(static_cast<int>(N))>(weights);
}
}