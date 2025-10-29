#pragma once
#include "../LAYOUT/Horizontal_Layout.h"
#include "../LAYOUT/Vertical_Layout.h"
#include "../MANAGED/Button.h"
#include <map>

class Scrollbar : public Horizontal_Layout
{
	
	//scroll
	Button* to_up = nullptr;
	Button* to_down = nullptr;

	void handle_buttons(Core* the_core, Scene_Component* button);

	Vertical_Layout slider_area;
	sf::FloatRect slider;

	Horizontal_Layout top_section;
	Horizontal_Layout bottom_section;
	//bar	
	Vertical_Layout bar;
	sf::Vector2i  ratio;

	//OVERRIDED
	void update(Core* the_core) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

public:

	Scrollbar();
	
	void set_ratio(const sf::Vector2i& new_ratio);
	void add_element(const Layout*& new_component);
	void remove_element(const Layout*& component);

};

