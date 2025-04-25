#include "Game_object/character/Monster_group_creater.hpp"
#include "Game_object/character/Monster_group.hpp"
#include "Game_object/character/AllMonster.hpp"
#include "RUtil/Random.hpp"

#include "Util/Logger.hpp"

namespace Monster{
    void Monster_group_creater::CreateGroup(Monster_group &group,GroupName group_name,RUtil::Random &rng){
        switch(group_name){
            case GroupName::Cultist:
                group.AddTop(std::make_shared<Cultist>());
                return;
            case GroupName::_2_Louse:
                rng.NextInt(0,2)==0?group.AddTop(std::make_shared<RedLouse>()):group.AddTop(std::make_shared<GreenLouse>());
                return;
            case GroupName::Small_Slimes:
                rng.NextInt(0,2)==0?group.AddTop(std::make_shared<SpikeSlimeM>()):group.AddTop(std::make_shared<AcidSlimeM>());
                rng.NextInt(0,2)==0?group.AddTop(std::make_shared<SpikeSlimeS>()):group.AddTop(std::make_shared<AcidSlimeS>());
                group.AddTop(std::make_shared<Cultist>());
                return;
            case GroupName::Gremlin_Gang:{
                int vector[5]={0,0,0,0,0};
                while (vector[0]+vector[1]+vector[2]+vector[3]+vector[4]<4){
                    switch (rng.NextInt(0,5))
                    {
                        case 0:
                            if(vector[0]<2){
                                // group.AddTop(std::make_shared<MadGremlin>());
                                vector[0]++;
                            }
                            break;
                        case 1:
                            if(vector[1]<2){
                                // group.AddTop(std::make_shared<SneakyGremlin>());
                                vector[1]++;
                            }
                            break;
                        case 2:
                            if(vector[2]<2){
                                group.AddTop(std::make_shared<FatGremlin>());
                                vector[2]++;
                            }
                            break;
                        case 3:
                            if(!vector[3]){
                                // group.AddTop(std::make_shared<GremlinWizard>());
                                vector[3]++;
                            }
                        case 4:
                            if(!vector[4]){
                                // group.AddTop(std::make_shared<ShieldGremlin>());
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
                rng.NextInt(0,2)==0?group.AddTop(std::make_shared<SpikeSlimeL>()):group.AddTop(std::make_shared<AcidSlimeL>());
                return;
            case GroupName::Lots_of_Slimes:
                for(size_t i=0;i<3;i++)
                    group.AddTop(std::make_shared<SpikeSlimeS>());
                for(size_t i=0;i<2;i++)
                    group.AddTop(std::make_shared<AcidSlimeS>());
                return;
            case GroupName::Red_Slaver:
                // group.AddTop(std::make_shared<RedSlaver>());
                return;
            case GroupName::Blue_Slaver:
                // group.AddTop(std::make_shared<BlueSlaver>());
                return;
            case GroupName::_3_Louse:
                // for(size_t i=0;i<3;i++)
                    rng.NextInt(0,2)==0?group.AddTop(std::make_shared<RedLouse>()):group.AddTop(std::make_shared<GreenLouse>());
                return;
            case GroupName::_2_Fungi_Beasts:
                // for(size_t i=0;i<2;i++)
                    // group.AddTop(std::make_shared<FungiBeast>());
                return;
            case GroupName::Exordium_Thugs:
                switch (rng.NextInt(0,9)){
                    case 0:
                        group.AddTop(std::make_shared<RedLouse>());
                        break;
                    case 1:
                        group.AddTop(std::make_shared<GreenLouse>());
                        break;
                    case 2:
                        group.AddTop(std::make_shared<AcidSlimeM>());
                        break;
                    case 3:
                        group.AddTop(std::make_shared<SpikeSlimeM>());
                        break;
                    case 4:
                        // group.AddTop(std::make_shared<Looter>());
                        break;
                    case 5:
                        // group.AddTop(std::make_shared<Mugger>());
                        break;
                    case 6:
                        group.AddTop(std::make_shared<Cultist>());
                        break;
                    case 7:
                        // group.AddTop(std::make_shared<BlueSlaver>());
                        break;
                    case 8:
                        // group.AddTop(std::make_shared<RedSlaver>());
                        break;
                    default:
                        break;
                }
                return;
            case GroupName::Exordium_Wildlife:
                switch (rng.NextInt(0,6)){
                    case 0:
                        // group.AddTop(std::make_shared<FungiBeast>());
                        break;
                    case 1:
                        group.AddTop(std::make_shared<JawWorm>());
                        break;
                    case 2:
                        group.AddTop(std::make_shared<RedLouse>());
                        break;
                    case 3:
                        group.AddTop(std::make_shared<GreenLouse>());
                        break;
                    case 4:
                        group.AddTop(std::make_shared<AcidSlimeM>());
                        break;
                    case 5:
                        group.AddTop(std::make_shared<SpikeSlimeM>());
                        break;
                    default:
                        break;
                }
                return;
            case GroupName::Looter:
                // rng.NextInt(0,2)==0?group.AddTop(std::make_shared<Looter>()):group.AddTop(std::make_shared<Mugger>());
                return;
            case GroupName::None:
                group.AddTop(std::make_shared<FatGremlin>());
                return;
            default:
                LOG_ERROR("The Group:{} is has not be set yet",static_cast<int>(group_name));
                return;
        }
        group.AddTop(std::make_shared<FatGremlin>());
        
    }
}