#pragma once

#include <list>
#include <memory>
#include <array>

#include "Game_object/Group_template.hpp"
#include "Game_object/effect/Effect_group.hpp"
#include "Game_object/power/Powers.hpp"
#include "Draw/Text_box.hpp"
#include "WindowSize.hpp"

//fwd decl
namespace Draw{
    class Draw_2D;
    class ReTexture;
}

namespace Power
{
class Power_group final:public Template::Group_template<std::list<std::shared_ptr<Powers>>>
{
public:
    Power_group()=default;
    ~Power_group()override=default;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const;
    void render_tip(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y)const;
    void render_tip_with_other(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, const Draw::Text_box&other_box, const std::shared_ptr<Draw::ReTexture> &other_img)const;
    void update(){for(const auto&it:box)it->update();}

    //events
    void at_turn_end(Dungeon::Dungeon_shared &dungeon_shared, const std::shared_ptr<Character::Characters> &target)const{for(const auto&it:box)it->at_turn_end(dungeon_shared,target);}
    float calculate_damage_dealt(float damage)const{for(const auto&it:box)damage=it->calculate_damage_dealt(damage);return damage;}

    //special
    bool no_lose_block()const{
        for(const auto&it:box) if(it->power_id == RUtil::Powers_Text_ID::Barricade) return true;
        return false;
    }
private:
    float calculate_tip_height()const;
    float calculate_tip_height_with_other(const Draw::Text_box&other_box)const;
    static constexpr float TIP_MAX_HEIGHT=Setting::WINDOW_HEIGHT*0.7F,
                           TIP_PADDING_Y=Draw::Text_box::BOX_EDGE_H*3.15F;
};
} // namespace Power
