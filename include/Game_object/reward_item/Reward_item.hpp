#pragma once

#include <memory>

#include "RUtil/Hitbox.hpp"
#include "RUtil/Some_Math.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
    class ReTexture;
}
namespace Dungeon{
    struct Dungeon_shared;
}

namespace Reward{
class Reward_item
{
public:
    Reward_item();
    virtual ~Reward_item()=default;
    void update();
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void move(float y)noexcept{
        this->y=y;
        this->hb.move((float)Setting::WINDOW_WIDTH/2.0F, this->y);
    }
    virtual void take_reward(Dungeon::Dungeon_shared &dungeon_shared)=0;
    bool HitboxClicked()const noexcept{return hb.Clicked();}
    bool is_taking_reward()const noexcept{return taking_reward;}
    bool did_take_reward()const noexcept{return took_reward;}
    void flash()noexcept{flash_timer=0.5F;}
protected:
    virtual void child_render(const std::shared_ptr<Draw::Draw_2D> &r2)const=0;
    virtual void child_render_text(const std::shared_ptr<Draw::Draw_2D> &r2, Uint32 color)const=0;

    float y;
    bool taking_reward=false;
    bool took_reward=false;
    static constexpr float ITEM_X = (float)Setting::WINDOW_WIDTH * 0.41F,
                           TEXT_X = (float)Setting::WINDOW_WIDTH * 0.434F;
private:
    float flash_timer;
    RUtil::Hitbox hb;
    float eff_dur,eff_scale,eff_a;

    static const std::shared_ptr<Draw::ReTexture> &LIST_IMG;
    static constexpr auto HOVERED_COLOR=RUtil::Math::GetColorUint32_RGB(0.4F, 0.6F, 0.6F);
    static constexpr auto COLOR=RUtil::Math::GetColorUint32_RGB(0.5F, 0.6F, 0.6F);
    static constexpr auto EFF_DUR=1.1F;
};
}