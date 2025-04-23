#include "Game_object/character/Monster_group_creater.hpp"
#include "Game_object/character/Monster_group.hpp"
#include "Game_object/character/Monster/Cultist.hpp"
#include "Game_object/character/Monster/FatGremlin.hpp"
#include "RUtil/Random.hpp"

#include "Util/Logger.hpp"

namespace Monster{
    void Monster_group_creater::CreateGroup(Monster_group &group,GroupName group_name,RUtil::Random &rng){
        // switch(group_name){
        //     case GroupName::Blue_Slaver:
                
        //         return;
        //     case GroupName::Cultist:
        //         group.AddTop(std::make_shared<Cultist>());
        //         return;
        //     default:
        //         LOG_ERROR("The Group:{} is has not be set yet",static_cast<int>(group_name));
        //         return;
        // }
        group.AddTop(std::make_shared<FatGremlin>());
        
    }
}