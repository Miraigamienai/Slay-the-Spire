#include "draw_test.hpp"
#include "RUtil/All_Image.hpp"
#include "Draw/Draw_2D.hpp"
#include "Draw/Atlas_Region.hpp"
#include "Util/Input.hpp"
#include "Draw/Text_layout_color.hpp"
#include "Game_object/top_panel/Top_panel.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"
TopPanel::Top_panel top_panel;
void test(const std::shared_ptr<Draw::Draw_2D> &r2){
    top_panel.render(r2);

}
void test2(Dungeon::Dungeon_shared &dungeon_shared){

    top_panel.update(dungeon_shared);
}
