#pragma once

#include <string>

#include "WindowSize.hpp"

namespace RUtil
{
class File_Pos_Getter
{
public:
    static std::string GetLanguageJsonPos(){
        switch (Setting::language){
            case Language::eng:return RESOURCE_DIR"/language/" "eng/";
            case Language::jpn:return RESOURCE_DIR"/language/" "jpn/";
            default:return RESOURCE_DIR"/language/" "zht/";
        }
    }
};
} // namespace RUtil
