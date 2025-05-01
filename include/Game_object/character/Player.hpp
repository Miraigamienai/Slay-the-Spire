#ifndef GAME_OBJECT_CHARACTER_PLAYER
#define GAME_OBJECT_CHARACTER_PLAYER
#include "Game_object/character/Characters.hpp"
#include "RUtil/Some_Math.hpp"

//fwd decl
namespace Dungeon{
    class Dungeon_shared;
}

namespace Character{
enum class PlayerType{
    Ironclad,
    Silent,
    Defect,
    Watcher
};
class Player final :public Characters
{
public:
    Player();
    virtual ~Player()=default;
    void damage(const Damage_info& damage_info)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    const PlayerType player_type;

    void ReduceEnergy(int value, Dungeon::Dungeon_shared &dungeon_shared);
    void AddEnergy(int value, Dungeon::Dungeon_shared &dungeon_shared);
    const int &GetCurrEnergy()const noexcept{return current_energy;}
    const int &GetMaxEnergy()const noexcept{return max_energy;}
    constexpr Uint32 GetCardTrailColor()const noexcept(noexcept(RUtil::Math::GetColorUint32_RGB(1.0F,0.4F,0.1F))){return RUtil::Math::GetColorUint32_RGB(1.0F,0.4F,0.1F);}
    constexpr Uint32 GetCardRenderColor()const noexcept{return 0xff341cff;}
private:
    int max_energy,current_energy;
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr int WIDTH_OFFSET=-800.0F*Setting::SCALE,
                        HEIGHT_OFFSET=-200.0F*Setting::SCALE;
    static constexpr int WIDTH=300.0F*Setting::SCALE,
                        HIGHT=200.0F*Setting::SCALE;
    static constexpr int HPBarWidth=WIDTH*0.5F;
};
}
#endif