#pragma once

#include "Button.h"
#include "../NON-MANAGED/Icon.h"

class Button_Icon : public Button
{
	Icon icon;
	
	void draw(sf::RenderTarget&, sf::RenderStates) const override;

	void update(Core* the_core) override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

public:
	Button_Icon();
	Button_Icon(Core::slot_type on_click);

	~Button_Icon();
};

