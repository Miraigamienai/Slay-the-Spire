#include "Game_object/character/Monster/Hexaghost.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
#include "Game_object/action/Call_action.hpp"
#include "Game_object/action/Effect_gen_capsule_action.hpp"
#include "Game_object/action/Damage_action.hpp"
#include "Game_object/action/Show_card_to_discard_action.hpp"
#include "Game_object/action/Effect_capsule_action.hpp"
#include "Game_object/action/Anim_set_action.hpp"
#include "Game_object/action/Apply_power_action.hpp"
#include "Game_object/action/Gain_block_action.hpp"
#include "Game_object/action/Burn_plus_action.hpp"
#include "Game_object/action/Wait_action.hpp"
#include "Game_object/effect/Ghostly_fire_eff.hpp"
#include "Game_object/effect/Border_flash_eff.hpp"
#include "Game_object/effect_gen/Ghost_ignite_gen.hpp"
#include "Game_object/effect_gen/Fire_ball_gen.hpp"
#include "Game_object/effect_gen/Inflame_eff_gen.hpp"
#include "Game_object/effect_gen/Screen_on_fire_gen.hpp"
#include "Game_object/card/status/Burn.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/Random.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"

namespace Monster
{
    Hexaghost::Hexaghost()
        :Abstraction::Monster_move_tracker<1, HexaghostAction>(0.0F, 0.0F, WIDTH, HEIGHT, HB_OFFSET_X, HB_OFFSET_Y, HP, IMG),
        body_angle(),
        body_angle_speed(1.0F),
        body_target_angle_speed(30.0F),
        body_float_speed(0.75F),
        body_y_timer(RUtil::Random::GetRandomFloat(0.0F, 360.0F)),
        body_y(std::sin(body_y_timer)*5.0F*Setting::SCALE),
        orbs(OrbCreater(orbs_pos)),
        burn_plus(false),
        current_orb_cnt(0),
        first_move(false)
    {

    }
    
    void Hexaghost::Action(Dungeon::Dungeon_shared &dungeon_shared){
        switch(current_move()){
            case HexaghostAction::Activate:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<Hexaghost, CallType>>(std::static_pointer_cast<Hexaghost>(shared_from_this()), CallType::Activate));
                break;
            case HexaghostAction::Divider:
                for(int i=0;i<DIVIDER_HITS;i++){
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Ghost_ignite_gen>(dungeon_shared.player->GetcX()+RUtil::Random::GetRandomFloat(-120.0F, 120.0F)*Setting::SCALE, dungeon_shared.player->GetcY()+RUtil::Random::GetRandomFloat(-120.0F, 120.0F)*Setting::SCALE), 0.05F));
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::blunt_heavy}, dungeon_shared.player));    
                }
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<Hexaghost, CallType>>(std::static_pointer_cast<Hexaghost>(shared_from_this()), CallType::Deactivate));
                break;
            case HexaghostAction::Inferno:
                {
                    burn_plus=true;
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Screen_on_fire_gen>(), 1.0F));
                    for(int i=0;i<INFERNO_HITS;i++)
                        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::fire}, dungeon_shared.player));
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Burn_plus_action>());
                    auto burn_card=std::make_shared<Card::Status::Burn>();
                    burn_card->CallUpgrade();
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Show_card_to_discard_action>(burn_card, 3));
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Wait_action>(1.0F));
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<Hexaghost, CallType>>(std::static_pointer_cast<Hexaghost>(shared_from_this()), CallType::Deactivate));
                }
                break;
            case HexaghostAction::Sear:
                {
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Fire_ball_gen>(GetcX(), GetcY(), dungeon_shared.player->GetcX(), dungeon_shared.player->GetcY()), 0.5F));
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::fire}, dungeon_shared.player));
                    auto burn_card=std::make_shared<Card::Status::Burn>();
                    if(burn_plus) burn_card->CallUpgrade();
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Show_card_to_discard_action>(burn_card, 1));
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<Hexaghost, CallType>>(std::static_pointer_cast<Hexaghost>(shared_from_this()), CallType::ActivateOrb));
                }
                break;
            case HexaghostAction::Tackle:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_capsule_action>(std::make_shared<Effect::Border_flash_eff>(RUtil::ToRGBA(RUtil::Colors::CHARTREUSE)), 0.0F, Action::Effect_capsule_action::Layer::normal));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Anim_set_action>(shared_from_this(), Character::Animation::ATTACK_SLOW));
                for(int i=0;i<TACKLE_HITS;i++)
                    dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Damage_action>(Damage_info{current_damage(), shared_from_this(), AttackType::fire}, dungeon_shared.player));    
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<Hexaghost, CallType>>(std::static_pointer_cast<Hexaghost>(shared_from_this()), CallType::ActivateOrb));
                break;
            case HexaghostAction::Inflame:
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Inflame_eff_gen>(GetcX(), GetcY()), 0.5F));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Gain_block_action>(shared_from_this(), 12));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Apply_power_action>(RUtil::Powers_Text_ID::Strength, 2, shared_from_this(), shared_from_this(), true));
                dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Call_action<Hexaghost, CallType>>(std::static_pointer_cast<Hexaghost>(shared_from_this()), CallType::ActivateOrb));
                break;
            default:
                break;
        }
    }

    void Hexaghost::Call(CallType val){
        switch(val){
            case CallType::Activate:
                body_target_angle_speed=120.0F;
                for(auto&it:orbs) it.activate();
                break;
            case CallType::ActivateOrb:
                orbs[current_orb_cnt-1].activate();
                break;
            case CallType::Deactivate:
                for(auto&it:orbs) it.deactivate();
                break;
        }
    }

    void Hexaghost::next_move(Dungeon::Dungeon_shared &dungeon_shared){
        if(!first_move){
            first_move=true;
            set_move(HexaghostAction::Activate, nullptr, Intent::unknown, dungeon_shared.player->get_powers());    
        }else if(current_move()==HexaghostAction::Activate){
            set_move(HexaghostAction::Divider, nullptr, Intent::attack, dungeon_shared.player->GetCurrentHP()/12+1, DIVIDER_HITS, dungeon_shared.player->get_powers());    
        }else{
            switch(PATTERN[current_orb_cnt]){
                case HexaghostAction::Inferno:
                    set_move(HexaghostAction::Inferno, nullptr, Intent::attack_debuff, INFERNO_DAMAGE, INFERNO_HITS, dungeon_shared.player->get_powers());
                    break;
                case HexaghostAction::Sear:
                    set_move(HexaghostAction::Sear, nullptr, Intent::attack_debuff, SEAR_DAMAGE, dungeon_shared.player->get_powers());
                    break;
                case HexaghostAction::Tackle:
                    set_move(HexaghostAction::Tackle, nullptr, Intent::attack, TACKLE_DAMAGE, TACKLE_HITS, dungeon_shared.player->get_powers());
                    break;
                case HexaghostAction::Inflame:
                    set_move(HexaghostAction::Inflame, nullptr, Intent::defend_buff, dungeon_shared.player->get_powers());
                    break;
                default:
                    break;
            }
            ++current_orb_cnt;
            if(current_orb_cnt>=static_cast<int>(PATTERN.size()))current_orb_cnt=0;
        }
    }

    static constexpr const char*BODY_IMG_FILES[]={"plasma1.png", "plasma2.png", "plasma3.png", "shadow.png"};
    
    template <int N>
    static inline auto &BODY_IMG(){
        static auto&IMG=RUtil::Image_book::GetTexture(static_cast<std::string>(RESOURCE_DIR"/Image/monster/Hexaghost/") + BODY_IMG_FILES[N]);
        return IMG;
    }

    void Hexaghost::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetColor(RUtil::WHITE, img_color_a);
        r2->draw(BODY_IMG<2>(), getAnimX()+orgX - 256.0F+12.0F*Setting::SCALE, getAnimY()+orgY - 256.0F+body_y*2.0F, 512.0F, 512.0F, body_angle[2], 256.0F, 256.0F, Setting::SCALE*0.95F, Setting::SCALE*0.95F);
        r2->draw(BODY_IMG<1>(), getAnimX()+orgX - 256.0F+6.0F*Setting::SCALE, getAnimY()+orgY - 256.0F+body_y, 512.0F, 512.0F, body_angle[1], 256.0F, 256.0F, Setting::SCALE, Setting::SCALE);
        r2->draw(BODY_IMG<0>(), getAnimX()+orgX - 256.0F, getAnimY()+orgY - 256.0F+body_y*0.5F, 512.0F, 512.0F, body_angle[0], 256.0F, 256.0F, Setting::SCALE, Setting::SCALE);
        r2->draw(BODY_IMG<3>(), getAnimX()+orgX - 256.0F+12.0F*Setting::SCALE, getAnimY()+orgY - 256.0F+body_y*0.25F-15.0F*Setting::SCALE, 512.0F, 512.0F, 0.0F, 256.0F, 256.0F, Setting::SCALE, Setting::SCALE);
        Monster::Monsters::render(r2);
    }

    void Hexaghost::update(){
        //body
        body_angle[0] += body_angle_speed * RUtil::Game_Input::delta_time();
        body_angle[1] += body_angle_speed/2.0F * RUtil::Game_Input::delta_time();
        body_angle[2] += body_angle_speed/3.0F * RUtil::Game_Input::delta_time();
        body_angle_speed = RUtil::Math::fadelerp(body_angle_speed, body_target_angle_speed);
        body_float_speed = body_angle_speed * RUtil::Game_Input::delta_time();
        body_y_timer += body_float_speed * RUtil::Game_Input::delta_time();
        body_y = std::sin(body_y_timer)*5.0F*Setting::SCALE;
        Monster::Monsters::update();
    }

    Hexaghost::Orb::Orb(float x, float y, int index)
        :_x(x*Setting::SCALE + RUtil::Random::GetRandomFloat(-10.0F, 10.0F)*Setting::SCALE),
        _y(y*Setting::SCALE + RUtil::Random::GetRandomFloat(-10.0F, 10.0F)*Setting::SCALE),
        offset_timer(RUtil::Random::GetRandomFloat(0.0F, 360.0F)),
        offset(std::sin(offset_timer)*5.0F*Setting::SCALE),
        activate_timer(static_cast<float>(index)*0.3F),
        is_activate(false),
        ignite(false),
        particle_timer(0.0F){}
    
    void Hexaghost::Orb::update(float x, float y, Dungeon::Dungeon_shared &dungeon_shared){
        offset_timer += (is_activate ? 4.0F : 2.0F) * RUtil::Game_Input::delta_time();
        offset = std::sin(offset_timer)*5.0F*Setting::SCALE;
        if(ignite){
            ignite=false;
            dungeon_shared.gen_group.AddTop(std::make_shared<EffectGen::Ghost_ignite_gen>(x+_x, y+_y));
        }
        particle_timer -= RUtil::Game_Input::delta_time();
        if(particle_timer<0.0F){
            particle_timer=0.06F;
            dungeon_shared.effs.AddTop(std::make_shared<Effect::Ghostly_fire_eff>(x+_x+offset, y+_y+offset, !is_activate));
        }
    }

    const std::shared_ptr<Draw::ReTexture> &Hexaghost::IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Hexaghost/core.png");
} // namespace Monster
