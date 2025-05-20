#include "Game_object/effect/Power_remove_text_eff.hpp"
#include "RUtil/Powers_Text_Reader.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Text_Vector_Reader.hpp"
#include "Draw/Text_layout.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"

namespace Effect{
    void Power_remove_text_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        auto &name=RUtil::Powers_Text_Reader::GetName(power_text_id);
        name->SetFontSize(36);
        name->SetFontAlpha(color_a);
        name->render_top_left(r2, this->x, this->y + this->offset_y, Setting::SCALE);
        TEXT->SetFontSize(36);
        TEXT->SetFontAlpha(color_a);
        TEXT->render_top_left(r2, this->x, this->y + this->offset_y-40.0F*Setting::SCALE, Setting::SCALE);
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(RUtil::WHITE, color_a);
        auto&img=RUtil::All_Image::GetAtlasRegion(power_128_id);
        r2->draw(img, this->x - static_cast<float>(img->GetRegionWidth())/2.0F - 64.0F*Setting::SCALE, this->y + this->offset_y, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), 0.0F, static_cast<float>(img->GetRegionWidth())/2.0F, static_cast<float>(img->GetRegionHeight())/2.0F, this->scale, this->scale);
    }
    
    void Power_remove_text_eff::update(){
        offset_y=RUtil::Math::interpolation_exp10in(TARGET_OFFSET_Y, START_OFFSET_Y, duration/2.0F);
        color_a=RUtil::Math::interpolation_exp10out(0.0F, 1.0F, duration/2.0F);
        TimeGo();
    }

    const std::shared_ptr<Draw::Text_layout> &Power_remove_text_eff::TEXT=RUtil::Text_Vector_Reader::GetTextVector(RUtil::Text_ID::PowerExpireTextEffect)[0];
}