#pragma once

#include <memory>

#include "Game_object/effect/Effects.hpp"
#include "Game_object/interface/Reusable.hpp"

//fwd decl
namespace Draw{
    class Atlas_Region;
}

namespace Effect{
class Card_proof_particle final:public Effects,public Interface::Reusable<Card_proof_particle>
{
public:
    Card_proof_particle(const float x,const float y){Initial(x,y);}
    ~Card_proof_particle()override=default;
    void Initial(const float x,const float y);
    
    static const std::shared_ptr<Draw::Atlas_Region> &SMOKE1,&SMOKE2,&SMOKE3;
};
}