#pragma once

#include "vector2.hpp"

#include <string_view>
#include <array>

constexpr int MENU_FIRST_Y = 180;
constexpr int MENU_SPACING = 60;

namespace UI
{
	enum class MenuID
	{
		None,
		Main,
		Solo,
		Multiplayer,
		OnlineIP,
		Options,
		Rules
	};

	enum class GameAction
	{
		None,

		StartSoloEasy,
		StartSoloMedium,
		StartSoloHard,

		StartLocalMultiplayer,

		Back,
		Quit
	};

	struct ButtonDescription
	{
		std::string_view txt;
		Util::Vec2 position;
		MenuID menuID;
		GameAction action;
	};

	constexpr std::array<ButtonDescription,4> mainMenuButtons
	{ {
		{"Solo",{600,MENU_FIRST_Y + MENU_SPACING * 0},MenuID::Solo,GameAction::None},
		{"Multiplayer",{550,MENU_FIRST_Y + MENU_SPACING * 1},MenuID::Multiplayer,GameAction::None},
		{"Options",{580,MENU_FIRST_Y + MENU_SPACING * 2},MenuID::Options,GameAction::None},
		{"Quit",{600,MENU_FIRST_Y + MENU_SPACING * 3},MenuID::None,GameAction::Quit}
	} };

	constexpr std::array<ButtonDescription,4> soloMenuButtons
	{{
		{"Easy",{600,MENU_FIRST_Y + MENU_SPACING * 0},MenuID::None,GameAction::StartSoloEasy},
		{"Medium",{580,MENU_FIRST_Y + MENU_SPACING * 1},MenuID::None,GameAction::StartSoloMedium},
		{"Hard",{600,MENU_FIRST_Y + MENU_SPACING * 2},MenuID::None,GameAction::StartSoloHard},
		{"Back",{600,MENU_FIRST_Y + MENU_SPACING * 3},MenuID::None,GameAction::Back}
	}};

	constexpr std::array<ButtonDescription,1> IpMenuButtons
	{
		{"Back",{600,MENU_FIRST_Y + MENU_SPACING * 1},MenuID::None,GameAction::Back}
	};

	constexpr std::array<ButtonDescription,3> multiPlayerButtons
	{ {
		{"Local Multiplayer",{500,MENU_FIRST_Y + MENU_SPACING * 0},MenuID::None,GameAction::StartLocalMultiplayer},
		{"Online MultiPlayer",{500,MENU_FIRST_Y + MENU_SPACING * 1},MenuID::OnlineIP,GameAction::None},
		{"Back",{600,MENU_FIRST_Y + MENU_SPACING * 2},MenuID::None,GameAction::Back}
	} };

	constexpr std::array<ButtonDescription,2> optionsButtons
	{ {
		{"Rules",{600,MENU_FIRST_Y + MENU_SPACING * 0},MenuID::Rules,GameAction::None },
		{"Back",{600,MENU_FIRST_Y + MENU_SPACING * 1},MenuID::None,GameAction::Back}
	} };
}