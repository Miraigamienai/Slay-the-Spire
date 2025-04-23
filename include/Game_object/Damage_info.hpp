#include <memory>

namespace Character{
    class Characters;
}

struct Damage_info
{
    int dmg;
    std::shared_ptr<Character::Characters> src;
};
