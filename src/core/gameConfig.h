#pragma once

namespace Core
{
	struct GameConfig
	{
		enum class Mode
		{
			Solo,
			LocalMP,
			OnlineMp
		};

		Mode mode{ Mode::Solo };
		bool debug{ false };
	};

	GameConfig parseArgs(int argc, char* argv[]);
}