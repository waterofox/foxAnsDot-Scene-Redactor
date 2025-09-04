#include "Input_Line.h"
#include "../Application.h"

#define LIGHT_GREY sf::Color(211, 211, 211, 255)
#define  DARK_GREY sf::Color(169, 169, 169, 255)
#define  GAINSBORO sf::Color(220, 220, 220, 255)
#define     SILVER sf::Color(192, 192, 192, 255)

void Input_Line::add_sign_in_text(const std::string& buffer)
{
	inputed_text.insert(inputed_text.begin()+caret_pos,buffer[0]);
	caret_pos += 1;
}
void Input_Line::remove_sign_from_text()
{
	inputed_text.erase(inputed_text.begin() + (caret_pos-1));
	caret_pos -= 1;
}


sf::Drawable* Input_Line::as_drawable() { return this; }

sf::FloatRect Input_Line::get_component_render_bounds() { return body.getGlobalBounds(); }
sf::FloatRect Input_Line::get_component_bounds() { return body.getGlobalBounds(); }

Input_Line::Input_Line()
{
	is_active = false;

	body.setFillColor(SILVER);
	body.setOutlineColor(sf::Color::Black);

	body.setOutlineThickness(5);
	body.setSize(sf::Vector2f(300, 20));

	text_label.setFillColor(sf::Color::Black);
	text_label.setCharacterSize(12);
}
Input_Line::~Input_Line() {}

void Input_Line::on_intersection(Core* the_core, Scene_Component* component) {}

void Input_Line::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) 
{
	text_label.update_resource(resource);
}



void Input_Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body,states);
	target.draw(text_label, states);
}

void Input_Line::update(Core* the_core)
{
	APPLICATION
		
		if (!application.recent_clicks.empty())
		{
			sf::Event::MouseButtonPressed& re_click = application.recent_clicks.front();
			if (body.getGlobalBounds().contains(application.mapPixelToCoords(re_click.position)))
			{
				if (!is_active)
				{
					application.recent_keyboard_input = "";
					body.setFillColor(GAINSBORO);
				}
				is_active = true;
				application.recent_clicks.pop();
			}
			else 
			{
				body.setFillColor(SILVER);
				is_active = false; 
			}
		}

		if (is_active)
		{
			if (application.recent_keyboard_input.length() != 0) {
				add_sign_in_text(application.recent_keyboard_input);
				application.recent_keyboard_input = "";
			}
			if (application.remove_sign) {
				if (inputed_text.length() != 0)
				{
					remove_sign_from_text();
				}
				application.remove_sign = false;
			}
		}

	text_label.setPosition(body.getPosition());
	text_label.setString(inputed_text);
}

