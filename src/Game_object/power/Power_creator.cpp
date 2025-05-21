#include "Game_object/power/Power_creator.hpp"
#include "RUtil/Powers_Text_Reader.hpp"

#include "Game_object/power/Weak_power.hpp"

namespace Power
{
    std::shared_ptr<Power::Powers> Power_creator::GetPowerByID(RUtil::Powers_Text_ID power_id){
        switch(power_id){
            case RUtil::Powers_Text_ID::Weakened: return std::make_shared<Weak_power>();
            default:return nullptr;
        }
    }
} // namespace Power
