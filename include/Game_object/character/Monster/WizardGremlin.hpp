#ifndef GAME_OBJECT_CHARACTER_MONSTER_WIZARDGREMLIN_HPP
#define GAME_OBJECT_CHARACTER_MONSTER_WIZARDGREMLIN_HPP
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class WizardGremlinAction
{
    Charging,
    UltimateBlast
};
class WizardGremlin final:public Monsters
{
public:
    WizardGremlin(float offsetX,float offsetY);
    ~WizardGremlin()override=default;
    void Action(WizardGremlinAction action_type);
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    
    
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr float WIDTH=180.0F*Setting::SCALE,
                        HIGHT=130.0F*Setting::SCALE;
    static constexpr int MAX_HP=25,
                        MIN_HP=23,
                        DAMAGE=25;
    static constexpr float HPBarWidth=WIDTH*0.8F;
};
}
#endif