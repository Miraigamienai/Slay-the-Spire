#pragma once

#include <memory>
#include <vector>

//fwd decl
namespace Dungeon{
    class Dungeon_shared;
}

namespace Room{
namespace Option{
//fwd decl
class Options;

class Option_handler
{
public:
    Option_handler(const Dungeon::Dungeon_shared& dungeon_shared);
    ~Option_handler()=default;
private:
    std::vector<std::shared_ptr<Options>> opts;
};
}
}
