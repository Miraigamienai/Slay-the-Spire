#pragma once

#include <memory>
#include <string>

#include "Draw/Fonts.hpp"//calculate scale inline
#include "WindowSize.hpp"//for getting default font size

//fwd decl
namespace Draw{
    class Image_Region;
    class Draw_2D;
}

namespace Draw{
//A class for drawing number.
//Color needs to be set manually.
class NumberDrawer
{
public:
    NumberDrawer(int fontsize){SetFontSize(fontsize);}
    ~NumberDrawer()=default;
    void SetFontSize(int fontsize){
        if(this->fontsize==fontsize) return;
        this->fontsize=fontsize;
        font_scale=Fonts::CalFontScale(fontsize,this->fw);
    }
    void ChangeFontWeight(FontWeight fw){
        if(fw==this->fw) return;
        this->fw=fw;
        if(fontsize!=Setting::BIGGIST_SIZE) font_scale=Fonts::CalFontScale(fontsize,fw);
    }
    int PureWidth(const std::string &num_str)const;
    
    void render_center(const std::shared_ptr<Draw_2D> &r2,const std::string &num_str,const float center_x,const float center_y,const float scale)const;
private:
    int fontsize=Setting::BIGGIST_SIZE;
    float font_scale=1.0F;
    FontWeight fw=FontWeight::regular;

    const std::shared_ptr<Image_Region>&GetNumIMG(char c)const;
};
}