#include "TheApp.hpp"
#include "Core/Context.hpp"
#include "Draw/Draw_2D.hpp"
#include "Cursor.hpp"
#include "Util/Input.hpp"
#include "draw_test.hpp"
#include "Game_object/effect/Auto_release_pool_manager.hpp"

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    context->SetWindowIcon(RESOURCE_DIR"/Image/assets/icon.png");
    SDL_ShowCursor(SDL_DISABLE);
    std::shared_ptr<Draw::Draw_2D> Draw2D =std::make_shared<Draw::Draw_2D>(4095);
    TheApp app;
    while (!context->GetExit()) {
        Effect::Auto_release_pool_manager::update();
        RUtil::Game_Input::update();
        app.update();
        Draw2D->begin();
        app.render(Draw2D);
        
        Cursor::Draw(Draw2D);
        Draw2D->end();
        context->Update();
        if (Util::Input::IsKeyPressed(Util::Keycode::ESCAPE) || Util::Input::IfExit()) {
            context->SetExit(true);
        }
    }
    return 0;
}
