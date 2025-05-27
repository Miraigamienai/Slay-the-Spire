#pragma once

#include <memory>
#include <utility>//std::move

#include "Game_object/action/Actions.hpp"
#include "Game_object/effect/Effects.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace Action{
class Effect_capsule_action: public Actions
{
public:
    enum class Layer{
        normal,
        back,
        top
    };
    Effect_capsule_action(const std::shared_ptr<Effect::Effects> &eff, float duration, Layer layer)
        noexcept : eff(eff), once(false), layer(layer)
    {
        this->duration = duration;
    }
    Effect_capsule_action(std::shared_ptr<Effect::Effects> &&eff,float duration, Layer layer)
        noexcept : eff(std::move(eff)), once(false), layer(layer)
    {
        this->duration = duration;
    }
    ~Effect_capsule_action()override=default;
    
    void update(Dungeon::Dungeon_shared &dungeon_shared)override{
        if(!once){
            once=true;
            if(eff!=nullptr){
                switch(layer){
                    case Layer::top:
                        dungeon_shared.top_effs.AddTop(eff);
                        break;
                    case Layer::back:
                        dungeon_shared.back_effs.AddTop(eff);
                        break;
                    default:
                        dungeon_shared.effs.AddTop(eff);
                        break;
                }
            }
        }
        TimeGo();
    }
private:
    std::shared_ptr<Effect::Effects> eff;
    bool once;
    Layer layer;
};
}