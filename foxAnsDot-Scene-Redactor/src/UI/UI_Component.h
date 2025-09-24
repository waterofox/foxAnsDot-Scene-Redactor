#pragma once

#include <foxAndDot-SDK/Core.h>
class UI_Component : public Scene_Component, public sf::Drawable
{
public:
	sf::RectangleShape body;

	virtual ~UI_Component() = default;
};

