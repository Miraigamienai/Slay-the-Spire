#pragma once

#include <memory>

#include "Game_object/character/Characters.hpp"

namespace Monster{
class Monsters:public Character::Characters
{
public:
    // Characters(CharacterType type, float x, float y, float width, float height, float hb_offset_x, float hb_offset_y, int HP);
    Monsters(float offset_x, float offset_y, float width, float height, 
        float hb_offset_x, float hb_offset_y, int HP_min, int HP_max, 
        const std::shared_ptr<Draw::ReTexture> &img);
    
    virtual ~Monsters()=default;
    virtual void Action(Dungeon::Dungeon_shared &dungeon_shared)=0; 
    void damage(const Damage_info& damage_info)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update()override;
    bool IsInDyingFade()const noexcept{return dying_fade_timer!=0.0F;}
protected:
    static constexpr int FLOOR_Y=Setting::WINDOW_HEIGHT*0.5F-200.0F*Setting::SCALE;
private:
    const std::shared_ptr<Draw::ReTexture> &img;
    float img_color_a;
    float dying_fade_timer;
};
}