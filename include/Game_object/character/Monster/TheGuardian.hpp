#pragma once

#include "Game_object/abstraction/Monster_move_tracker.hpp"
#include "RUtil/Weighted_index_picker.hpp"

namespace Monster{
enum class TheGuardianAction
{
    Bellow,         // 鼓風 (增加力量)
    Rush,           // 衝撞 (造成傷害)
    SkullBash,      // 顱擊 (造成傷害+易傷)
    DefensiveMode,  // 防禦模式 (獲得護甲，切換到防禦姿態)
    RollAttack,     // 滾動攻擊 (造成傷害，在防禦模式)
    TwinSlam,       // 雙重打擊 (造成2次傷害，在防禦模式)
    Whirlwind,      // 旋風 (造成多次傷害，在防禦模式)
    ChargedUp       // 充能完畢 (從防禦模式返回攻擊模式)
};

class TheGuardian final:public Abstraction::Monster_move_tracker<2, TheGuardianAction>
{
public:
    TheGuardian(float offset_x, float offset_y, RUtil::Random& rng);
    ~TheGuardian()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void next_move(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override; // 新增渲染方法來處理不同模式的圖片
private:
    bool first_move;
    bool in_defensive_mode;
    int defensive_mode_counter;
    
    static constexpr float WIDTH=260.0F*Setting::SCALE,
                           HEIGHT=170.0F*Setting::SCALE,
                           HB_OFFSET_X=0.0F,
                           HB_OFFSET_Y=-25.0F*Setting::SCALE;
    static constexpr int MAX_HP=240,
                         MIN_HP=240,
                         BELLOWS_STRENGTH=3,
                         RUSH_DAMAGE=9,
                         SKULL_BASH_DAMAGE=8,
                         SKULL_BASH_VULNERABLE=2,
                         ROLL_ATTACK_DAMAGE=5, 
                         TWIN_SLAM_DAMAGE=8,
                         TWIN_SLAM_TIMES=2,
                         WHIRLWIND_DAMAGE=5,
                         WHIRLWIND_TIMES=4,
                         DEFENSIVE_MODE_BLOCK=20;
    static const std::shared_ptr<Draw::ReTexture> &IMG; // 攻擊模式圖片
    static const std::shared_ptr<Draw::ReTexture> &DEF_IMG; // 防禦模式圖片
    // 攻擊模式動作權重
    static constexpr auto attack_move_dist=RUtil::make_weighted_index_picker(std::array{33.0F, 33.0F, 33.0F, 0.0F, 0.0F, 0.0F, 0.0F, 0.0F});
    // 防禦模式動作權重
    static constexpr auto defensive_move_dist=RUtil::make_weighted_index_picker(std::array{0.0F, 0.0F, 0.0F, 0.0F, 33.0F, 33.0F, 33.0F, 0.0F});
};
}