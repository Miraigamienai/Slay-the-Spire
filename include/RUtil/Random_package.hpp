#pragma once

#include "RUtil/Random.hpp"

namespace RUtil{
struct Random_package
{
    Random map_rng;//Used for generating the map.
    Random monster_rng;//Used for designing mosters in rooms.
    Random reward_rng;//Used for generating rewards.
    Random misc_rng;//other

    //The following RNGs are refreshed when entering each room.
    
    Random card_get_rng;//Used for generating temporacy battle-only cards.
    Random card_shuffle_rng;//Used for shuffling the cards.
    Random monster_status_rng;//Used for randomizing the monster status.
    Random monster_ai_rng;//Used for randomizing the monster AI.
    Random monster_type_rng;//Used for randomizing the monster type.
    Random_package()=default;

    void SetAllSeed(unsigned long long int seed){
        map_rng.SetNewSeed(seed);
        monster_rng.SetNewSeed(seed);
        reward_rng.SetNewSeed(seed);
        card_get_rng.SetNewSeed(seed);
        card_shuffle_rng.SetNewSeed(seed);
        monster_status_rng.SetNewSeed(seed);
        monster_ai_rng.SetNewSeed(seed);
        misc_rng.SetNewSeed(seed);
    }
    void ResetRoomRNGs(unsigned long long int seed){
        card_get_rng.SetNewSeed(seed);
        card_shuffle_rng.SetNewSeed(seed);
        monster_status_rng.SetNewSeed(seed);
        monster_ai_rng.SetNewSeed(seed);
        monster_type_rng.SetNewSeed(seed);
    }
};
}