#include "Game_object/power/Weak_power.hpp"
#include "Draw/Text_layout.hpp"

namespace Power{
    void Weak_power::desc_update(){
        tip_box.change_body(get_desc());
        tip_box.get_body()->set_num_info(Draw::number_info{25, 0, this->amount, Draw::NumStatus::blue});
    }
}