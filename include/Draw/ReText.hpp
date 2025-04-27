#pragma once

#include <memory>
#include <SDL_ttf.h>//TTF_Font

#include "Draw/ReTexture.hpp"

namespace Draw {
class ReText:public ReTexture{
public:
    /**
     * @brief Load text from filepath.
     * 
     * This class is able to be converted into "Retexture" class.
     * Can't change anything after created.
     * If you want chage color or font size,
     * please use draw function in "Draw_2D"
     */
    ReText(const std::shared_ptr<TTF_Font> &font, const std::string &text);
    ReText(const ReText &) = delete;
    ReText(ReText &&) = delete;

    ~ReText() override=default;

    ReText &operator=(const ReText &) = delete;
    ReText &operator=(ReText &&)=delete;
};
} // namespace Core
