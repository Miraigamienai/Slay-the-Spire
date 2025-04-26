#pragma once

#include <memory>
#include <SDL_ttf.h>
#include "WindowSize.hpp"

enum class FontWeight:int{
    regular,
    bold,
    medium
};

namespace Draw{
class Fonts
{
public:
    Fonts() = delete;
    ~Fonts() = delete;
    Fonts(const Fonts &) = delete;
    Fonts(Fonts &&) = delete;
    Fonts &operator=(const Fonts &) = delete;
    Fonts &operator=(Fonts &&)=delete;

    static const std::shared_ptr<TTF_Font> &GetRegularFont();
    static const std::shared_ptr<TTF_Font> &GetBoldFont();
    static const std::shared_ptr<TTF_Font> &GetMediumFont();
    static float CalFontScale(int fontsize,FontWeight fw);
    static const auto &GetFont(FontWeight fw){
        switch(fw){
            case FontWeight::bold:return GetBoldFont();
            case FontWeight::medium:return GetMediumFont();
            default:return GetRegularFont();
        }
    }
private:
    static constexpr auto GetPos(Language lang,FontWeight fw){
        switch (lang){
            case Language::eng:
                switch (fw){
                    case FontWeight::bold:return RESOURCE_DIR "/font/Kreon-Bold.ttf";
                    case FontWeight::medium:return RESOURCE_DIR "/font/ZillaSlab-RegularItalic.otf";
                    default:return RESOURCE_DIR "/font/Kreon-Regular.ttf";
                }
            case Language::jpn:
                switch(fw){
                    case FontWeight::bold:return RESOURCE_DIR "/font/jpn/NotoSansCJKjp-" "Bold.otf";
                    case FontWeight::medium:return RESOURCE_DIR "/font/jpn/NotoSansCJKjp-" "Medium.otf";
                    default:return RESOURCE_DIR "/font/jpn/NotoSansCJKjp-" "Regular.otf";
                }
            default:
                switch(fw){
                    case FontWeight::bold:return RESOURCE_DIR "/font/zht/NotoSansCJKtc-" "Bold.otf";
                    case FontWeight::medium:return RESOURCE_DIR "/font/zht/NotoSansCJKtc-" "Medium.otf";
                    default:return RESOURCE_DIR "/font/zht/NotoSansCJKtc-" "Regular.otf";
                }
        }        
    }
};
}