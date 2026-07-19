#pragma once

#include "vector2.hpp"

#include <string_view>
#include <array>

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
		{"Solo",{100,50},MenuID::Solo,GameAction::None},
		{"Multiplayer",{100,60},MenuID::Multiplayer,GameAction::None},
		{"Options",{100,70},MenuID::Options,GameAction::None},
		{"Quit",{100,80},MenuID::None,GameAction::Quit}
	} };

	constexpr std::array<ButtonDescription,4> soloMenuButtons
	{{
		{"Easy",{100,50},MenuID::None,GameAction::StartSoloEasy},
		{"Medium",{100,60},MenuID::None,GameAction::StartSoloMedium},
		{"Hard",{100,70},MenuID::None,GameAction::StartSoloHard},
		{"Back",{100,80},MenuID::None,GameAction::Back}
	}};

	constexpr std::array<ButtonDescription,1> IpMenuButtons
	{
		{"Back",{100,70},MenuID::None,GameAction::Back}
	};

	constexpr std::array<ButtonDescription,3> multiPlayerButtons
	{ {
		{"Local Multiplayer",{100,50},MenuID::None,GameAction::StartLocalMultiplayer},
		{"Online MultiPlayer",{100,60},MenuID::OnlineIP,GameAction::None},
		{"Back",{100,70},MenuID::None,GameAction::Back}
	} };

	constexpr std::array<ButtonDescription,2> optionsButtons
	{ {
		{"Rules",{100,50},MenuID::Rules,GameAction::None },
		{"Back",{100,60},MenuID::None,GameAction::Back}
	} };
}