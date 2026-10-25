#pragma once
#include <string>
#include <cstdio>
#include <utility>
#include "util/vector2.hpp"
#include "util/util.h"


namespace UI
{
	enum class MenuID
	{
		None,
		Main,
		Pause,
		Solo,
		Multiplayer,
		OnlineIP,
		Options,
		Rules,
		Play_rules
	};

	enum class GameAction
	{
		None,

		StartSoloEasy,
		StartSoloMedium,
		StartSoloHard,
		StartCustomGame,

		StartLocalMultiplayer,

		Resume,
		BackToMenu,

		HostGame,
		JoinGame,

		Back,
		Quit
	};

	struct Action
	{
		MenuID menuid;
		GameAction action;
	};

	//interface d'un composant de menu
	class MenuItem
	{
	public:
		virtual ~MenuItem() = default;
		virtual std::string label() const = 0;
		virtual void onLeft() {};
		virtual void onRight() {};
		virtual Action onActivate() { return {}; }
	};

	class ButtonItem : public MenuItem
	{
	public:
		ButtonItem(std::string name, Action action)
			: name(std::move(name)), action(action)
		{
		}

		std::string label() const override { return name; }

		Action onActivate() override
		{
			return { action.menuid, action.action };
		}

	private:
		std::string name;
		Action action;
		Util::Vec2 pos;
	};

	// represente un Item toggle qui permet d'etre activer ou non (ce que j'ai compris)
	class ToggleItem : public MenuItem
	{
	public:
		ToggleItem(std::string name, bool& value) : name(std::move(name)), value(value)
		{ }
		std::string label() const override { return name + ": " + (value ? "ON" : "OFF"); }
		void onLeft() override { value = !value; }
		void onRight() override { value = !value; }
		Action onActivate() override { value = !value; return{}; }
	private:
		std::string name;
		bool& value;
	};

	// represente un champ qui peut defiler de gauche a droite avec une valeure
	// Possede une valeur min et une valeur max
	template <typename T>
	class RangeItem : public MenuItem
	{
	public:
		RangeItem(std::string name, T& value, T minValue, T maxValue, T step)
        : name(std::move(name)), value(value),
          min(minValue), max(maxValue), step(step) {}

		std::string label() const override
		{
			return name + ": < " + this->toText(value) + " >";
		}

		void onLeft() override
		{
			if (value > min + step)
			{
				value -= step;
			}
			else
			{
				value = min;
			}
		}

		void onRight() override
		{
			if (value + step < max)
			{
				value += step;
			}
			else
			{
				value = max;
			}
		}
	private:
		static std::string toText(float value) { return Util::fmt(value); }
		static std::string toText(unsigned int value) { return std::to_string(value); }
	private:
		std::string name;
		T& value;
		T min;
		T max;
		T step;
	};
}