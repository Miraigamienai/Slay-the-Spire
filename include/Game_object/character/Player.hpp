#ifndef GAME_OBJECT_CHARACTER_PLAYER
#define GAME_OBJECT_CHARACTER_PLAYER
#include "Game_object/character/Characters.hpp"
#include "RUtil/Some_Math.hpp"

//fwd decl
namespace Dungeon{
    struct Dungeon_shared;
}

namespace Character{
enum class PlayerType:int{
    Ironclad,
    Silent,
    Defect,
    Watcher,
    NONE
};
class Player final :public Characters
{
public:
    Player();
    virtual ~Player()=default;
    void damage(const Damage_info& damage_info, Dungeon::Dungeon_shared &dungeon_shared, bool deduct_block);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    void update()override{
        update_HP_and_power();
        update_animation();
    }
    const PlayerType player_type;

    int GetGold()const noexcept{return gold;}
    void ReduceGold(int value)noexcept{gold-=value;}
    void AddGold(int value)noexcept{gold+=value;}
    void ReduceEnergy(int value, Dungeon::Dungeon_shared &dungeon_shared);
    void AddEnergy(int value, Dungeon::Dungeon_shared &dungeon_shared);
    const int &GetCurrEnergy()const noexcept{return current_energy;}
    const int &GetMaxEnergy()const noexcept{return max_energy;}
    constexpr Uint32 GetCardTrailColor()const noexcept(noexcept(RUtil::Math::GetColorUint32_RGB(1.0F,0.4F,0.1F))){return RUtil::Math::GetColorUint32_RGB(1.0F,0.4F,0.1F);}
    constexpr Uint32 GetCardRenderColor()const noexcept{return 0xff341cff;}
private:
    int max_energy,current_energy;
    int gold;
    static const std::shared_ptr<Draw::ReTexture> &img, &img_died;
    static constexpr float WIDTH=290.0F*Setting::SCALE,
                           HEIGHT=240.0F*Setting::SCALE,
                           HB_OFFSET_X=-4.0F*Setting::SCALE,
                           HB_OFFSET_Y=-16.0F*Setting::SCALE;
};
}
#endif