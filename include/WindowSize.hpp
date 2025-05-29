#ifndef WINDOW_SIZE_H
#define WINDOW_SIZE_H

#define SETTING_IS_CONSTEXPR 1

#if SETTING_IS_CONSTEXPR
    #define SETTING_CONSTEXPR constexpr
#else
    #define SETTING_CONSTEXPR const
#endif

// #include "config.hpp"

enum class Language{
    eng,
    zht,
    jpn
};

namespace Setting{
    // constexpr float SCALE =(float)WINDOW_WIDTH / 1920.0F;
    SETTING_CONSTEXPR int WINDOW_WIDTH=1280;
    SETTING_CONSTEXPR int WINDOW_HEIGHT=720;
    
    SETTING_CONSTEXPR float SCALE =(float)1280 / 1920.0F;
    
    //temp
    SETTING_CONSTEXPR Language language=Language::zht;
    constexpr int BIGGIST_SIZE=32;//temp max 32 if there is a bigger font ,adjust this.
}
#endif