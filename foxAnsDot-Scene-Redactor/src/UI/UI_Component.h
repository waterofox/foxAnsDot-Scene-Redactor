#pragma once

#include <foxAndDot-SDK/Core.h>
class UI_Component : public Scene_Component, public sf::Drawable
{
protected:
	//-1 means "no limit"
	float min_heigth = -1;
	float min_width = -1;

	float max_heigth = -1;
	float max_width = -1;
public:
	sf::RectangleShape body;

	virtual ~UI_Component() = default;

	void handle_new_size(sf::Vector2f& new_size);

	void set_min_heigth(const float& arg);
	void set_min_width(const float& arg);

	void set_max_heigth(const float& arg);
	void set_max_width(const float& arg);
};

