#pragma once

#include <memory>
#include <string>

//fwd decl
namespace Draw{
    class Text_layout;
}

namespace RUtil{
class Text_layout_creator
{
public:
    Text_layout_creator()=delete;~Text_layout_creator()=delete;Text_layout_creator(const Text_layout_creator &) = delete;Text_layout_creator(Text_layout_creator &&) = delete;Text_layout_creator &operator=(const Text_layout_creator &) = delete;Text_layout_creator &operator=(Text_layout_creator &&) = delete;
    static std::shared_ptr<Draw::Text_layout> GetLayout(const std::string&text);
};
}