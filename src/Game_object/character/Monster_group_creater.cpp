#include <array>
#include <type_traits>

#include "Game_object/character/Monster_group_creater.hpp"
#include "Game_object/character/AllMonster.hpp"
#include "Game_object/dungeon/Dungeon_shared.hpp"

#include "Util/Logger.hpp"

namespace Monster{
    class Wrapper{
        public:
            Wrapper(Dungeon::Dungeon_shared& dungeon_shared):_dungeon_shared(dungeon_shared){}
            template <typename T, typename...Args>
            void AT(Args&&...args){
                _dungeon_shared.room_monsters.AddTop(std::make_shared<T>(std::forward<Args>(args)...));
            }
            template <typename T>
            void AT(float offset_x, float offset_y){
                _dungeon_shared.room_monsters.AddTop(std::make_shared<T>(offset_x, offset_y, _dungeon_shared.random_package.monster_status_rng));
            }
            template <typename T1, typename T2>
            void AT(float offset_x, float offset_y){
                if(_dungeon_shared.random_package.monster_rng.Nextboolean())
                    _dungeon_shared.room_monsters.AddTop(std::make_shared<T1>(offset_x, offset_y, _dungeon_shared.random_package.monster_status_rng));
                else
                    _dungeon_shared.room_monsters.AddTop(std::make_shared<T2>(offset_x, offset_y, _dungeon_shared.random_package.monster_status_rng));
            }
            template <typename...Ts>
            void AT(float offset_x, float offset_y, int x){
                constexpr auto N = sizeof...(Ts);
                static constexpr auto funs_table = std::array{&bind_fun<Ts>...};
                if(x<0||x>=static_cast<int>(N)) LOG_ERROR("x is bigger than N or smaller than 0 when AddTop.[x:{}, N:{}]", x, N);
                else _dungeon_shared.room_monsters.AddTop(funs_table[x](offset_x, offset_y, _dungeon_shared.random_package.monster_status_rng));
            }
            void add_bottom_weak_wild_life(float offset_x, float offset_y){
                switch(_dungeon_shared.random_package.monster_rng.NextInt(3)){
                    case 0:
                        AT<RedLouse, GreenLouse>(offset_x, offset_y);
                        break;
                    case 1:
                        AT<SpikeSlimeM>(offset_x, offset_y);
                        break;
                    default:
                        AT<AcidSlimeM>(offset_x, offset_y);
                        break;
                }
            }
            void add_bottom_strong_humanoid(float offset_x, float offset_y){
                switch(_dungeon_shared.random_package.monster_rng.NextInt(3)){
                    case 0:
                        AT<Cultist>(offset_x, offset_y);
                        break;
                    case 1:
                        AT<BlueSlaver, RedSlaver>(offset_x, offset_y);
                        break;
                    default:
                        AT<Looter>(offset_x, offset_y);
                        break;
                }
            }
        private:
            Dungeon::Dungeon_shared& _dungeon_shared;
            template <typename T>
            static std::shared_ptr<Monsters> bind_fun(float offset_x, float offset_y, RUtil::Random& rng){
                return std::make_shared<T>(offset_x, offset_y, rng);
            }
    };

    static inline float random_offset(float val){
        return val + RUtil::Random::GetRandomFloat(-20.0F, 20.0F);
    }

    void Monster_group_creater::CreateGroup(Dungeon::Dungeon_shared& dungeon_shared, GroupName group_name){
        Wrapper w{dungeon_shared};
        auto &monster_rng=dungeon_shared.random_package.monster_rng;

        switch(group_name){
            case GroupName::Cultist:
                w.AT<Cultist>(0.0F, -10.0F);
                break;
            case GroupName::Jaw_Worm:
                w.AT<JawWorm>(0.0F, 25.0F);
                break;
            case GroupName::_2_Louse:
                w.AT<RedLouse, GreenLouse>(-200.0F, 10.0F);
                w.AT<RedLouse, GreenLouse>(80.0F, 30.0F);
                break;
            case GroupName::Small_Slimes:
                if(monster_rng.Nextboolean()){
                    w.AT<AcidSlimeS>(-230.0F, 32.0F);
                    w.AT<SpikeSlimeM>(35.0F, 8.0F);
                }else{
                    w.AT<SpikeSlimeS>(-230.0F, 32.0F);
                    w.AT<AcidSlimeM>(35.0F, 8.0F);
                }
                break;
            case GroupName::Gremlin_Gang:
                {
                    static constexpr float pos[4][2]={{-320.0F, 25.0F}, {-160.0F, -12.0F}, { 25.0F, -12.0F}, {190.0F, 25.0F}};
                    auto arr=std::array{0, 0, 1, 1, 2, 2, 3, 4};
                    std::shuffle(arr.begin(), arr.end(), monster_rng);
                    for(int i=0;i<4;i++)
                        w.AT<MadGremlin, SneakyGremlin, FatGremlin, ShieldGremlin, WizardGremlin>(pos[i][0], pos[i][1], arr[i]);
                }
                break;
            case GroupName::Large_Slime:
                w.AT<SpikeSlimeL, AcidSlimeL>(0.0F, 0.0F);
                break;
            case GroupName::Lots_of_Slimes:
                {
                    static constexpr float pos[5][2]={{-480.0F, 30.0F}, {-320.0F, 2.0F}, {-160.0F, 32.0F}, {10.0F, -12.0F}, {200.0F, 9.0F}};
                    auto arr=std::array{0, 0, 1, 1, 1};
                    std::shuffle(arr.begin(), arr.end(), monster_rng);
                    for(int i=0;i<5;i++)
                        w.AT<AcidSlimeS, SpikeSlimeS>(pos[i][0], pos[i][1], arr[i]);
                }
                break;
            case GroupName::Red_Slaver:
                w.AT<RedSlaver>(0.0F, 0.0F);
                break;
            case GroupName::Blue_Slaver:
                w.AT<BlueSlaver>(0.0F, 0.0F);
                break;
            case GroupName::_3_Louse:
                {
                    constexpr float pos[3][2]={{-350.0F, 25.0F}, {-125.0F, 10.0F}, {80.0F, 30.0F}};
                    for(int i=0;i<3;i++)
                        w.AT<RedLouse, GreenLouse>(pos[i][0], pos[i][1]);
                }
                break;
            case GroupName::_2_Fungi_Beasts:
                {
                    constexpr float pos[2][2]={{-400.0F, 30.0F}, {-40.0F, 20.0F}};
                    for(int i=0;i<2;i++)
                        w.AT<FungiBeast>(pos[i][0], pos[i][1]);
                }
                break;
            case GroupName::Exordium_Thugs:
                w.add_bottom_weak_wild_life(random_offset(-160.0F), random_offset(20.0F));
                w.add_bottom_strong_humanoid(random_offset(130.0F), random_offset(20.0F));
                break;
            case GroupName::Exordium_Wildlife:
                w.AT<FungiBeast, JawWorm>(random_offset(-150.0F), random_offset(20.0F));
                w.add_bottom_weak_wild_life(random_offset(150.0F), random_offset(20.0F));
                break;
            case GroupName::Looter:
                w.AT<Looter>(0.0F, 0.0F);
                break;
            case GroupName::Gremlin_Nob:
                w.AT<GremlinNob>(0.0F, 0.0F);
                break;
            case GroupName::Lagavulin:
                // w.AT<Lagavulin>(0.0F, 0.0F);
                break;
            case GroupName::_3_Sentries:
                {
                    static constexpr float pos[3][2]={{-300.0F, 30.0F}, {-100.0F, 10.0F}, {100.0F, 30.0F}};
                    for(int i=0;i<3;i++)
                        w.AT<Sentry>(pos[i][0], pos[i][1]);
                }
                break;
            case GroupName::Slime_Boss:
                w.AT<SlimeBoss>();
                break;
            case GroupName::Hexaghost:
                w.AT<Hexaghost>();
                break;
            case GroupName::None:
                //for test
                w.AT<FatGremlin>(0.0F, 0.0F);
                break;
            default:
                LOG_ERROR("The Group:{} is has not be set yet",static_cast<int>(group_name));
                break;
        }
    }
}