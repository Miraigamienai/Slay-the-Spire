#ifndef GAME_OBJECT_CHARACTER_MONSTER_MADGREMLIN_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_MADGREMLIN_HPP
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class MadGremlinAction
{
    Scratch
};
class MadGremlin final:public Monsters
{
public:
    MadGremlin(float offsetX,float offsetY);
    ~MadGremlin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    void damage(const Damage_info& damage_info) override;
    
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    static constexpr float WIDTH=150.0F*Setting::SCALE,
                        HIGHT=200.0F*Setting::SCALE;
    int m_damage=0;
    static constexpr int MAX_HP=20,
                        MIN_HP=24,
                        SCRATCH_DAMAGE=4;
    static constexpr float HPBarWidth=WIDTH*0.8F;
};
}
#endif