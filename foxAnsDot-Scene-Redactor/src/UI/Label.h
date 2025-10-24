#pragma once
#include <foxAndDot-SDK/Core.h>
#include "base/UI_Component.h"


class Label : public UI_Component
{

	static inline sf::Font defualt_font{}; //empty
public:
	sf::Text* label = nullptr;
protected:
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	void update(Core* the_core) override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds() override;

	
public:
	Label();
	Label(const std::string& text);
	~Label();

};