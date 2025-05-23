#pragma once

#include <vector>
#include <memory>

//fwd decl
namespace Draw{
    class Text_layout;
}

namespace RUtil{
enum class Cards_Text_ID:int{
    //cards.json 423
    A_Thousand_Cuts,Accuracy,Acrobatics,Adaptation,Adrenaline,After_Image,Aggregate,All_For_One,All_Out_Attack,Allocate,Alpha,Amplify,Anger,Apotheosis,Armaments,AscendersBane,Auto_Shields,AwakenedStrike,Axe_Kick,Backflip,Backstab,Ball_Lightning,Bandage_Up,Bane,Barrage,Barricade,Bash,BattleHymn,Battle_Trance,Beam_Cell,BecomeAlmighty,Berserk,Beta,Biased_Cognition,BigBrain,Bite,Blade_Dance,Blasphemy,Blaster,Blessed,Blind,Blizzard,Blood_for_Blood,Bloodletting,Bludgeon,Blur,Body_Slam,BootSequence,Bouncing_Flask,BowlingBash,Brilliance,BrillianceAura,Brutality,Buffer,Bullet_Time,Burn,Burning_Pact,Burst,Calculated_Gamble,Calm,Caltrops,Capacitor,Carnage,CarveReality,Catalyst,Causality,Chaos,Chill,Choke,Chrysalis,Clarity,Clash,CleanseEvil,ClearTheMind,Cleave,Cloak_And_Dagger,Clothesline,Clumsy,Cold_Snap,Collect,Combust,Compile_Driver,Concentrate,Conclude,ConjureBlade,Consecrate,Conserve_Battery,Consume,Coolheaded,Core_Surge,Corpse_Explosion,Corruption,Creative_AI,Crescendo,CrescentKick,Crippling_Poison,CrushJoints,CurseOfTheBell,CutThroughFate,Dagger_Spray,Dagger_Throw,Dark_Embrace,Dark_Shackles,Darkness,Dash,Dazed,Deadly_Poison,Decay,DeceiveReality,Deep_Breath,Defend_B,Defend_G,Defend_P,Defend_R,Deflect,Defragment,Demon_Form,DeusExMachina,DevaForm,Devotion,Die_Die_Die,Disarm,Discipline,Discovery,Distraction,Dodge_and_Roll,Doom_and_Gloom,Doppelganger,Double_Energy,Double_Tap,Doubt,Dramatic_Entrance,Dropkick,Dual_Wield,Dualcast,Echo_Form,Electrodynamics,EmptyBody,EmptyFist,EmptyMind,Endless_Agony,Energy_Pulse,Enlightenment,Entrench,Envenom,Eruption,Escape_Plan,Establishment,Evaluate,Eviscerate,Evolve,Exhume,Experienced,Expertise,Expunger,FTL,FameAndFortune,Fasting,Fasting2,FearNoEvil,Feed,Feel_No_Pain,Fiend_Fire,Finesse,Finisher,Fire_Breathing,Fission,FlameMastery,Flame_Barrier,Flare,Flash_of_Steel,Flechettes,Flex,Flick,Flicker,Flow,FlowState,FlurryOfBlows,Flux_Capacitor,FlyingSleeves,Flying_Knee,FollowUp,Footwork,Force_Field,ForeignInfluence,Forethought,FuryAura,Fusion,Gash,Genetic_Algorithm,Ghostly,Ghostly_Armor,Glacier,Glass_Knife,Go_for_the_Eyes,Good_Instincts,Grand_Finale,Halt,HandOfGreed,Havoc,Headbutt,Heatsinks,Heavy_Blade,Heel_Hook,Hello_World,Hemokinesis,Hide,Hologram,Hyperbeam,Immolate,Impatience,Impervious,Indignation,Infernal_Blade,Infinite_Blades,Inflame,Injury,InnerPeace,Insight,Intimidate,Iron_Wave,J_A_X_,Jack_Of_All_Trades,Judgement,Juggernaut,JustLucky,Leap,Leg_Sweep,LessonLearned,LetFateDecide,LikeWater,Limit_Break,LiveForever,Lockon,Loop,Machine_Learning,Madness,Magnetism,Malaise,MasterReality,Master_of_Strategy,Masterful_Stab,Mastery,Mayhem,Meditate,Melter,MentalFortress,Metallicize,Metamorphosis,Metaphysics,Meteor_Strike,Mind_Blast,Miracle,Multi_Cast,Necronomicurse,Neutralize,Night_Terror,Nirvana,Normality,Noxious_Fumes,Offering,Omega,Omniscience,Outmaneuver,Pain,PalmThatRestrains,Panacea,Panache,PanicButton,Parasite,PathToVictory,Peace,PerfectedForm,Perfected_Strike,Perseverance,Phantasmal_Killer,PiercingWail,Poisoned_Stab,Polymath,Pommel_Strike,Power_Through,Pray,Predator,Prediction,Prepared,Pride,Prostrate,Protect,Pummel,Punishment,Purity,Quick_Slash,Rage,Ragnarok,Rainbow,Rampage,ReachHeaven,Reaper,Reboot,Rebound,Reckless_Charge,Recycle,Redo,Reflex,Regret,Reinforced_Body,Reprogram,RetreatingHand,Retribution,Riddle_With_Holes,Rip_and_Tear,RitualDagger,Rupture,Sadistic_Nature,Safety,Sanctity,SandsOfTime,SashWhip,Scrape,Scrawl,Searing_Blow,Second_Wind,Secret_Technique,Secret_Weapon,Seeing_Red,Seek,Self_Repair,Sentinel,Serenity,Setup,Sever_Soul,Shame,Shield,Shiv,Shockwave,Shrug_It_Off,SignatureMove,Skewer,Skim,Slice,Slimed,Smite,SoothingAura,SpiritShield,Spot_Weakness,Stack,Static_Discharge,Steam,Steam_Power,StepAndStrike,Storm,Storm_of_Steel,Streamline,Strike_B,Strike_G,Strike_P,Strike_R,Study,SublimeSlice,Sucker_Punch,Sunder,Survey,Survivor,Sweeping_Beam,Swift_Strike,Swipe,Swivel,Sword_Boomerang,Tactician,TalkToTheHand,Tantrum,Tempest,Terror,The_Bomb,Thinking_Ahead,ThirdEye,ThroughViolence,Thunder_Strike,Thunderclap,Thwack,Tools_of_the_Trade,Torrent,Transcendence,Transmutation,Trip,True_Grit,Truth,Turbo,Twin_Strike,Underhanded_Strike,Undo,Unload,Unraveling,Uppercut,Vault,Vengeance,Venomology,Vigilance,Violence,Void,Wallop,Warcry,WardAura,WaveOfTheHand,WaveOfTheHand2,Weave,Well_Laid_Plans,WheelKick,Whirlwind,White_Noise,Wild_Strike,WindmillStrike,Windup,Wireheading,Wisdom,Wish,Worship,Wound,Wraith_Form_v2,Wrath,WreathOfFlame,Writhe,Zap

    ,SIZE
};
struct CardInfo{
    std::shared_ptr<Draw::Text_layout> name, desc, upgrade_desc;
};
class Cards_Text_Reader
{
public:
    Cards_Text_Reader()=delete;~Cards_Text_Reader()=delete;Cards_Text_Reader(const Cards_Text_Reader &) = delete;Cards_Text_Reader(Cards_Text_Reader &&) = delete;Cards_Text_Reader &operator=(const Cards_Text_Reader &) = delete;Cards_Text_Reader &operator=(Cards_Text_Reader &&) = delete;
    static const std::vector<std::shared_ptr<Draw::Text_layout>> &GetExtended(Cards_Text_ID id);
    static const CardInfo &GetInfo(Cards_Text_ID id);
    static constexpr auto FILENAME="cards.json";
};
}