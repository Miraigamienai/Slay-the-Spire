#include "Game_object/character/Monster/GreenLouse.hpp"
#include "RUtil/Random.hpp"
namespace Monster{
    GreenLouse::GreenLouse(float offsetX, float offsetY):Monsters(Setting::WINDOW_WIDTH*0.75F+offsetX, FLOOR_Y+offsetY, WIDTH, HIGHT,HPBarWidth)
    {
        setHP(MIN_HP,MAX_HP);
        setBlock(0);
        m_damage=int(RUtil::Random::GetRandomFloat(MIN_DAMAGE,MAX_DAMAGE));

    }
    
    void GreenLouse::render(const std::shared_ptr<Draw::Draw_2D> &r2) const 
    {
        r2->SetColor(-1);
        r2->draw(img,getPosition().x,getPosition().y,WIDTH,HIGHT);
        render_HP(r2);
    }
    const std::shared_ptr<Draw::ReTexture> &GreenLouse::img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/monster/Louses/Louse-green-pretty.png");

}

