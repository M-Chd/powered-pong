#include "debugOverlay.h"

namespace UI
{
	void DebugOverlay::init(View& view,
		const std::string& fontPath, int fontSize, SDL_Color color,
		float x, float y, int lineCount)
	{
		this->color = color;
		font = std::shared_ptr<TTF_Font>(TTF_OpenFont(fontPath.c_str(), fontSize), TTF_CloseFont);
 
		int lineHeight = fontSize + 4;

		layers.reserve(lineCount);
		for (int i = 0; i < lineCount; ++i)
		{
			float lineY = y - (lineCount - i) * lineHeight;
			layers.push_back(view.addLayer(std::make_unique<UILayer>(Util::Vec2{ x, lineY })));
		}
	}
 
	void DebugOverlay::update(SDL_Renderer* renderer, const std::vector<std::string>& lines)
	{
		for (size_t i = 0; i < lines.size() && i < layers.size(); ++i)
			setLayerText(*layers[i], renderer, font.get(), lines[i], color);
	}
}