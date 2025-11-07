#pragma once
#include "../LAYOUT/Horizontal_Layout.h"
#include "../LAYOUT/Vertical_Layout.h"
#include "../MANAGED/Button.h"
#include <map>

class Scrollbar : public Horizontal_Layout
{
	//bar	
	Vertical_Layout bar;
	std::vector<UI_Component*> bar_members;
	//bar data
	int showed_members_count = 0;

	//scroll 
	Button* to_up = nullptr;
	Button* to_down = nullptr;

	void handle_buttons(Core* the_core, Scene_Component* button);
	
	//scroll data
	bool is_scrolled = false;
	int top_border = 0;

	//scroll view
	Vertical_Layout slider_area;
	sf::RectangleShape slider;

	Horizontal_Layout top_section;
	Horizontal_Layout bottom_section;

	//OVERRIDED
	void update(Core* the_core) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

public:

	Scrollbar();
	
	void set_showed_elements_count(const int& arg);
	void add_element(UI_Component* new_component);
	void remove_element(UI_Component* component);

};

