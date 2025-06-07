#include <type_traits>
#include <array>

#include "Game_object/character/Monster/Monsters.hpp"
#include "Game_object/Damage_info.hpp"
#include "Game_object/effect/Debuff_particle_eff.hpp"
#include "Game_object/effect/Buff_particle_eff.hpp"
#include "Game_object/effect/Shield_particle_eff.hpp"
#include "Game_object/effect/Unknown_particle_eff.hpp"
#include "Game_object/effect/Stun_star_eff.hpp"
#include "Game_object/effect/Effect_pool.hpp"
#include "Game_object/effect_gen/Flash_intent_particle_gen.hpp"
#include "Game_object/action/Effect_gen_capsule_action.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Random.hpp"
#include "Draw/ReTexture.hpp"
#include "Draw/Draw_2D.hpp"

#include "Util/Logger.hpp"

namespace Monster
{
    static SETTING_CONSTEXPR float ORIGIN_X = Setting::WINDOW_WIDTH*0.75F,
                                   FLOOR_Y = Setting::WINDOW_HEIGHT*0.5F - 200.0F*Setting::SCALE;
    static SETTING_CONSTEXPR float INTENT_HB_W=64.0F*Setting::SCALE;

    template <int N>
    static inline auto &ATK_TIP_IMG(){
        static auto&IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/intent/tip/" + std::to_string(N) + ".png");
        return IMG;
    }

    static inline auto &ATK_TIP_IMG(int amt){
        if(amt<5) return ATK_TIP_IMG<1>();
        if(amt<10) return ATK_TIP_IMG<2>();
        if(amt<15) return ATK_TIP_IMG<3>();
        if(amt<20) return ATK_TIP_IMG<4>();
        if(amt<25) return ATK_TIP_IMG<5>();
        if(amt<30) return ATK_TIP_IMG<6>();
        return ATK_TIP_IMG<7>();
    }

    template <int N>
    static inline auto &ATK_INTENT_IMG(){
        static auto&IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/intent/attack/attack_intent_" + std::to_string(N) + ".png");
        return IMG;
    }

    static inline auto &ATK_INTENT_IMG(int amt){
        if(amt<5) return ATK_INTENT_IMG<1>();
        if(amt<10) return ATK_INTENT_IMG<2>();
        if(amt<15) return ATK_INTENT_IMG<3>();
        if(amt<20) return ATK_INTENT_IMG<4>();
        if(amt<25) return ATK_INTENT_IMG<5>();
        if(amt<30) return ATK_INTENT_IMG<6>();
        return ATK_INTENT_IMG<7>();
    }

    static constexpr std::array<const char*, static_cast<int>(Intent::NONE)> TIP_IMG_FILE_POS=[]()constexpr{
        std::array<const char*, static_cast<int>(Intent::NONE)> temp{};
        temp[static_cast<int>(Intent::attack_buff)]   = RESOURCE_DIR"/Image/intent/attackBuff.png";
        temp[static_cast<int>(Intent::attack_debuff)] = RESOURCE_DIR"/Image/intent/attackDebuff.png";
        temp[static_cast<int>(Intent::attack_defend)] = RESOURCE_DIR"/Image/intent/attackDefend.png";
        temp[static_cast<int>(Intent::buff)]          = RESOURCE_DIR"/Image/intent/buff1.png";
        temp[static_cast<int>(Intent::debuff)]        = RESOURCE_DIR"/Image/intent/debuff1.png";
        temp[static_cast<int>(Intent::strong_debuff)] = RESOURCE_DIR"/Image/intent/debuff2.png";
        temp[static_cast<int>(Intent::defend)]        =
        temp[static_cast<int>(Intent::defend_debuff)] = RESOURCE_DIR"/Image/intent/defend.png";
        temp[static_cast<int>(Intent::defend_buff)]   = RESOURCE_DIR"/Image/intent/defendBuff.png";
        temp[static_cast<int>(Intent::escape)]        = RESOURCE_DIR"/Image/intent/escape.png";
        temp[static_cast<int>(Intent::magic)]         = RESOURCE_DIR"/Image/intent/magic.png";
        temp[static_cast<int>(Intent::sleep)]         = RESOURCE_DIR"/Image/intent/sleep.png";
        temp[static_cast<int>(Intent::stun)]          = RESOURCE_DIR"/Image/intent/stun.png";
        temp[static_cast<int>(Intent::unknown)]       = RESOURCE_DIR"/Image/intent/unknown.png";
        return temp;
    }();
    
    template <Intent I>
    using TIP_IMG_TYPE = std::enable_if_t<I != Intent::attack && I != Intent::NONE, const std::shared_ptr<Draw::ReTexture> &>;

    template <Intent I>
    static inline TIP_IMG_TYPE<I> TIP_IMG(){
        static auto&IMG=RUtil::Image_book::GetTexture(TIP_IMG_FILE_POS[static_cast<int>(I)]);
        return IMG;
    }

    static constexpr std::array<const char*, static_cast<int>(Intent::NONE)> INTENT_IMG_FILE_POS=[]()constexpr{
        std::array<const char*, static_cast<int>(Intent::NONE)> temp{};
        temp[static_cast<int>(Intent::buff)]          = RESOURCE_DIR"/Image/intent/buff1L.png";
        temp[static_cast<int>(Intent::debuff)]        = RESOURCE_DIR"/Image/intent/debuff1L.png";
        temp[static_cast<int>(Intent::strong_debuff)] = RESOURCE_DIR"/Image/intent/debuff2L.png";
        temp[static_cast<int>(Intent::defend)]        =
        temp[static_cast<int>(Intent::defend_debuff)] = RESOURCE_DIR"/Image/intent/defendL.png";
        temp[static_cast<int>(Intent::defend_buff)]   = RESOURCE_DIR"/Image/intent/defendBuffL.png";
        temp[static_cast<int>(Intent::escape)]        = RESOURCE_DIR"/Image/intent/escapeL.png";
        temp[static_cast<int>(Intent::magic)]         = RESOURCE_DIR"/Image/intent/magicL.png";
        temp[static_cast<int>(Intent::sleep)]         = RESOURCE_DIR"/Image/intent/sleepL.png";
        temp[static_cast<int>(Intent::stun)]          = RESOURCE_DIR"/Image/intent/stunL.png";
        temp[static_cast<int>(Intent::unknown)]       = RESOURCE_DIR"/Image/intent/unknownL.png";
        return temp;
    }();

    template <Intent I>
    using INTENT_IMG_TYPE = std::enable_if_t<I != Intent::attack && I != Intent::attack_buff && I != Intent::attack_debuff && I != Intent::attack_defend && I != Intent::NONE, const std::shared_ptr<Draw::ReTexture> &>;

    template <Intent I>
    static inline INTENT_IMG_TYPE<I> INTENT_IMG(){
        static auto&IMG=RUtil::Image_book::GetTexture(INTENT_IMG_FILE_POS[static_cast<int>(I)]);
        return IMG;
    }

    static inline auto&INTENT_IMG(Intent intent, int amt=0){
        switch(intent){
            case Intent::buff:return INTENT_IMG<Intent::buff>();
            case Intent::debuff:return INTENT_IMG<Intent::debuff>();
            case Intent::strong_debuff:return INTENT_IMG<Intent::strong_debuff>();
            case Intent::defend:return INTENT_IMG<Intent::defend>();
            case Intent::defend_debuff:return INTENT_IMG<Intent::defend_debuff>();
            case Intent::defend_buff:return INTENT_IMG<Intent::defend_buff>();
            case Intent::escape:return INTENT_IMG<Intent::escape>();
            case Intent::magic:return INTENT_IMG<Intent::magic>();
            case Intent::sleep:return INTENT_IMG<Intent::sleep>();
            case Intent::stun:return INTENT_IMG<Intent::stun>();
            case Intent::unknown:return INTENT_IMG<Intent::unknown>();
            case Intent::attack:
            case Intent::attack_buff:
            case Intent::attack_debuff:
            case Intent::attack_defend:
                return ATK_INTENT_IMG(amt);
            default:
                LOG_ERROR("Try to get intent_img with{}", static_cast<int>(intent));
                return INTENT_IMG<Intent::buff>();
        }
    }

    Monsters::Monsters(float offset_x, float offset_y, float width, float height, 
        float hb_offset_x, float hb_offset_y, int HP, const std::shared_ptr<Draw::ReTexture> &img)
        :Character::Characters(Character::CharacterType::MONSTER, ORIGIN_X+offset_x*Setting::SCALE, FLOOR_Y+offset_y*Setting::SCALE+height/2.0F, width, height, hb_offset_x, hb_offset_y, HP),
        img_color_a(1.0F),
        img(img),
        dying_fade_timer(0.0F),
        move(),
        intent_tip_img(nullptr),
        intent_hb(INTENT_HB_W, INTENT_HB_W),
        intent_a(0.0F),
        intent_target_a(0.0F),
        intent_offset_y(0.0F),
        intent_offset_timer(RUtil::Random::GetRandomFloat(0.0F, 360.0F)),
        intent_angle(0.0F),
        intent_particle_timer(0.0F)
    {
        intent_hb.move(GetcX(), GetcY() + GetHeight()/2.0F + INTENT_HB_W/2.0F);
    }
    

    void Monsters::damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared){
        if(current_HP<=0 || escaping) return;

        int dmg = damage_info.dmg;
        const bool had_block = GetCurrentBlock() > 0;
        if(had_block){
            if(damage_info.dmg > GetCurrentBlock()){
                const auto temp=GetCurrentBlock();
                ReduceBlock(temp, dungeon_shared);
                dmg -= temp;
            }else{
                ReduceBlock(damage_info.dmg, dungeon_shared);
                dmg = 0;
            }
        }
        
        //TODO: effs
        if(dmg>0){
            if(damage_info.src.get()!=this) use_animation<Character::Animation::STAGGER>();
            //strike eff if hp!=0
            current_HP-=dmg;
            if(current_HP<0)current_HP=0;
            health_update_event();
        }else{
            //dmg==0
            if(!had_block && GetCurrentBlock()==0){
                //strike eff
            }else{
                //block eff
            }
        }

        if(current_HP<=0){
            dying_fade_timer = FADE_TIME;
        }
    }

    void Monsters::update(){
        //TODO: escape
        update_HP_and_power();
        update_animation();
        //fade update
        if(current_HP<=0 && dying_fade_timer!=0.0F){
            dying_fade_timer-=RUtil::Game_Input::delta_time();
            if(dying_fade_timer<0.0F) dying_fade_timer=0.0F;
            img_color_a = RUtil::Math::varlerp(img_color_a, 0.0F, 3.0F, 0.005F);
        }
        //intent alhpa
        if(intent_a<intent_target_a){
            intent_a+=RUtil::Game_Input::delta_time();
            if(intent_a>intent_target_a) intent_a=intent_target_a;
        }else if(intent_a>intent_target_a){
            intent_a-=RUtil::Game_Input::delta_time();
            if(intent_a<intent_target_a) intent_a=intent_target_a;
        }
        //intent angle
        if(move.intent!=Intent::debuff && move.intent!=Intent::strong_debuff) intent_angle=0.0F;
        else intent_angle+=RUtil::Game_Input::delta_time()*150.0F;
        //intent vfx
        intent_effs.update();
        intent_back_effs.update();
        if(!current_HP<=0 && intent_a>0.0F) update_intent_vfx();
        //intent hb
        intent_hb.move(GetcX(), GetcY() + GetHeight()/2.0F + INTENT_HB_W/2.0F);
        intent_hb.update();
    }

    void Monsters::update_intent_vfx(){
        //offset_y
        intent_offset_y = std::sin(intent_offset_timer)*5.0F*Setting::SCALE;
        intent_offset_timer += RUtil::Game_Input::delta_time()*4.0F;
        //particle
        intent_particle_timer-=RUtil::Game_Input::delta_time();
        if(intent_particle_timer<0.0F){
            switch(move.intent){
                case Intent::stun:
                    intent_particle_timer=0.67F;
                    intent_effs.AddTop(Effect::Effect_pool<Effect::Stun_star_eff>::GetEffect(intent_hb.CenterX(), intent_hb.CenterY()));
                    break;
                case Intent::unknown:
                    intent_particle_timer=0.5F;
                    if(Effect::Unknown_particle_eff::is_render_back()) 
                        intent_back_effs.AddTop(Effect::Effect_pool<Effect::Unknown_particle_eff>::GetEffect(intent_hb.CenterX(), intent_hb.CenterY()));
                    else
                        intent_effs.AddTop(Effect::Effect_pool<Effect::Unknown_particle_eff>::GetEffect(intent_hb.CenterX(), intent_hb.CenterY()));
                    break;
                case Intent::attack_defend:
                    intent_particle_timer=0.5F;
                    intent_back_effs.AddTop(Effect::Effect_pool<Effect::Shield_particle_eff>::GetEffect(intent_hb.CenterX(), intent_hb.CenterY()));
                    break;
                case Intent::buff:
                case Intent::attack_buff:
                case Intent::defend_buff:
                    intent_particle_timer=0.1F;
                    if(RUtil::Random::GetRandomBoolean())
                        intent_back_effs.AddTop(Effect::Effect_pool<Effect::Buff_particle_eff>::GetEffect(intent_hb.CenterX(), intent_hb.CenterY()));
                    else
                        intent_effs.AddTop(Effect::Effect_pool<Effect::Buff_particle_eff>::GetEffect(intent_hb.CenterX(), intent_hb.CenterY()));    
                    break;
                case Intent::debuff:
                case Intent::strong_debuff:
                case Intent::attack_debuff:
                case Intent::defend_debuff:
                    intent_particle_timer=1.0F;
                    if(Effect::Debuff_particle_eff::is_render_back()) 
                        intent_back_effs.AddTop(Effect::Effect_pool<Effect::Debuff_particle_eff>::GetEffect(intent_hb.CenterX(), intent_hb.CenterY()));
                    else
                        intent_effs.AddTop(Effect::Effect_pool<Effect::Debuff_particle_eff>::GetEffect(intent_hb.CenterX(), intent_hb.CenterY()));
                    break;
                default:
                    break;
            }
        }
    }

    void Monsters::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        //img
        if(img!=nullptr){
            r2->SetColor(RUtil::WHITE, img_color_a);
            r2->draw(img, getAnimX()+orgX-GetWidth()/2.0F, getAnimY()+orgY-GetHeight()/2.0F, GetWidth(), GetHeight());
        }
        //intent
        if(!current_HP<=0 && !IsInDyingFade() && intent_a!=0.0F){
            //img & effs
            intent_back_effs.render(r2);
            r2->SetColor(RUtil::WHITE, intent_a);
            r2->draw(move.intent_img, intent_hb.CenterX()-64.0F, intent_hb.CenterY()-64.0F+intent_offset_y, 128.0F, 128.0F, intent_angle, 64.0F, 64.0F, Setting::SCALE, Setting::SCALE); 
            intent_effs.render(r2);
            //num
            if(move.intent==Intent::attack||move.intent==Intent::attack_buff||move.intent==Intent::attack_debuff||move.intent==Intent::attack_defend){
                if(move.is_multi_dmg) s_intent_num_drawer.render_top_left_with_bg(r2, std::to_string(move.damage) + "x" + std::to_string(move.multiplier), intent_hb.CenterX()-30.0F*Setting::SCALE, intent_hb.CenterY()+intent_offset_y-12.0F*Setting::SCALE, Setting::SCALE, RUtil::WHITE, intent_a);
                else s_intent_num_drawer.render_top_left_with_bg(r2, std::to_string(move.damage), intent_hb.CenterX()-30.0F*Setting::SCALE, intent_hb.CenterY()+intent_offset_y-12.0F*Setting::SCALE, Setting::SCALE, RUtil::WHITE, intent_a);
            }
        }
        render_HP_and_power(r2);
    }

    void Monsters::flash_intent(Dungeon::Dungeon_shared &dungeon_shared){
        intent_target_a=0.0F;
        dungeon_shared.action_group_handler.AddActionBot(std::make_shared<Action::Effect_gen_capsule_action>(std::make_shared<EffectGen::Flash_intent_particle_gen>(intent_hb.CenterX()-static_cast<float>(move.intent_img->GetWidth())/2.0F, intent_hb.CenterY()-static_cast<float>(move.intent_img->GetHeight())/2.0F, move.intent_img), 1.5F));
    }

    void Monsters::refresh_dmg_display(const Power::Power_group &player_powers){
        float dmg = static_cast<float>(move.base_damage);
        for(const auto&it:this->powers) dmg = it->calculate_damage_dealt(dmg);
        for(const auto&it:player_powers) dmg = it->calculate_damage_receive(dmg);
        for(const auto&it:this->powers) dmg = it->calculate_final_damage_dealt(dmg);
        for(const auto&it:player_powers) dmg = it->calculate_final_damage_receive(dmg);
        move.damage = static_cast<int>(dmg);
        if(move.damage < 0) move.damage = 0;
        move.intent_img=INTENT_IMG(move.intent, (move.is_multi_dmg ? move.damage*move.multiplier : move.damage));
    }

    void Monsters::set_move(const std::shared_ptr<Draw::Text_layout> &move_name, Intent intent, int base_damage, int multiplier, const Power::Power_group &player_powers){
        this->move=Move{move_name, INTENT_IMG(intent, base_damage*multiplier), intent, true, multiplier, base_damage, 0};
        set_move(player_powers);
    }

    void Monsters::set_move(const std::shared_ptr<Draw::Text_layout> &move_name, Intent intent, int base_damage, const Power::Power_group &player_powers){
        this->move=Move{move_name, INTENT_IMG(intent, base_damage), intent, false, 0, base_damage, 0};
        set_move(player_powers);
    }

    void Monsters::set_move(const std::shared_ptr<Draw::Text_layout> &move_name, Intent intent, const Power::Power_group &player_powers){
        this->move=Move{move_name, INTENT_IMG(intent), intent, false, 0, 0, 0};
        set_move(player_powers);
    }

    void Monsters::refresh_intent_tip(){
        auto &TEXT_VEC=RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::AbstractMonster);
        switch(move.intent){
            case Intent::attack:
                intent_tip.change_title(TEXT_VEC[0]);
                if(move.is_multi_dmg){
                    intent_tip.change_body(TEXT_VEC[1]);
                    intent_tip_img=ATK_TIP_IMG(move.damage * move.multiplier);
                }else{
                    intent_tip.change_body(TEXT_VEC[2]);
                    intent_tip_img=ATK_TIP_IMG(move.damage);
                }
                break;
            case Intent::attack_buff:
                intent_tip.change_title(TEXT_VEC[3]);
                if(move.is_multi_dmg) intent_tip.change_body(TEXT_VEC[4]);
                else intent_tip.change_body(TEXT_VEC[5]);
                intent_tip_img=TIP_IMG<Intent::attack_buff>();
                break;
            case Intent::attack_debuff:
                intent_tip.change_title(TEXT_VEC[6]);
                intent_tip.change_body(TEXT_VEC[7]);
                intent_tip_img=TIP_IMG<Intent::attack_debuff>();
                break;
            case Intent::attack_defend:
                intent_tip.change_title(TEXT_VEC[0]);
                if(move.is_multi_dmg) intent_tip.change_body(TEXT_VEC[8]);
                else intent_tip.change_body(TEXT_VEC[9]);
                intent_tip_img=TIP_IMG<Intent::attack_defend>();
                break;
            case Intent::buff:
                intent_tip.change_title(TEXT_VEC[6]);
                intent_tip.change_body(TEXT_VEC[10]);
                intent_tip_img=TIP_IMG<Intent::buff>();
                break;
            case Intent::debuff:
                intent_tip.change_title(TEXT_VEC[6]);
                intent_tip.change_body(TEXT_VEC[11]);
                intent_tip_img=TIP_IMG<Intent::debuff>();
                break;
            case Intent::strong_debuff:
                intent_tip.change_title(TEXT_VEC[6]);
                intent_tip.change_body(TEXT_VEC[12]);
                intent_tip_img=TIP_IMG<Intent::strong_debuff>();
                break;
            case Intent::defend:
                intent_tip.change_title(TEXT_VEC[13]);
                intent_tip.change_body(TEXT_VEC[14]);
                intent_tip_img=TIP_IMG<Intent::defend>();
                break;
            case Intent::defend_debuff:
                intent_tip.change_title(TEXT_VEC[13]);
                intent_tip.change_body(TEXT_VEC[15]);
                intent_tip_img=TIP_IMG<Intent::defend_debuff>();
                break;
            case Intent::defend_buff:
                intent_tip.change_title(TEXT_VEC[13]);
                intent_tip.change_body(TEXT_VEC[16]);
                intent_tip_img=TIP_IMG<Intent::defend_buff>();
                break;
            case Intent::escape:
                intent_tip.change_title(TEXT_VEC[17]);
                intent_tip.change_body(TEXT_VEC[18]);
                intent_tip_img=TIP_IMG<Intent::escape>();
                break;
            case Intent::magic:
                intent_tip.change_title(TEXT_VEC[19]);
                intent_tip.change_body(TEXT_VEC[20]);
                intent_tip_img=TIP_IMG<Intent::magic>();
                break;
            case Intent::sleep:
                intent_tip.change_title(TEXT_VEC[21]);
                intent_tip.change_body(TEXT_VEC[22]);
                intent_tip_img=TIP_IMG<Intent::sleep>();
                break;
            case Intent::stun:
                intent_tip.change_title(TEXT_VEC[23]);
                intent_tip.change_body(TEXT_VEC[24]);
                intent_tip_img=TIP_IMG<Intent::stun>();
                break;
            case Intent::unknown:
                intent_tip.change_title(TEXT_VEC[25]);
                intent_tip.change_body(TEXT_VEC[26]);
                intent_tip_img=TIP_IMG<Intent::unknown>();
                break;
            default:
                intent_tip.change_title(nullptr);
                intent_tip.change_body(nullptr);
                intent_tip_img=nullptr;
                break;
        }
    }

    const Draw::NumberDrawer Monsters::s_intent_num_drawer{INTENT_FONTSIZE, FontWeight::bold};
} // namespace Monster