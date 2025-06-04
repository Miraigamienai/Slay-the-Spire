#include <glm/gtc/constants.hpp>

#include "InitScreenBackground.hpp"
#include "RUtil/Random.hpp"
#include "RUtil/ColorValuesOnly.hpp"
#include "RUtil/Game_Input.hpp"
#include "RUtil/Image_book.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/ReTexture.hpp"
#include "WindowSize.hpp"

using namespace RUtil;

InitScreenBackground::InitScreenBackground():
    top_cloud(CloudCreater(true, top_cloud_id)),
    mid_cloud(CloudCreater(false, mid_cloud_id)),
    glow_timer(Random::GetRandomFloat(0.0F, glm::two_pi<float>())),
    logo_a(1.0F){}

void InitScreenBackground::render(const std::shared_ptr<Draw::Draw_2D> &r2) const{
    r2->SetColor(RUtil::WHITE);
    render_format(r2, AtlasRegionID::_jpg_sky, 0.0F, 0.0F);
    render_format(r2, AtlasRegionID::_mg3Bot, 0.0F, static_cast<float>(Setting::WINDOW_HEIGHT)-2219.0F*Setting::SCALE);
    render_format(r2, AtlasRegionID::_mg3Top, 0.0F, static_cast<float>(Setting::WINDOW_HEIGHT)-1080.0F*Setting::SCALE);
    r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE);
    r2->SetColor(1.0F, 0.2F, 0.1F, 0.1F+(std::cos(glow_timer)+1.25F)/5.0F);
    render_format(r2, AtlasRegionID::_mg3BotGlow, 0.0F, static_cast<float>(Setting::WINDOW_HEIGHT)-2220.0F*Setting::SCALE);
    render_format(r2, AtlasRegionID::_mg3TopGlow1, 0.0F, static_cast<float>(Setting::WINDOW_HEIGHT)-1080.0F*Setting::SCALE);
    render_format(r2, AtlasRegionID::_mg3TopGlow2, 0.0F, static_cast<float>(Setting::WINDOW_HEIGHT)-1080.0F*Setting::SCALE);
    r2->SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    r2->SetColor(RUtil::WHITE);
    //TODO: dust
    for(auto&it:mid_cloud) it.render(r2);
    for(auto&it:top_cloud) it.render(r2);
    r2->SetColor(RUtil::WHITE, logo_a);
    static auto &LOGO_IMG=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/startScreen/logo.png");
    r2->draw(LOGO_IMG, 930.0F*Setting::SCALE - static_cast<float>(LOGO_IMG->GetWidth())/2.0F, static_cast<float>(Setting::WINDOW_HEIGHT)/2.0F + 14.0F*Setting::SCALE - static_cast<float>(LOGO_IMG->GetHeight())/2.0F, static_cast<float>(LOGO_IMG->GetWidth()), static_cast<float>(LOGO_IMG->GetHeight()), 0.0F, static_cast<float>(LOGO_IMG->GetWidth())/2.0F, static_cast<float>(LOGO_IMG->GetHeight())/2.0F, Setting::SCALE, Setting::SCALE);

    //TODO flame
}

inline void InitScreenBackground::render_format(const std::shared_ptr<Draw::Draw_2D> &r2, RUtil::AtlasRegionID id, float x, float y){
    auto &img=All_Image::GetAtlasRegion(id);
    r2->draw(img, x + img->offsetX*Setting::SCALE, y + img->offsetY*Setting::SCALE, static_cast<float>(img->GetRegionWidth()), static_cast<float>(img->GetRegionHeight()), 0.0F, 0.0F, 0.0F, Setting::SCALE, Setting::SCALE);
}

void InitScreenBackground::update(bool darken){
    for(auto&it:top_cloud) it.update();
    for(auto&it:mid_cloud) it.update();
    glow_timer += glm::two_pi<float>() * Game_Input::delta_time();
    logo_a = RUtil::Math::varlerp(logo_a, (darken ? 0.25F : 1.0F), 3.0F, 0.01F);
}

static SETTING_CONSTEXPR float CLOUD_Y = static_cast<float>(Setting::WINDOW_HEIGHT) - 1100.0F*Setting::SCALE;

static inline float GetNewCloudY(){
    return CLOUD_Y+Random::GetRandomFloat(-50.0F, 50.0F)*Setting::SCALE;
}

static inline float GetNewCloudSpeedX(bool move_right){
    return Random::GetRandomFloat(10.0F, 50.0F)*Setting::SCALE * (move_right ? 1.0F : -1.0F);
}

static inline float GetNewCloudSpeedY(bool move_right, float speed_x){
    return (move_right ? Random::GetRandomFloat(-speed_x, speed_x) : Random::GetRandomFloat(speed_x, -speed_x)) / 10.0F;
}

InitScreenBackground::Cloud::Cloud(AtlasRegionID region_id, bool move_right)
    :region_id(region_id),
    move_right(move_right),
    x(RUtil::Random::GetRandomFloat(-static_cast<float>(Setting::WINDOW_WIDTH), static_cast<float>(Setting::WINDOW_WIDTH))),
    y(GetNewCloudY()),
    speed_x(GetNewCloudSpeedX(move_right)),
    speed_y(GetNewCloudSpeedY(move_right, speed_x)){}
        
void InitScreenBackground::Cloud::update(){
    x+=speed_x*Game_Input::delta_time();
    y+=speed_y*Game_Input::delta_time();
    if(x>static_cast<float>(Setting::WINDOW_WIDTH) || x<-static_cast<float>(Setting::WINDOW_WIDTH)){
        x=static_cast<float>(Setting::WINDOW_WIDTH) * (move_right ? -1.0F : 1.0F);
        y=GetNewCloudY();
        speed_x=GetNewCloudSpeedX(move_right);
        speed_y=GetNewCloudSpeedY(move_right, speed_x);
    }
}