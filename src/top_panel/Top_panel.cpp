#include "Game_object/top_panel/Top_panel.hpp"
#include "RUtil/Image_book.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

namespace TopPanel
{
    Top_panel::Top_panel()
    {
        // Constructor implementation
    }
    void Top_panel::update(Dungeon::Dungeon_shared &dungeon_shared)
    {
        deck.update(dungeon_shared);
        floor.update(dungeon_shared);
        map.update();
        goldBag.update(dungeon_shared);
        heart.update(dungeon_shared);
        setting.update();
    }
    void Top_panel::render(const std::shared_ptr<Draw::Draw_2D> &r2)const
    {
        r2->SetColor(-1);
        r2->draw(bar_img, bar_x, bar_y,bar_w, bar_h);
        deck.render(r2);
        floor.render(r2);
        map.render(r2);
        goldBag.render(r2);
        heart.render(r2);
        setting.render(r2);
    }

    const std::shared_ptr<Draw::ReTexture> &Top_panel::bar_img=RUtil::Image_book::GetTexture(RESOURCE_DIR"/Image/topPanel/bar.png");
}