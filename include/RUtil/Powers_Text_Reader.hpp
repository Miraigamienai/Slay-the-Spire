#pragma once

#include <array>
#include <memory>

//fwd decl
namespace Draw{
    class Text_layout;
}

namespace RUtil{
enum class Powers_Text_ID:int{
    //power 178
    Accuracy,Adaptation,After_Image,AlwaysMad,Amplify,AngelForm,Anger,Angry,Artifact,Attack_Burn,BackAttack,Barricade,BattleHymn,BeatOfDeath,Berserk,Bias,BlockReturnPower,Blur,Brutality,Buffer,Bullet_Time,Burst,CannotChangeStancePower,Choked,Collect,Combust,Compulsive,Condense,Confusion,Conserve,Constricted,Controlled,CorpseExplosionPower,Corruption,Creative_AI,Curiosity,Curl_Up,Dance_Puppet,Dark_Embrace,Demon_Form,DevaForm,DevotionPower,DexLoss,Dexterity,DisciplinePower,Double_Damage,Double_Tap,Draw,Draw_Card,Draw_Down,Draw_Reduction,DuplicationPower,Echo_Form,Electro,EmotionalTurmoilPower,EndTurnDeath,Energized,EnergizedBlue,EnergyDownPower,Entangled,Envenom,Equilibrium,EstablishmentPower,Evolve,Explosive,Extra_Cards,Fading,Feel_No_Pain,Fire_Breathing,Flame_Barrier,Flex,FlickPower,Flight,FlowPower,Focus,Frail,FreeAttackPower,FreeToPlayPower,Gambit,Generic_Strength_Up_Power,Grounded,GrowthPower,Heatsink,Hello,Hex,Hide,HotHot,Infinite_Blades,Intangible,IntangiblePlayer,Inverted,Invincible,Juggernaut,Knowledge,Life_Link,LikeWaterPower,Lockon,Loop,Machine_Learning,Magnetism,Malleable,Mantra,MasterRealityPower,Mastery,Mayhem,Metallicize,Minion,Mode_Shift,Next_Turn_Block,Night_Terror,Nirvana,NoBlockPower,NoSkills,No_Attack,No_Draw,Noxious_Fumes,Nullify_Attack,OmegaPower,OmnisciencePower,Painful_Stabs,Panache,PathToVictoryPower,Pen_Nib,Phantasmal,Plated_Armor,Poison,Prime,Primitive,Rage,Rebound,Reduce_Damage,Regenerate,Regeneration,Repair,Repulse,Retain_Cards,Retain_Hand,Retribution,Riposte,Ritual,Rupture,Sadistic,Serenity,Serpentine,Shackled,Sharp_Hide,Shifting,Shriek_From_Beyond,Skill_Burn,Slow,Split,Spore_Cloud,Stasis,StaticDischarge,Storm,Strength,StrikeUp,Study,Surrounded,TheBomb,Thievery,Thorns,Thousand_Cuts,TimeMazePower,Time_Warp,Tools_Of_The_Trade,Unawakened,Unstable,Vault,Venomology,Vigor,Vulnerable,WaveOfTheHandPower,WaveOfTheHandPower2,Weakened,WireheadingPower,Wraith_Form_v2,WrathNextTurnPower

    ,SIZE
};

class Powers_Text_Reader
{
public:
    Powers_Text_Reader()=delete;~Powers_Text_Reader()=delete;Powers_Text_Reader(const Powers_Text_Reader &) = delete;Powers_Text_Reader(Powers_Text_Reader &&) = delete;Powers_Text_Reader &operator=(const Powers_Text_Reader &) = delete;Powers_Text_Reader &operator=(Powers_Text_Reader &&) = delete;
    static const std::array<std::shared_ptr<Draw::Text_layout>, 2> &GetDescriptions(const Powers_Text_ID id);
    static const std::shared_ptr<Draw::Text_layout> &GetName(const Powers_Text_ID id);
    static constexpr auto FILENAME="powers.json";
};
}