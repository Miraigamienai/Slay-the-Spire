#include "Draw/Fonts.hpp"

namespace Draw
{
    const std::shared_ptr<TTF_Font> &Fonts::GetRegularFont(){
        constexpr auto pos=GetPos(Setting::language,FontWeight::regular);
        static std::shared_ptr<TTF_Font> font(TTF_OpenFont(pos, Setting::BIGGIST_SIZE),TTF_CloseFont);
        return font;
    }
    const std::shared_ptr<TTF_Font> &Fonts::GetBoldFont(){
        constexpr auto pos=GetPos(Setting::language,FontWeight::bold);
        static std::shared_ptr<TTF_Font> font(TTF_OpenFont(pos, Setting::BIGGIST_SIZE),TTF_CloseFont);
        return font;
    }
    const std::shared_ptr<TTF_Font> &Fonts::GetMediumFont(){
        constexpr auto pos=GetPos(Setting::language,FontWeight::medium);
        static std::shared_ptr<TTF_Font> font(TTF_OpenFont(pos, Setting::BIGGIST_SIZE),TTF_CloseFont);
        return font;
    }
    float Fonts::CalFontScale(int fontsize,FontWeight fw){
        //use "0"'s height for estimate.
        constexpr auto WORD="0";
        static int regular_height;
        static int bold_height;
        static int medium_height;
        static bool once=false;
        int temp;
        if(!once){
            once=true;
            TTF_SizeUTF8(GetRegularFont().get(), WORD, &temp, &regular_height);
            TTF_SizeUTF8(GetBoldFont().get(), WORD, &temp, &bold_height);
            TTF_SizeUTF8(GetMediumFont().get(), WORD, &temp, &medium_height);
        }
        int height;
        TTF_Font *font=TTF_OpenFont(GetPos(Setting::language,fw), fontsize);
        TTF_SizeUTF8(font, WORD, &temp, &height);
        TTF_CloseFont(font);
        switch(fw){
            case FontWeight::bold:return static_cast<float>(height) / static_cast<float>(bold_height);
            case FontWeight::medium:return static_cast<float>(height) / static_cast<float>(medium_height);
            default:return static_cast<float>(height) / static_cast<float>(regular_height);
        }
    }
} // namespace Draw
