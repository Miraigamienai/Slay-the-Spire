#pragma once

#include <utility>

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class CallType{
    Activate,
    ActivateOrb,
    Deactivate
};
enum class HexaghostAction
{
    Activate,
    Divider,
    Inferno,
    Sear,
    Tackle,
    Inflame
};
class Hexaghost final:public Abstraction::Monster_move_tracker<1, HexaghostAction>
{
public:
    Hexaghost(Dungeon::Dungeon_shared &dungeon_shared);
    ~Hexaghost()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void update()override;
    void Call(CallType val);
private:
    class Orb{
    public:
        Orb(float x, float y, int index);
        void activate()noexcept{is_activate=ignite=true;hide=false;}
        void deactivate()noexcept{is_activate=false;}
        void update(float x, float y, Dungeon::Dungeon_shared &dungeon_shared);
    private:
        const float _x, _y;
        float offset_timer, offset;
        float activate_timer;
        bool is_activate;
        bool ignite;
        float particle_timer;
        bool hide;
    };
    Dungeon::Dungeon_shared &dungeon_shared;
    float body_angle[3];
    float body_angle_speed, body_target_angle_speed;
    float body_float_speed;
    float body_y_timer;
    float body_y;
    std::array<Orb, 6> orbs;
    bool burn_plus;
    int current_orb_cnt;
    bool first_move;
    template <typename T, size_t...Is>
    static auto OrbCreater(const T&pos_arr, std::index_sequence<Is...>){
        return std::array{Orb{pos_arr[Is].first, pos_arr[Is].second, static_cast<int>(Is)}...};
    }
    template <typename T, size_t N>
    static auto OrbCreater(const std::array<T, N>&pos_arr){
        return OrbCreater(pos_arr, std::make_index_sequence<N>{});
    }
    static constexpr float WIDTH=450.0F*Setting::SCALE,
                           HEIGHT=450.0F*Setting::SCALE,
                           HB_OFFSET_X=20.0F*Setting::SCALE,
                           HB_OFFSET_Y=0.0F*Setting::SCALE;
    static constexpr int HP=250,
                         DIVIDER_HITS=6,
                         INFERNO_DAMAGE=2,
                         INFERNO_HITS=6,
                         SEAR_DAMAGE=6,
                         TACKLE_DAMAGE=5,
                         TACKLE_HITS=2;
    // static constexpr auto orbs_pos=std::array{std::pair{-90.0F, 380.0F-225}, std::pair{90.0F, 380.0F}, std::pair{160.0F, 250.0F}, std::pair{90.0F, 120.0F}, std::pair{-90.0F, 120.0F}, std::pair{-160.0F, 250.0F}};
    static constexpr auto orbs_pos=std::array{std::pair{-90.0F, 140.0F}, std::pair{90.0F, 140.0F}, std::pair{160.0F, 10.0F}, std::pair{90.0F, -120.0F}, std::pair{-90.0F, -120.0F}, std::pair{-160.0F, 10.0F}};
    static constexpr auto PATTERN=std::array{HexaghostAction::Sear, HexaghostAction::Tackle, HexaghostAction::Sear, HexaghostAction::Inflame, HexaghostAction::Tackle, HexaghostAction::Sear, HexaghostAction::Inferno};
    static const std::shared_ptr<Draw::ReTexture> &IMG;
};
}