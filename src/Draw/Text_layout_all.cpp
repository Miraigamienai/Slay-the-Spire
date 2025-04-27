#include "Draw/Text_layout_all.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Draw/Draw_2D.hpp"
#include "RUtil/All_Image.hpp"

#include "Util/Logger.hpp"

namespace Draw
{
    
    
    static auto&GetOrb(char c){
        switch (c){
            case 'R':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_red);
            case 'G':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_green);
            case 'B':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_blue);
            case 'W':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_purple);
            case 'C':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_card);
            case 'P':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_potion);
            case 'T':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_relic);
            case 'S':return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_special);
            default:
                LOG_ERROR("The orb ID:\"{}\" dosen't exist.",c);
                return RUtil::All_Image::GetAtlasRegion(RUtil::AtlasRegionID::orb_red);
        }
    }
} // namespace Draw
