#ifndef GAME_OBJECT_CHARACTER_MONSTER_WIZARDGREMLIN_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_WIZARDGREMLIN_HPP
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class WizardGremlinAction
{
    Charging,
    UltimateBlast,
    None
};
class WizardGremlin final:public Monsters
{
public:
    WizardGremlin(float offsetX,float offsetY);
    ~WizardGremlin()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;

    
    
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    static constexpr float WIDTH=180.0F*Setting::SCALE,
                        HIGHT=130.0F*Setting::SCALE;
    static constexpr int MAX_HP=25,
                        MIN_HP=23,
                        ULTIMATE_BLAST=25;
    static constexpr float HPBarWidth=WIDTH*0.8F;
    bool isFirstAttack=true;
    int ChargingCounter=0;
};
}
#endif