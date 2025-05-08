#ifndef GAME_OBJECT_CHARACTER_MONSTER_ACIDSLIMEL
#define GAME_OBJECT_CHARACTER_MONSTER_ACIDSLIMEL
#include "Game_object/character/Monster/Monsters.hpp"

namespace Monster{
enum class AcidSlimeLAction
{
    CorrosiveSpit,
    Lick,
    Tackle,
    Split,
    None
};
class AcidSlimeL final:public Monsters
{
public:
    AcidSlimeL(float offsetX,float offsetY);
    ~AcidSlimeL()override=default;
    void Action(Dungeon::Dungeon_shared &dungeon_shared) override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2) const override;
    // void apply(const std::shared_ptr<Action::Action_group> &action_group)const override;
private:
    
    static const std::shared_ptr<Draw::ReTexture> &img;
    static constexpr int WIDTH=300.0F*Setting::SCALE,
                         HIGHT=180.0F*Setting::SCALE;
    static constexpr int MAX_HP=69,
                         MIN_HP=65,
                         TACKLE_DAMAGE=16,
                         CORROSIVE_SPIT_DAMAGE=11;
    static constexpr int HPBarWidth=WIDTH*0.8F;
    Monster::AcidSlimeLAction currentAction=Monster::AcidSlimeLAction::None;
    static constexpr float ActionProbability[3]={30.0F,40.0F,30.0F};
};
}
#endif