#pragma once

#include <memory>
#include <glm/vec2.hpp>
#include <SDL_stdinc.h>

#include "Game_object/effect/Effects.hpp"
#include "Game_object/abstraction/Reusable.hpp"

//fwd decl
namespace Draw{
    class ReTexture;
}

namespace Effect{
class Slash_eff final:public Effects,public Abstraction::Reusable<Slash_eff>
{
public:
    Slash_eff(glm::vec2 pos, glm::vec2 distant, float angle, float target_scale, Uint32 color1, Uint32 color2){
        Initial(pos,distant,angle,target_scale,color1,color2);
    }
    ~Slash_eff()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update() override;
    void Initial(glm::vec2 pos, glm::vec2 distant, float angle, float target_scale, Uint32 color1, Uint32 color2);
private:
    glm::vec2 pos, start_pos, target_pos, m_scale;
    Uint32 color2;
    float angle;
    static const std::shared_ptr<Draw::ReTexture> &IMG;
    static constexpr float DUR=0.4F;
};
}
