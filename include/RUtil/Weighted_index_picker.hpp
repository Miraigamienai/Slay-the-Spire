#pragma once

#include <array>
#include <algorithm>

#include "RUtil/Random.hpp"

template <int N>
class Weighted_index_picker
{
static_assert(N > 0, "Weighted_index_picker requires N > 0");
public:
    explicit constexpr Weighted_index_picker(const std::array<float, N>& weights)
        :cdf_arr()
    {
        float total = cdf_arr[0] = weights[0];
        for(int i=1;i<N;i++){
            total+=weights[i];
            cdf_arr[i]=cdf_arr[i-1]+weights[i];
        }
        if(total!=0.0F)
            for(int i=0;i<N;i++) cdf_arr[i]/=total;
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
private:
    std::array<float, N> cdf_arr;
};