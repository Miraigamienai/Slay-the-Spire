#include "Game_object/character/Monster_group_creater.hpp"
#include "Game_object/character/Monster_group.hpp"
#include "Game_object/character/AllMonster.hpp"
#include "RUtil/Random.hpp"

#include "Util/Logger.hpp"

namespace Monster{
    void Monster_group_creater::CreateGroup(Monster_group &group,GroupName group_name,RUtil::Random &rng){
        switch(group_name){
            case GroupName::Cultist:{
                    group.AddTop(std::make_shared<Cultist>(0.0F, -10.0F));
                }
                return;
            case GroupName::_2_Louse:
                rng.NextInt(0,2)==0?group.AddTop(std::make_shared<RedLouse>(-200.0F, 10.0F)):group.AddTop(std::make_shared<GreenLouse>(-200.0F, 10.0F));
                rng.NextInt(0,2)==0?group.AddTop(std::make_shared<RedLouse>(80.0F, 30.0F)):group.AddTop(std::make_shared<GreenLouse>(80.0F, 30.0F));
                return;
            case GroupName::Small_Slimes:
                if(rng.NextInt(0,2)){
                    group.AddTop(std::make_shared<SpikeSlimeM>(35.0F, 8.0F));
                    group.AddTop(std::make_shared<AcidSlimeS>(-230.0F, 32.0F));
                }
                else{
                    group.AddTop(std::make_shared<AcidSlimeM>(35.0F, 8.0F));
                    group.AddTop(std::make_shared<SpikeSlimeS>(-230.0F, 32.0F));
                }
                return;
            case GroupName::Gremlin_Gang:{
                int vector[5]={0,0,0,0,0};
                float pos[4][2]={{-320.0F, 25.0F},{-160.0F, -12.0F},{ 25.0F, -12.0F},{190.0F, 25.0F}};
                while (vector[0]+vector[1]+vector[2]+vector[3]+vector[4]<4){
                    int num=vector[0]+vector[1]+vector[2]+vector[3]+vector[4];
                    switch (rng.NextInt(0,5))
                    {
                        case 0:
                            if(vector[0]<2){
                                group.AddTop(std::make_shared<MadGremlin>(pos[num][0],pos[num][1]));
                                vector[0]++;
                            }
                            break;
                        case 1:
                            if(vector[1]<2){
                                group.AddTop(std::make_shared<SneakyGremlin>(pos[num][0],pos[num][1]));
                                vector[1]++;
                            }
                            break;
                        case 2:
                            if(vector[2]<2){
                                group.AddTop(std::make_shared<FatGremlin>(pos[num][0],pos[num][1]));
                                vector[2]++;
                            }
                            break;
                        case 3:
                            if(!vector[3]){
                                group.AddTop(std::make_shared<WizardGremlin>(pos[num][0],pos[num][1]));
                                vector[3]++;
                            }
                            break;
                        case 4:
                            if(!vector[4]){
                                group.AddTop(std::make_shared<ShieldGremlin>(pos[num][0],pos[num][1]));
                                vector[4]++;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
                return;
            case GroupName::Large_Slime:
                rng.NextInt(0,2)==0?group.AddTop(std::make_shared<SpikeSlimeL>(0.0F, 0.0F)):group.AddTop(std::make_shared<AcidSlimeL>(0.0F, 0.0F));
                return;
            case GroupName::Lots_of_Slimes:{
                float pos[5][2]={{-480.0F, 30.0F},{-320.0F, 2.0F},{-160.0F, 32.0F},{10.0F, -12.0F},{200.0F, 9.0F}};
                for(size_t i=0;i<3;i++)
                    group.AddTop(std::make_shared<SpikeSlimeS>(pos[i][0],pos[i][1]));
                for(size_t i=0;i<2;i++)
                    group.AddTop(std::make_shared<AcidSlimeS>(pos[i+3][0],pos[i+3][1])); 
                return;
            }

            case GroupName::Red_Slaver:
                group.AddTop(std::make_shared<RedSlaver>(0.0F, 0.0F));
                return;
            case GroupName::Blue_Slaver:
                group.AddTop(std::make_shared<BlueSlaver>(0.0F, 0.0F));
                return;
            case GroupName::_3_Louse:{
                float pos[3][2]={{-350.0F, 25.0F},{-125.0F, 10.0F},{80.0F, 30.0F}};
                for(size_t i=0;i<3;i++)
                    rng.NextInt(0,2)==0?group.AddTop(std::make_shared<RedLouse>(pos[i][0],pos[i][1]))
                                    :group.AddTop(std::make_shared<GreenLouse>(pos[i][0],pos[i][1]));
                return;
            }

            case GroupName::_2_Fungi_Beasts:{
                float pos[2][2]={{-400.0F, 30.0F},{-40.0F, 20.0F}};
                for(size_t i=0;i<2;i++)
                    group.AddTop(std::make_shared<FungiBeast>(pos[i][0],pos[i][1]));
                return;
            }

            case GroupName::Exordium_Thugs:{
                switch (rng.NextInt(0,4)){
                    case 0:
                        group.AddTop(std::make_shared<RedLouse>(-160.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 1:
                        group.AddTop(std::make_shared<GreenLouse>(-160.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 2:
                        group.AddTop(std::make_shared<AcidSlimeM>(-160.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 3:
                        group.AddTop(std::make_shared<SpikeSlimeM>(-160.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    default:
                        break;
                }
                switch (rng.NextInt(0,4)){
                    case 0:
                        group.AddTop(std::make_shared<Looter>(130.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 1:
                        group.AddTop(std::make_shared<Cultist>(130.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 2:
                        group.AddTop(std::make_shared<BlueSlaver>(130.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 3:
                        group.AddTop(std::make_shared<RedSlaver>(130.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    default:
                        break;
                }
                return;
            }

            case GroupName::Exordium_Wildlife:
                switch (rng.NextInt(0,2)){
                    case 0:
                        group.AddTop(std::make_shared<FungiBeast>(-150.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 1:
                        group.AddTop(std::make_shared<JawWorm>(-150.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    default:
                        break;
                }
                switch (rng.NextInt(0,4)){
                    case 0:
                        group.AddTop(std::make_shared<RedLouse>(150.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 1:
                        group.AddTop(std::make_shared<GreenLouse>(150.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 2:
                        group.AddTop(std::make_shared<AcidSlimeM>(150.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    case 3:
                        group.AddTop(std::make_shared<SpikeSlimeM>(150.0F+rng.NextInt(-20,21),20.0F+rng.NextInt(-20,21)));
                        break;
                    default:
                        break;
                }
                return;
            case GroupName::Looter:
                group.AddTop(std::make_shared<Looter>(0.0F, 0.0F));
                return;
            case GroupName::None:
                group.AddTop(std::make_shared<FatGremlin>(0.0F, 0.0F));
                return;
            default:
                LOG_ERROR("The Group:{} is has not be set yet",static_cast<int>(group_name));
                return;
        }
        
    }
}