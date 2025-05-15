#include "Game_object/effect/Purge_card_eff.hpp"
#include "Game_object/card/Cards.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "RUtil/All_Image.hpp"
#include "RUtil/Some_Math.hpp"
#include "RUtil/Random.hpp"

namespace Effect
{
    void Purge_card_eff::render(const std::shared_ptr<Draw::Draw_2D> &r2)const{
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        r2->SetColor(color, color_a);
        auto &img=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_512_bg_power_silhouette);
        r2->draw(img, card->GetX() + img->offsetX - (float)img->original_width / 2.0F, card->GetY() + img->offsetY - (float)img->original_height / 2.0F,(float)img->GetRegionWidth(), (float)img->GetRegionHeight(), 0.0F, (float)img->original_width / 2.0F - img->offsetX, (float)img->original_height / 2.0F - img->offsetY, this->scale * RUtil::Random::GetRandomFloat(0.95F, 1.05F), this->scale2 * RUtil::Random::GetRandomFloat(0.95F, 1.05F));
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
        r2->SetColor(color2, color_a);
        auto &img2=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_512_card_super_shadow);
        r2->draw(img2, card->GetX() + img2->offsetX - (float)img2->original_width / 2.0F, card->GetY() + img2->offsetY - (float)img2->original_height / 2.0F,(float)img2->GetRegionWidth(), (float)img2->GetRegionHeight(), 0.0F, (float)img2->original_width / 2.0F - img2->offsetX, (float)img2->original_height / 2.0F - img2->offsetY, this->scale * RUtil::Random::GetRandomFloat(0.95F, 1.05F)*0.75F, this->scale2 * RUtil::Random::GetRandomFloat(0.95F, 1.05F)*0.75F);
        r2->draw(img2, card->GetX() + img2->offsetX - (float)img2->original_width / 2.0F, card->GetY() + img2->offsetY - (float)img2->original_height / 2.0F,(float)img2->GetRegionWidth(), (float)img2->GetRegionHeight(), 0.0F, (float)img2->original_width / 2.0F - img2->offsetX, (float)img2->original_height / 2.0F - img2->offsetY, this->scale * RUtil::Random::GetRandomFloat(0.95F, 1.05F)*0.5F, this->scale2 * RUtil::Random::GetRandomFloat(0.95F, 1.05F)*0.5F);
        r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        card->render(r2);
    }

    void Purge_card_eff::update(){
        if(duration<0.5F){
            this->color_a=RUtil::Math::fadelerp(this->color_a, 0.5F);
            this->scale=RUtil::Math::interpolation_swing_out(1.6F, 1.0F, this->duration*2.0F)*Setting::SCALE;
            this->scale2=RUtil::Math::interpolation_fade(0.005F, 1.0F, this->duration*2.0F)*Setting::SCALE;
        }
        TimeGo();
    }
} // namespace Effect
