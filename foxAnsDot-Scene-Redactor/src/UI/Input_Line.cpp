#include "Input_Line.h"
#include "../Application.h"

#define LIGHT_GREY sf::Color(211, 211, 211, 255)
#define  DARK_GREY sf::Color(169, 169, 169, 255)
#define  GAINSBORO sf::Color(220, 220, 220, 255)
#define     SILVER sf::Color(192, 192, 192, 255)

const std::string& Input_Line::get_text()
{
	return inputed_text;
}

void Input_Line::clear()
{

	
}

void Input_Line::add_sign_in_text(const std::string& buffer)
{

}
void Input_Line::remove_sign_from_text()
{

	
}

void Input_Line::move_text(const side& side)
{


}


sf::Drawable* Input_Line::as_drawable() { return this; }

sf::FloatRect Input_Line::get_component_render_bounds() { return body.getGlobalBounds(); }
sf::FloatRect Input_Line::get_component_bounds() { return body.getGlobalBounds(); }

Input_Line::Input_Line()
{
	is_active = false;

	body.setFillColor(SILVER);
	body.setOutlineColor(sf::Color::Black);

	body.setOutlineThickness(1);
	body.setSize(sf::Vector2f(300, 28));

	text_label.setCharacterSize(14);
	text_label.setFillColor(sf::Color::Black);
	text_label.setString("");

	caret.setFillColor(sf::Color::Black);
	caret.setSize(sf::Vector2f(1, 18));
	caret.setOrigin(sf::Vector2f(0, 9));
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
	if (is_active and show_caret) 
	{
		target.draw(caret, states);
	}
}

void Input_Line::update(Core* the_core)
{
	APPLICATION
		if (application.recent_mous_pressed_evnt.position.x != -1)
		{
			sf::Event::MouseButtonPressed& re_click = application.recent_mous_pressed_evnt;
			if (body.getGlobalBounds().contains(application.mapPixelToCoords(re_click.position)))
			{
				if (!is_active)
				{
					application.recent_keyboard_input = "";
					body.setFillColor(sf::Color::White);
				}
				is_active = true;

			}
			else 
			{
				body.setFillColor(SILVER);
				is_active = false; 
			}
		}

		if (is_active)
		{
			if ((application.two_recent_keys_pressed.first.scancode == sf::Keyboard::Scancode::Left or\
				 application.two_recent_keys_pressed.second.scancode == sf::Keyboard::Scancode::Left) and caret_pos != 0)
			{
				caret_pos -= 1;
				fake_caret_pos -= 1;
				
				if (application.two_recent_keys_pressed.first.scancode == sf::Keyboard::Scancode::LControl or \
					application.two_recent_keys_pressed.second.scancode == sf::Keyboard::Scancode::LControl)
				{
					std::cout << "CONTROL!\n";
				}

				Application::clear_key(application, sf::Keyboard::Scancode::Left);

			}
			if ((application.two_recent_keys_pressed.first.scancode == sf::Keyboard::Scancode::Right or \
				 application.two_recent_keys_pressed.second.scancode == sf::Keyboard::Scancode::Right) and caret_pos != inputed_text.length())
			{
				caret_pos += 1;
				fake_caret_pos += 1;

				Application::clear_key(application, sf::Keyboard::Scancode::Right);

			}

			if (application.recent_keyboard_input.length() != 0) 
			{
				add_sign_in_text(application.recent_keyboard_input);
				application.recent_keyboard_input = "";
			}
			if (application.two_recent_keys_pressed.first.scancode == sf::Keyboard::Scancode::Backspace or\
				application.two_recent_keys_pressed.second.scancode == sf::Keyboard::Scancode::Backspace)
			{
				if (inputed_text.length() != 0)
				{
					remove_sign_from_text();
				}

				Application::clear_key(application, sf::Keyboard::Scancode::Backspace);
			}
			//caret
			

	
		}

		text_label.setOrigin(sf::Vector2f(0, text_label.getCharacterSize() / 2));

	
	text_label.setPosition(body.getPosition());
	text_label.move(sf::Vector2f(5, body.getSize().y / 2));
}

