#pragma once

#include <memory>
#include <SDL_stdinc.h>

#include "RUtil/Hitbox.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
    class ReTexture;
}
namespace Dungeon{
    struct Dungeon_shared;
}

namespace Room{
namespace Option{
class Options
{
public:
    Options(const std::shared_ptr<Draw::ReTexture> &img, bool is_activating=true);
    virtual ~Options()=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update();
    void move(float center_x, float center_y)noexcept(noexcept(hb.move(center_x, center_y))){hb.move(center_x, center_y);}
    
    bool is_logically_clicked()const noexcept{return hb.Clicked()&&is_activating;}
    bool IsDone()const noexcept{return is_done;}
    bool IsCancelled()const noexcept{return is_cancelled;}
    virtual void take_reward(Dungeon::Dungeon_shared &dungeon_shared)=0;
    
protected:
    virtual void chile_label_render(const std::shared_ptr<Draw::Draw_2D> &r2,Uint32 font_color)const=0;
    virtual void chile_description_render(const std::shared_ptr<Draw::Draw_2D> &r2,float font_color_a)const=0;
    RUtil::Hitbox hb;
    float scale;
    bool is_activating;
    bool is_done;
    bool is_cancelled;
    static constexpr float DESCRIPTION_X=950.0F * Setting::SCALE,
                           DESCRIPTION_Y=static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F + 20.0F*Setting::SCALE; 
    static constexpr int TEXT_SIZE=26;
private:
    const std::shared_ptr<Draw::ReTexture> &img;
    
    static const std::shared_ptr<Draw::ReTexture> &OUTLINE;
    static constexpr float SHADOW_X = 11.0F * Setting::SCALE,
                           SHADOW_Y = -8.0F * Setting::SCALE,
                           NORMAL_SCALE = 0.9F * Setting::SCALE,
                           HOVER_SCALE = Setting::SCALE;
};   
}
}