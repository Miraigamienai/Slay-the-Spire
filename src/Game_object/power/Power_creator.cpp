#include "Game_object/power/Power_creator.hpp"
#include "RUtil/Powers_Text_Reader.hpp"

#include "Game_object/power/Barricade_power.hpp"
#include "Game_object/power/Frail_power.hpp"
#include "Game_object/power/Ritual_power.hpp"
#include "Game_object/power/Strength_power.hpp"
#include "Game_object/power/Vulnerable_power.hpp"
#include "Game_object/power/Weak_power.hpp"

#include "Util/Logger.hpp"

namespace Power
{
    std::shared_ptr<Power::Powers> Power_creator::GetPowerByID(RUtil::Powers_Text_ID power_id){
        switch(power_id){
            case RUtil::Powers_Text_ID::Barricade: return std::make_shared<Barricade_power>();
            case RUtil::Powers_Text_ID::Frail: return std::make_shared<Frail_power>();
            case RUtil::Powers_Text_ID::Ritual: return std::make_shared<Ritual_power>();
            case RUtil::Powers_Text_ID::Strength: return std::make_shared<Strength_power>();
            case RUtil::Powers_Text_ID::Vulnerable: return std::make_shared<Vulnerable_power>();
            case RUtil::Powers_Text_ID::Weakened: return std::make_shared<Weak_power>();
            default:
                LOG_ERROR("The power id:{} has not been implemented yet.", static_cast<int>(power_id));
                return std::make_shared<Weak_power>();
        }
    }
} // namespace Power
