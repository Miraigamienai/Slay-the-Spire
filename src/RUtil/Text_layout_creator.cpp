#include "RUtil/Text_layout_creator.hpp"
#include "Draw/Text_layout_all.hpp"
#include "Draw/Text_layout_color.hpp"
#include "Draw/Text_layout_normal.hpp"

namespace RUtil
{
    static inline bool HasOrbCode(const std::string &text)noexcept{
        for(size_t i=0;i+2<text.size();i++)
            if(text[i] == '[' && text[i + 2] == ']')
                return true;
        return false;
    }
    static inline bool HasNumCode(const std::string &text)noexcept{
        for(size_t i=0;i+2<text.size();i++)
            if(text[i] == '!' && text[i + 2] == '!')
                return true;
        return false;
    }
    std::shared_ptr<Draw::Text_layout> Text_layout_creator::GetLayout(const std::string &text){
        if(text.empty()) return nullptr;
        if(HasOrbCode(text)||HasNumCode(text))
            return std::make_shared<Draw::Text_layout_all>(text);
        if(text.find('#')!=std::string::npos)
            return std::make_shared<Draw::Text_layout_color>(text);
        return std::make_shared<Draw::Text_layout_normal>(text);
    }
} // namespace RUtil
