#pragma once
#include "item.h"
#include "player.h"
#include "matchEvent.h"

#include <variant>

namespace Entities
{
	class ActiveEffect
	{
	public:

		ActiveEffect(ItemType effect, float duration, std::variant<Ball*,Player*> target) : effectType(effect), remainingTime(duration),
			target(target) {};

		void update(float);
		void apply();
		bool isEffectFinished() const { return isFinished; }
		void reset();


	private:
		float remainingTime{};
		ItemType effectType{};
		std::variant<Ball*, Player*> target{};
		bool isFinished{ false };	
	};

	constexpr Util::Vec2 yAxisItemSpawns[6] =
	{
		//TODO
	};
}