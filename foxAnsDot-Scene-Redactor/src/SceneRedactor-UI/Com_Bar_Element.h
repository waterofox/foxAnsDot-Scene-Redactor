#pragma once
#include "../UI/LAYOUT/Horizontal_Layout.h"
#include "../UI/MANAGED/Button.h"
#include "../UI/MANAGED/Input_Line.h"

#include "../UI/NON-MANAGED/Icon.h"

class Com_Bar_Element : public Horizontal_Layout
{	
	Icon el_icon;
	Input_Line name_of_component;
	Button* body_button = nullptr;

	void handle_click(Core* the_core, Scene_Component* component);


	//OVERRIDED
	void update(Core* the_core) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

public:
	Com_Bar_Element();
	~Com_Bar_Element();
};

