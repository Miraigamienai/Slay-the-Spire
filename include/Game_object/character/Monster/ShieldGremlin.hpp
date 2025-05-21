#ifndef GAME_OBJECT_CHARACTER_MONSTER_SHIELDGREMLIN_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_SHIELDGREMLIN_HPP
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class ShieldGremlinAction
{
    Protect,
    ShieldBash,
    None
};
class ShieldGremlin final:public Monsters
{
public:
    ShieldGremlin(float offsetX,float offsetY);
    ~ShieldGremlin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    
    
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    static constexpr float WIDTH=150.0F*Setting::SCALE,
                        HIGHT=200.0F*Setting::SCALE;
    static constexpr int MAX_HP=15,
                        MIN_HP=12,
                        PROTECT_BLOCK=7,
                        SHIELD_BASH_DAMAGE=6;
    static constexpr float HPBarWidth=WIDTH*0.8F;
};
}
#endif