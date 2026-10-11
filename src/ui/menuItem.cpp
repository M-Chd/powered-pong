#include "menuItem.h"

namespace UI
{
	template <typename T>
	std::string RangeItem<T>::label() const
	{
		return name + ": <" + std::to_string(value) + " >";
	}

	template <typename T>
	void RangeItem<T>::onLeft()
	{
		if (value -= step < 0)
		{
			value = min;
		}
		else
		{
			value -= step;
		}
	}

	template <typename T>
	void RangeItem<T>::onRight()
	{
		if (value += step > max)
		{
			value = max;
		}
		else
		{
			value += step;
		}
	}


}