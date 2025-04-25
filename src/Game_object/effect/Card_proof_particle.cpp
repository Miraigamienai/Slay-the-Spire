#include "Game_object/effect/Card_proof_particle.hpp"
#include "RUtil/All_Image.hpp"//for loading img
#include "Draw/Atlas_Region.hpp"//smoke img
#include "RUtil/Random.hpp"//ramdom something
#include "WindowSize.hpp"//Setting::Scale
namespace Effect{
    void Card_proof_particle::Initial(const float x,const float y){
        is_done=false;
        scale=Setting::SCALE;
        
    }
    const std::shared_ptr<Draw::Atlas_Region> &Card_proof_particle::SMOKE1=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke1),
                                              &Card_proof_particle::SMOKE2=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke2),
                                              &Card_proof_particle::SMOKE3=RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::_env_smoke3);
}
