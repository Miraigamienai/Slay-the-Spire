#include "draw_test.hpp"
Monster::AcidSlimeL acid_slime_l;
Monster::JawWorm jaw_worm;
Monster::FatGremlin fat_gremlin;
Character::Player player;
void test(const std::shared_ptr<Draw::Draw_2D> &r2){
    acid_slime_l.update();
    jaw_worm.update();
    fat_gremlin.update();
    player.update();
    acid_slime_l.render(r2);
    jaw_worm.render(r2);
    fat_gremlin.render(r2);
    player.render(r2);

}

