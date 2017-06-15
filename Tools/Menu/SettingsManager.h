#pragma once
#include "../../stdafx.h"

//Don't change the location of max value, always at the end.
//And also add new vars to bottom of lists or it will cause problems in cfgs.
//Skeltal is the cutest
enum MenuTabs
{
	Tab_Legitbot = 0,
	Tab_Visuals,
	Tab_Misc,
	Tab_Skinchanger,
	Tab_Colors,
	Tab_Config,
	Tab_Ragebot,
	MAXVALUEMENU
};

enum Config
{
	Config_save,
	Config_load,
	Config_type,
};

enum RagebotTab
{
	Ragebot_AimbotEnabled,
	Ragebot_Selection,
	Ragebot_Hitbox,
	Ragebot_Multipoint,
	Ragebot_PS,
	Ragebot_Multibox,
	Ragebot_Velocity,
	Ragebot_AutoShoot,
	Ragebot_Autoscope,
	Ragebot_SilentAim,
	Ragebot_Hitchance,
	Ragebot_MinDamage,
	Ragebot_AcceptKill,
	AntiAim_Enabled,
	AntiAim_Pitch,
	AntiAim_Yaw,
	AntiAim_AtTargets,
	AntiAim_FakeHitbox,
	AntiAim_EdgeDetection,
	Ragebot_Resolver,
	Ragebot_Accuracy,
	Ragebot_PreferBodyAim,
	Ragebot_PositionAdjustment,
	Ragebot_GOTV,
	Ragebot_MultipointType,
	MAXVALUERAGE
};

enum Visualstab
{
	Visuals_Enable,
	Visuals_BoxEnabled,
	Visuals_BoxType,
	Visuals_EspTeam,
	Visuals_HealthBar,
	Visuals_ArmorBar,
	Visuals_Name,
	Visuals_Flashed,
	Visuals_Weapons,
	Visuals_AimLines,
	Visuals_Skeltal,
	Visuals_EngineRadar,
	Visuals_Hostage,
	Visuals_DroppedWeapons,
	Visuals_NoRecoil,
	Visuals_NoFlash,
	Visuals_NoSmoke,
	Visuals_ThirdPerson,
	Visuals_NoScope,
	Visuals_Chams,
	Visuals_ChamsXQZ,
	Visuals_ChamsTeam,
	Visuals_ChamsGuns,
	Visuals_XQZ,
	Visuals_Crosshair,
	Visuals_CrosshairDynamic,
	Visuals_C4,
	Visuals_Flags,
	Visuals_Dlights,
	Visuals_fov,
	MAXVALUEVISUALS
};

enum MiscTab
{
	Misc_WhichWeapon,
	Misc_AntiUntrusted,
	Misc_AutoJump,
	Misc_AutoStrafe,
	Misc_AutoStraferMode,
	Misc_ClanTagSpammer,
	Misc_ClanTagSelection,
	Misc_ClanTagAnimate,
	Misc_AutoAccept,
	Misc_FakeLag,
	Misc_Aimstep,
	Misc_ZStrafe,
	Misc_ZStrafeKey,
	Misc_CircleStrafe,
	Misc_CircleStrafeKey,
	Misc_UI,
	Misc_KnifeBot,
	MAXVALUEMISC
};

enum Skins
{
	MAXVALUESKINS
};

enum LegitbotTab
{
	Legitbot_enable,
	Legitbot_Aimonkey,
	Legitbot_fov,
	Legitbot_fovtype,
	Legitbot_smoothtype,
	Legitbot_smoothX,
	Legitbot_smoothY,
	Legitbot_multihitbox,
	Legitbot_hitbox,
	Legitbot_rcs,
	Legitbot_rcsforceX,
	Legitbot_rcsforceY,
	Legitbot_Aimbotkey,
	Legitbot_Smokecheck,
	Legitbot_Firedelay,
	MAXVALUELEGIT
};

enum colors
{
	Colors_chams_visible_r,
	Colors_chams_visible_g,
	Colors_chams_visible_b,
	Colors_chams_visible_a,
	Colors_chams_invisible_r,
	Colors_chams_invisible_g,
	Colors_chams_invisible_b,
	Colors_chams_invisible_a,
	Colors_controls_text_r,
	Colors_controls_text_g,
	Colors_controls_text_b,
	Colors_controls_text_a,
	Colors_controls_background_r,
	Colors_controls_background_g,
	Colors_controls_background_b,
	Colors_controls_background_a,
	Colors_background_r,
	Colors_background_g,
	Colors_background_b,
	Colors_background_a,
	Colors_outline_r,
	Colors_outline_g,
	Colors_outline_b,
	Colors_outline_a,
	Colors_sliders_r,
	Colors_sliders_g,
	Colors_sliders_b,
	Colors_sliders_a,
	Colors_sliders_back_r,
	Colors_sliders_back_g,
	Colors_sliders_back_b,
	Colors_sliders_back_a,
	Colors_menutitle_r,
	Colors_menutitle_g,
	Colors_menutitle_b,
	Colors_menutitle_a,
	Colors_menutab_r,
	Colors_menutab_g,
	Colors_menutab_b,
	Colors_menutab_a,
	MAXVALUECOLORS
};

enum weapongroups
{
	Group_Default = 0,
	Group_Rifle,
	Group_Pistol,
	Group_Shotgun,
	Group_SMG,
	Group_Heavy,
	Group_AWP,
	Group_Scout,
	Group_Othersnipers,
	MAXVALUEWEAPONGROUPS
};



class SettingsManger
{
public:
	bool weaponconfigs();

	static void SetSetting( int Tab, int Setting, double Value );

	static double GetSetting( int Tab, int Setting );

	static double GetSettingLegit(int Tab, int Setting);

	double GetPlayer( int index, int Tab, int Setting );

	static double GetMenuSetting( int Tab, int Setting );
};

extern SettingsManger Settings;
