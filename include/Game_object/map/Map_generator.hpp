#pragma once

#include <memory>
#include <vector>

#include "Game_object/map/Map_node.hpp"
#include "Game_object/room/Monster_room.hpp"
#include "Game_object/room/Rest_room.hpp"
#include "Game_object/room/Shop_room.hpp"
#include "Game_object/room/Treasure_room.hpp"
#include "Game_object/room/Elite_room.hpp"

//fwd decl
namespace RUtil{
    class Random;
}

namespace Map{
class Map_generator
{
public:
    using MapType = std::vector<std::vector<std::shared_ptr<Map_node>>>;
    Map_generator()=delete;~Map_generator()=delete;Map_generator(const Map_generator &) = delete;Map_generator(Map_generator &&) = delete;Map_generator &operator=(const Map_generator &) = delete;Map_generator &operator=(Map_generator &&) = delete;
    static MapType Get_Map(size_t height,size_t width,int density, RUtil::Random &rng);

    template <typename TypePicker, typename WeakPicker, typename StrongPicker, typename ElitePicker>
    static void AssignRoom(const MapType &map, const TypePicker &tp, const WeakPicker &wp, const StrongPicker &sp, const ElitePicker &ep, RUtil::Random &rng){
        std::vector<std::pair<size_t, size_t>> monster_pos;
        int elite_cnt=0, shop_cnt=0;

        for(size_t i=0;i<map.size();i++){
            for(size_t j=0;j<map[i].size();j++){
                if(map[i][j]==nullptr) continue;
                if(i==0){
                    map[i][j]->SetRoom(std::make_shared<Room::Monster_room>(wp(rng)));
                }else if(i==8){
                    map[i][j]->SetRoom(std::make_shared<Room::Treasure_room>());
                }else if(i==14){
                    map[i][j]->SetRoom(std::make_shared<Room::Rest_room>());
                }else{
                    bool kotowaru;
                    do{
                        kotowaru=false;
                        switch(tp(rng)){
                            case Room::Room_type::Elite:
                                if(i<=4) kotowaru=true;
                                else{
                                    ++elite_cnt;
                                    map[i][j]->SetRoom(std::make_shared<Room::Elite_room>(ep(rng)));
                                }
                                break;
                            case Room::Room_type::Event:
                                kotowaru=true;
                                break;
                            case Room::Room_type::Monster:
                                map[i][j]->SetRoom(std::make_shared<Room::Monster_room>(i<3 ? wp(rng) : sp(rng)));
                                monster_pos.emplace_back(std::pair{i,j});
                                break;
                            case Room::Room_type::Rest:
                                if(i<=4 || i==13) kotowaru=true;
                                else map[i][j]->SetRoom(std::make_shared<Room::Rest_room>());
                                break;
                            case Room::Room_type::Shop:
                                ++shop_cnt;
                                map[i][j]->SetRoom(std::make_shared<Room::Shop_room>());
                                break;
                            case Room::Room_type::Treasure:
                                map[i][j]->SetRoom(std::make_shared<Room::Treasure_room>());
                                break;
                            default:
                                break;
                        }
                    }while(kotowaru);
                }
            }
        }

        while(elite_cnt<3){
            ++elite_cnt;
            if(!monster_pos.empty()){
                std::shuffle(monster_pos.begin(), monster_pos.end(), rng);
                map[monster_pos.back().first][monster_pos.back().second]->SetRoom(std::make_shared<Room::Elite_room>(ep(rng)));
                monster_pos.pop_back();
            }
        }

        while(shop_cnt<3){
            ++shop_cnt;
            if(!monster_pos.empty()){
                std::shuffle(monster_pos.begin(), monster_pos.end(), rng);
                map[monster_pos.back().first][monster_pos.back().second]->SetRoom(std::make_shared<Room::Shop_room>());
                monster_pos.pop_back();
            }
        }
    }
};
}