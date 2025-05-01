#include "Game_object/character/Monster/FatGremlin.hpp"
#include "RUtil/Random.hpp"
#include <iostream>
namespace Monster{
    FatGremlin::FatGremlin(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
        m_damage=DAMAGE;

    }
    
    void FatGremlin::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        r2->SetColor(-1);
        r2->draw(img,getPosition().x,getPosition().y,WIDTH,HIGHT); 
        render_HP(r2);
    }
    const std::shared_ptr<Draw::ReTexture> &FatGremlin::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Gremlins/Fat-gremlin-pretty.png");

}

