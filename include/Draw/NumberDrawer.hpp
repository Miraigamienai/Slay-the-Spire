#pragma once

#include <memory>
#include <string>

#include "Draw/Fonts.hpp"//calculate scale inline
#include "WindowSize.hpp"//for getting default font size
#include "Image_Region.hpp"//for inline

//fwd decl
namespace Draw{
    class Draw_2D;
}

namespace Draw{
//A class for drawing number.
//Color needs to be set manually.
class NumberDrawer
{
public:
    NumberDrawer(int fontsize=Setting::BIGGIST_SIZE){SetFontSize(fontsize);}
    NumberDrawer(int fontsize, FontWeight fw){SetFontSize(fontsize);ChangeFontWeight(fw);}
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
    int PureWidth(int num)const{return PureWidth(std::to_string(num));}
    int PureWidth(const std::string &num_str)const{
        int total=0;
        for(const auto&it:num_str) total+=GetNumIMG(it)->GetRegionWidth();
        return total;
    }
    static int PureWidth(int num, FontWeight fw){return PureWidth(std::to_string(num), fw);}
    static int PureWidth(const std::string &num_str, FontWeight fw){
        int total=0;
        for(const auto&it:num_str) total+=GetNumIMG(it, fw)->GetRegionWidth();
        return total;
    }
    int PureHeight()const{return GetNumIMG('0')->GetRegionHeight();}
    float Width(const std::string &num_str)const{return static_cast<float>(PureWidth(num_str))*font_scale;}
    void render_center(const std::shared_ptr<Draw_2D> &r2,const std::string &num_str,const float center_x,const float center_y,const float scale)const;
    void render_bot_right(const std::shared_ptr<Draw_2D> &r2,const std::string &num_str,const float right_x,const float y,const float scale)const;
    const std::shared_ptr<Image_Region>&GetNumIMG(char c)const;
    static const std::shared_ptr<Image_Region>&GetNumIMG(char c, FontWeight fw);
private:
    int fontsize=Setting::BIGGIST_SIZE;
    float font_scale=1.0F;
    FontWeight fw=FontWeight::regular;
};
}