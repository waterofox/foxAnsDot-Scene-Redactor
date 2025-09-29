#include "UI_Component.h"

void UI_Component::handle_new_size(sf::Vector2f& new_size)
{
	if (max_width < new_size.x and max_width != -1)
	{
		new_size.x = max_width;
	}
	if (max_heigth < new_size.y and max_heigth != -1)
	{
		new_size.y = max_heigth;
	}
	if (min_width > new_size.x and min_width != -1)
	{
		new_size.x = min_width;
	}
	if (min_heigth > new_size.y and min_heigth != -1)
	{
		new_size.y = min_heigth;
	}
}

void UI_Component::set_min_heigth(const float& arg)
{
	min_heigth = arg;
}

void UI_Component::set_min_width(const float& arg)
{
	min_width = arg;
}

void UI_Component::set_max_heigth(const float& arg)
{
	max_heigth = arg;
}

void UI_Component::set_max_width(const float& arg)
{
	max_width = arg;
}
