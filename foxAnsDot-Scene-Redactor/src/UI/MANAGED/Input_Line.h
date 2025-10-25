#pragma once
#include "../UI_Component.h"
#include "../NON-MANAGED/Label.h"

#define LIGHT_GREY sf::Color(211, 211, 211, 255)
#define  DARK_GREY sf::Color(169, 169, 169, 255)
#define  GAINSBORO sf::Color(220, 220, 220, 255)
#define     SILVER sf::Color(192, 192, 192, 255)

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
	//body view
	sf::Color body_color_memory = sf::Color(SILVER);
	sf::Color active_color = sf::Color::White;
	//text
	std::string inputed_text = "";
	unsigned short int rcp = 0;
	unsigned short int vcp = 0;

	//text view
	sf::RectangleShape text_area;
	Label text_label;
	sf::Vector2i text_border = sf::Vector2i(0, 0);

	//process
	input_event recent_input_event = input_event::unknown;
	void handle_input_event(Core*& the_core);

	//caret
	sf::RectangleShape caret;
	sf::Time caret_time = sf::Time::Zero;
	bool visible_caret = false;

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

	void set_active_color(const sf::Color& color);
};