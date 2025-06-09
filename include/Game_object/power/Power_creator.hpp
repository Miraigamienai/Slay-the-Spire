#pragma once

#include <memory>

//fwd decl
namespace Power{
    class Powers;
}
namespace RUtil{
    enum class Powers_Text_ID:int;
}
namespace Character{
    enum class CharacterType:int;    
}

namespace Power
{
class Power_creator{
public:
    Power_creator()=delete;~Power_creator()=delete;Power_creator(const Power_creator &) = delete;Power_creator(Power_creator &&) = delete;Power_creator &operator=(const Power_creator &) = delete;Power_creator &operator=(Power_creator &&) = delete;
    static std::shared_ptr<Power::Powers> GetPowerByID(RUtil::Powers_Text_ID power_id, Character::CharacterType owner_type);
};
} // namespace Power
