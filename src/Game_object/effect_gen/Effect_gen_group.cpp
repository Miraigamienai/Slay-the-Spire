#include "Game_object/effect_gen/Effect_gen_group.hpp"
#include "Game_object/effect_gen/Effect_gen.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"


namespace EffectGen{
    void Effect_gen_group::update(Dungeon::Dungeon_shared &dungeon_shared){
        for (auto it = box.begin(); it != box.end();) {
            (*it)->update(dungeon_shared);
            if ((*it)->IsDone())
                it = box.erase(it);
            else
                ++it;
        }
    }
}