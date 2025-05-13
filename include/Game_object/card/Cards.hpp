#pragma once

#include <vector>
#include <memory>

#include "Game_object/card/Card_soul.hpp"//father
#include "Game_object/effect/Card_flash.hpp"//member
#include "Game_object/effect/Effect_group.hpp"//member (glowgroup)
#include "RUtil/Some_Math.hpp"//get rgb color
#include "RUtil/Hitbox.hpp"//member

//fwd decl
namespace Draw{
    class Draw_2D;
    class Atlas_Region;
    class Text_layout;
}
namespace RUtil{
    enum class AtlasRegionID:int;
}
namespace Dungeon{
    struct Dungeon_shared;
}
namespace Monster{
    class Monster_group;//monsters
    class Monsters;
}

namespace Card{
enum class Rarity{
    basic,
    special,
    common,
    uncommon,
    rare,
    curse
};
enum class Type{
    attack,
    skill,
    power,
    status,
    curse
};
enum class Color{
    red,
    green,
    blue,
    purple,
    colorless,
    curse
};
enum class Target{
    enemy,
    all_enemy,
    self,
    self_and_enemy,
    all,
    none
};
//control render logic
//and normal move
class Cards:public Card_soul{
public:
    Cards(RUtil::AtlasRegionID card_name,Rarity rarity,Type type,Color color,Target target,
        const int base_cost,const int base_damage=0,const int base_defense=0,const int base_magic_num=0);
    virtual ~Cards() = default;
    Cards(const Cards& other);//ensure internal references are properly set when coping. //(m_card_flash)
    
    Cards(Cards &&) = delete;
    Cards &operator=(const Cards &) = delete;
    Cards &operator=(Cards &&) = delete;

    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void render_hovered_shadow(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    void update(Effect::Effect_group &top_effs);
    // void update_hover_logic();
    void SetHoverTimer(const float value);//hover timer will be set when releasing card.
    void MoveTargetY(const float value);
    void MoveTargetX(const float value);
    void MoveTargetAngle(const float value);
    
    void Darken(bool immediate);
    void Lighten();
    void Unhover();
    void draw();
    //check hover status at specific scale.
    bool IsHoveredInHand(const float scale)const;
    void CanUseUpdate(const Dungeon::Dungeon_shared &dungeon_shared);
    
    //virtual function
    
    //Check if it is usable based on the current situation.
    virtual bool CanUse(const Dungeon::Dungeon_shared &dungeon_shared)const;
    virtual void Use(Dungeon::Dungeon_shared &dungeon_shared,const Monster::Monster_group &room_monsters,const std::shared_ptr<Monster::Monsters> &target_monster)=0;
    virtual std::shared_ptr<Cards> Clone()const=0;
    virtual void Upgrade()=0;
    
    //inline function
    
    //immediately 1.0F draw scale
    void Hover()noexcept(noexcept(SetDrawScale(1.0F,true))){SetDrawScale(1.0F,true);}
    //check hover status at the current scale of card.
    bool HitboxHovered()const noexcept(noexcept(hb.Hovered())){return this->hb.Hovered();}
    bool HitboxClicked()const noexcept(noexcept(hb.Clicked())){return this->hb.Clicked();}
    void SetCanHoverInHand(bool value)noexcept{this->can_hover_in_hand=value;}
    //0.12F scale
    void Shrink(bool immediate)noexcept{
        m_target_draw_scale=0.12F;
        if(immediate) m_draw_scale=0.12F;
    }
    void Flash(Uint32 _c)noexcept{m_card_flash.change_color(_c);}
    void SuperFlash()noexcept{m_card_flash.change_color(GLOWCOLOR,true);}
    //Simply return the current status, dosen't do any actual checking.
    bool IsUpgraded()const noexcept{return upgraded;}
    bool CanUse()const noexcept{return can_use;}
    int GetCost()const noexcept{return cost;}
    float GetX()const noexcept{return current_x;}
    float GetY()const noexcept{return current_y;}
    float GetTargetX()const noexcept{return target_x;}
    float GetTargetY()const noexcept{return target_y;}
    float GetDrawScale()const noexcept{return m_draw_scale;}
    void SetY(const float value,const bool immediate=false)noexcept{target_y=value;if(immediate)current_y=value;}
    void SetX(const float value,const bool immediate=false)noexcept{target_x=value;if(immediate)current_x=value;}
    void SetAngle(const float value,const bool immediate=false)noexcept{target_angle=value;if(immediate)m_angle=value;}
    void SetDrawScale(const float value,const bool immediate=false)noexcept{m_target_draw_scale=value;if(immediate)m_draw_scale=value;}
    void SetColorAlpha(const float value,const bool immediate=false)noexcept{m_target_color_a=value;if(immediate)m_color_a=value;}
    bool IsSingleTarget()const noexcept{return target==Target::enemy||target==Target::self_and_enemy;}
    //static function
    static void SetRenderColor(Uint32 c)noexcept{s_render_color=c;}
    //member
    const RUtil::AtlasRegionID card_name;
    const Rarity rarity;
    const Type type;
    const Color color;
    const Target target;

    //for child classes 

    void ResetAttributes(){
        damage=base_damage;
        defense=base_defense;
        magic_num=base_magic_num;
        cost=base_cost;
    }
protected:
    void SetDamage(int num){
        this->base_damage=this->damage=num;
    }
    void SetDefense(int num){
        this->base_defense=this->defense=num;
    }
    void SetMagicNum(int num){
        this->base_magic_num=this->magic_num=num;
    }
    bool upgraded=false;
    int base_damage, base_defense, base_magic_num, base_cost;
    int damage,      defense,      magic_num,      cost;
private:
    static const float &DT;
    const std::shared_ptr<Draw::Atlas_Region> &m_card_bg_silhouette,&m_card_bg,&m_card_frame,&m_card_left_frame,&m_card_mid_frame,&m_card_right_frame,&m_card_banner,&m_card_portrait;
    Effect::Card_flash m_card_flash;
    RUtil::Hitbox hb;
    bool darken,can_use,can_hover_in_hand;
    float m_draw_scale,m_angle,m_tint_a,m_target_draw_scale,m_dark_timer,m_glow_timer,m_hover_timer;
    float m_color_a,m_target_color_a;
    float m_type_width,m_type_offset;
    int m_text_pos;
    Effect::Effect_group glowgroup;

    void format_render(const std::shared_ptr<Draw::Draw_2D> &r2,const std::shared_ptr<Draw::Atlas_Region> &img,const float x,const float y,const float scale=1.0F)const;
    void frame_format_render(const std::shared_ptr<Draw::Draw_2D> &r2,const std::shared_ptr<Draw::Atlas_Region> &img,const float x_offset,const float x_scale)const;
    void SetFontTypeOffset();
    static Uint32 s_render_color;
    static void init_static_menber();
    static constexpr Uint32 FRAME_SHADOW_COLOR=0,DEFAULT_COLOR=RUtil::Math::GetColorUint32_RGB(255,255,255),TYPE_COLOR=RUtil::Math::GetColorUint32_RGB(0.35F,0.35F,0.35F),TINT_COLOR=RUtil::Math::GetColorUint32_RGB(43,37,65);
    static constexpr float  SHADOW_OFFSET_X = 18.0F * Setting::SCALE,
                            SHADOW_OFFSET_Y = 14.0F * Setting::SCALE,
                            CARD_SNAP_THRESHOLD = 1.0F * Setting::SCALE;
    static const std::vector<std::shared_ptr<Draw::Text_layout>> &s_ui_vec;
    static float s_type_offset_attack,s_type_offset_skill,s_type_offset_power,s_type_offset_status,s_type_offset_curse,s_type_width_attack,s_type_width_skill,s_type_width_power,s_type_width_status,s_type_width_curse;
    static constexpr int CARD_FONT_SIZE=17;
    static constexpr Uint32 GLOWCOLOR=RUtil::Math::GetColorUint32_RGB(0.2F,0.9F,1.0F);
public:
    static constexpr float  IMG_WIDTH = 300.0F * Setting::SCALE,
                            IMG_HEIGHT = 420.0F * Setting::SCALE,
                            IMG_WIDTH_S = 300.0F * Setting::SCALE * 0.7F,
                            IMG_HEIGHT_S = 420.0F * Setting::SCALE * 0.7F;
};
inline bool operator<(Rarity lhs, Rarity rhs) {
    return static_cast<int>(lhs) < static_cast<int>(rhs);
}
inline bool operator<(Type lhs, Type rhs) {
    return static_cast<int>(lhs) < static_cast<int>(rhs);
}
}