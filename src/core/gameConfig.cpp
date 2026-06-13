#include "gameConfig.h"

namespace Core
{
	GameConfig parseArgs(int argc, char* argv[])
	{
		GameConfig cfg;

		for (int i = 1; i < argc; i++)
		{
			if (argv[i] == "-lmp")
				cfg.mode = GameConfig::Mode::LocalMP;

			if (argv[i] == "-mp")
				cfg.mode = GameConfig::Mode::OnlineMp;

			if (argv[i] == "-debug")
				cfg.debug = true;
		}
		return cfg;
	}
}