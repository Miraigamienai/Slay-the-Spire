#include "Game_object/power/Powers.hpp"
#include "RUtil/Powers_Text_Reader.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
namespace Power
{
    void Powers::render_img(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const{
        auto &img=RUtil::All_Image::GetAtlasRegion(region_48_id);
        r2->SetColor(RUtil::WHITE, color_a);
        r2->draw(img, x - (float)img->GetRegionWidth()/2.0F, y - (float)img->GetRegionHeight()/2.0F, (float)img->GetRegionWidth(), (float)img->GetRegionHeight(), 0.0F, (float)img->GetRegionWidth()/2.0F, (float)img->GetRegionHeight()/2.0F, Setting::SCALE, Setting::SCALE);   
    }

    void Powers::render_amount(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const{
                
    }
    
    void Powers::render_tip(const std::shared_ptr<Draw::Draw_2D> &r2, float x, float y, float color_a)const{

    }
    
    Draw::NumberDrawer Powers::amount_drawer(FONTSIZE);
} // namespace Power
