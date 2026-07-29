#include "item.h"

namespace Entities
{
	void Item::draw(SDL_Renderer* r)
	{
		if (_icon)
		{
			//icon
		}
		else
		{
			SDL_SetRenderDrawColor(r, _color.r, _color.g, _color.b, _color.a);
			SDL_Rect rect = { (int)(_position.x),(int)_position.y,(int)_size,(int)_size };
			SDL_RenderFillRect(r, &rect);
		}
	}

	bool Item::isInside(Util::Vec2 p)
	{
		return p.x >= _position.x && p.y >= _position.y && p.x <= _position.x + _size && p.y <= _position.y + _size;
	}
}