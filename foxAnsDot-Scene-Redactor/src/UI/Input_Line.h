#pragma once
#include "base/UI_Component.h"
#include "Label.h"


class Input_Line : public UI_Component
{
private:
	enum input_event
	{
		unknown,
		push_back,
		insert,
		pop_back,
		erase,
		move_rigth,
		move_left
	};

	bool is_active = false;

	//text
	std::string inputed_text = "";
	unsigned short int rcp = 0;
	unsigned short int vcp = 0;

	sf::RectangleShape text_area;
	Label text_label;
	sf::Vector2i text_border = sf::Vector2i(0, 0);

	input_event recent_input_event = input_event::unknown;

	void handle_input_event(Core*& the_core);

	sf::RectangleShape caret;

private:
	//overrided fox&Dot SDK
	
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void update(Core* the_core) override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)	override;

	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds() override;

	// overrided SFML

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Input_Line();
	~Input_Line();

	const std::string&  get_text();
	const bool& is_active_now();
};