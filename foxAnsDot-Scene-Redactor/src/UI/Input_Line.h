#pragma once
#include "Label.h"

class Input_Line : public Scene_Component, public sf::Drawable
{
private:
	enum side
	{
		right,
		left
	};

	bool is_active = false;

	std::string inputed_text = "";
	unsigned short int caret_pos = 0;

	unsigned short int fake_caret_pos = 0;
	sf::Vector2i showed_text_border = sf::Vector2i(0, 0);

	//view
	sf::RectangleShape body;
	sf::RectangleShape caret;
	Label text_label;
	bool show_caret = false;

	sf::Time caret_timer = sf::Time::Zero;

	void add_sign_in_text(const std::string& buffer);
	void remove_sign_from_text();

	void move_text(const side& side);

protected:
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void update(Core* the_core) override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)	override;

public:
	Input_Line();
	~Input_Line();
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds() override;

	
};