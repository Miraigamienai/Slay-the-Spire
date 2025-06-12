#pragma once

#include "Game_object/panel/Panels.hpp"
#include "RUtil/Some_Math.hpp"
#include "Draw/NumberDrawer.hpp"

//fwd decl
namespace EnergyOrb{
    class Energy_orb;
}
namespace Effect{
    class Effect_group;
}
namespace  Character{
    class Player;
    enum class PlayerType:int;
}

namespace Panel{
class Energy_panel final:public Panels
{
public:
    Energy_panel();
    ~Energy_panel()override=default;
    void update(Dungeon::Dungeon_shared &dungeon_shared)override;
    void render(const std::shared_ptr<Draw::Draw_2D> &r2)const override;
    void on_add_energy(Effect::Effect_group &effs);
    void on_use_energy()noexcept{font_scale=2.0F;}
private:
    int current_energy, max_energy;
    float vfx_angle,vfx_scale,vfx_color_a,vfx_timer,font_scale;
    Character::PlayerType current_player_type;
    std::shared_ptr<EnergyOrb::Energy_orb> energy_orb;
    std::shared_ptr<Draw::ReTexture> vfx_img;
    
    void update_vfx();
    void render_vfx(const std::shared_ptr<Draw::Draw_2D> &r2)const;
    
    static const Draw::NumberDrawer m_font;
    static constexpr int FONTSIZE=36;
    static constexpr Uint32 TEXTCOLOR=RUtil::Math::GetColorUint32_RGB(1.0F,1.0F,0.86F);
};
}