#pragma once

#include <memory>

#include "Game_object/character/Characters.hpp"

namespace Monster{
enum class Intent:int{
    attack,
    attack_buff,
    attack_debuff,
    attack_defend,
    buff,
    debuff,
    strong_debuff,
    defend,
    defend_debuff,
    defend_buff,
    escape,
    magic,
    sleep,
    stun,
    unknown,
    NONE
};
class Monsters:public Character::Characters
{
public:
    // Characters(CharacterType type, float x, float y, float width, float height, float hb_offset_x, float hb_offset_y, int HP);
    Monsters(float offset_x, float offset_y, float width, float height, 
        float hb_offset_x, float hb_offset_y, int HP_min, int HP_max, 
        const std::shared_ptr<Draw::ReTexture> &img);
    
    virtual ~Monsters()=default;
    virtual void Action(Dungeon::Dungeon_shared &dungeon_shared)=0;
    virtual void next_move(const Power::Power_group &player_powers)=0;
    void damage(const Damage_info& damage_info)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update()override;

    void refresh_dmg_display(const Power::Power_group &player_powers);
    bool IsInDyingFade()const noexcept{return dying_fade_timer!=0.0F;}
protected:
    void set_move(const std::shared_ptr<Draw::Text_layout> &move_name, Intent intent, int base_damage, int multiplier, const Power::Power_group &player_powers);
    void set_move(const std::shared_ptr<Draw::Text_layout> &move_name, Intent intent, int base_damage, const Power::Power_group &player_powers);
    static constexpr int FLOOR_Y=Setting::WINDOW_HEIGHT*0.5F-200.0F*Setting::SCALE;
private:
    struct Move{
        std::shared_ptr<Draw::Text_layout> move_name;
        std::shared_ptr<Draw::ReTexture> intent_img;
        Intent intent;
        bool is_multi_dmg;
        int multiplier;
        int base_damage;
        int damage;
    };
    const std::shared_ptr<Draw::ReTexture> &img;
    float img_color_a;
    float dying_fade_timer;
    //intent
    Move move;
    Effect::Effect_group intent_effs, intent_back_effs;
    Draw::Text_box intent_tip;
    std::shared_ptr<Draw::ReTexture> intent_tip_img;
    RUtil::Hitbox intent_hb;
    float intent_a, intent_target_a;
    float intent_angle;
    float intent_particle_timer;

    void update_intent_vfx();
    void refresh_intent_tip();
    void set_move(const Power::Power_group &player_powers){
        // this.intentParticleTimer = 0.5F;
        intent_a=0.0F;
        intent_target_a=1.0F;
        refresh_dmg_display(player_powers);
        refresh_intent_tip();
    }
};
}