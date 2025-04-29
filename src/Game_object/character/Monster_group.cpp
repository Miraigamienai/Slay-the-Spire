#include "Game_object/character/Monster_group.hpp"
#include "Game_object/character/Monster/Monsters.hpp"
#include "Draw/Draw_2D.hpp"

namespace Monster
{
    std::shared_ptr<Monsters> Monster_group::GetHoveredMonster()const{
        for(const auto &it:box) if(it->hovered()) return it;
        return nullptr;
    }
    void Monster_group::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        for(const auto &it:box) it->render(r2);
    }
    void Monster_group::update(){
        for(const auto &it:box) it->update();
    }
    bool Monster_group::IsAllDie()const{
        for(const auto &it:box) 
            if(!it->IsDie()) return false;
        return true;
    }
} // namespace Monster
