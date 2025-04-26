#ifndef WINDOW_SIZE_H
#define WINDOW_SIZE_H

// #include "config.hpp"

enum class Language{
    eng,
    zht,
    jpn
};

namespace Setting{
    // constexpr float SCALE =(float)WINDOW_WIDTH / 1920.0F;
    constexpr int WINDOW_WIDTH=1280;
    constexpr int WINDOW_HEIGHT=720;
    
    constexpr float SCALE =(float)1280 / 1920.0F;
    
    //temp
    constexpr Language language=Language::eng;
    constexpr int BIGGIST_SIZE=32;//temp max 32 if there is a bigger font ,adjust this.
}
#endif