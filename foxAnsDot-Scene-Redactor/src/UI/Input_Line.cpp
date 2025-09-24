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

const bool& Input_Line::is_active_now()
{
	return is_active;
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

	text_area.setOutlineColor(sf::Color::Blue);
	text_area.setFillColor(sf::Color::Transparent);
	text_area.setOutlineThickness(2);

	caret.setFillColor(sf::Color::Black);
}
Input_Line::~Input_Line() {}

void Input_Line::handle_input_event(Core*& the_core)
{
	APPLICATION

	switch (recent_input_event)
	{
	case input_event::unknown: { return; } break;
	case input_event::push_back: {

		inputed_text.push_back(application.recent_keyboard_input[0]);
		
		++rcp;
		++vcp;
		++text_border.y;

		text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));
		while (text_label.getGlobalBounds().size.x >= text_area.getSize().x)
		{
			--vcp;
			++text_border.x;
			text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));
		}

		//clear data
		application.recent_keyboard_input = "";

	}break;
	case input_event::insert:{

		inputed_text.insert(inputed_text.begin() + rcp, application.recent_keyboard_input[0]);

		++rcp;
		++vcp;
		++text_border.y;

		text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));

		while (text_label.getGlobalBounds().size.x >= text_area.getSize().x)
		{

			if (vcp == text_label.getString().getSize() - 1)
			{
				--vcp;
				++text_border.x;
			}
			else
			{
				--text_border.y;
			}
			text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));
		}

		//clear data
		application.recent_keyboard_input = "";

	}break;
	case input_event::pop_back: {
	
		if (rcp > 0)
		{
			--rcp;
			inputed_text.pop_back();
			--text_border.y;

			if (vcp == 1 and inputed_text.length() != 0) 
			{
				--text_border.x;
			}
			else
			{
				--vcp;
			}
			text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));
		}

		//clear data
		Application::clear_key(application, sf::Keyboard::Scancode::Backspace);

	} break;
	case input_event::erase: {
		if (rcp >= 1)
		{

			if (text_border.y < (inputed_text.size() - 1))
			{
				inputed_text.erase(inputed_text.begin() + (rcp - 1));

				if (vcp == 1)
				{
					if (rcp == 1)
					{
						--vcp;
						--rcp;
					}
					else
					{
						--rcp;
						--text_border.x;
						--text_border.y;
					}
				}
				else
				{
					--vcp;
					--rcp;
				}
			}
			else
			{
				inputed_text.erase(inputed_text.begin() + (rcp - 1));

				if (vcp == 1)
				{
					if (rcp == 1)
					{
						--vcp;
						--rcp;
						--text_border.y;
					}
					else
					{
						--rcp;
						--text_border.x;
					}

				}
				else
				{
					--vcp;
					--rcp;
					--text_border.y;
				}
			}
		}

		text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));

		//clear data
		Application::clear_key(application, sf::Keyboard::Scancode::Backspace);
	
	}break;
	case input_event::move_rigth: {
		
		if (rcp < inputed_text.length())
		{
			++rcp;
			++vcp;
			if (vcp >= text_label.getString().getSize() and rcp != inputed_text.length())
			{
				++text_border.x;
				++text_border.y;
				--vcp;
				text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));
				while (text_label.getGlobalBounds().size.x >= text_area.getSize().x)
				{
					++text_border.x;
					--vcp;
					text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));
				}
			}
		}
		//clear data
		Application::clear_key(application, sf::Keyboard::Scancode::Right);

	} break;
	case input_event::move_left:{

		if (rcp > 0)
		{
			--rcp;
			--vcp;

			if (vcp <= 0 and rcp != 0) 
			{
				--text_border.x;
				++vcp;
				text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));

				while (text_label.getGlobalBounds().size.x >= text_area.getSize().x)
				{
					--text_border.y;
					text_label.setString(inputed_text.substr(text_border.x, text_border.y - text_border.x + 1));
				}
			}
		}
		Application::clear_key(application, sf::Keyboard::Scancode::Left);

	} break;
	default:
		break;
	}
}

void Input_Line::on_intersection(Core* the_core, Scene_Component* component) {}

void Input_Line::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) 
{
	text_label.update_resource(resource);
}



void Input_Line::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body,states);
	target.draw(text_area, states);
	target.draw(text_label, states);

	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(2);

	shape.setSize(text_label.getGlobalBounds().size);
	shape.setPosition(text_label.getGlobalBounds().position);

	target.draw(shape, states);
	target.draw(caret);
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
	
	//text area position
	text_area.setSize(sf::Vector2f(body.getSize().x - 10, text_label.getCharacterSize()));
	text_area.setOrigin(sf::Vector2f(0, text_area.getSize().y / 2));
	text_area.setPosition(body.getPosition());
	text_area.move(sf::Vector2f((body.getSize().x - text_area.getSize().x) / 2, body.getSize().y / 2));
	//text position
	text_label.setPosition(text_area.getPosition());
	text_label.move(sf::Vector2f(0, text_area.getSize().y / -2));
	//caret positon
	caret.setSize(sf::Vector2f(2, text_area.getSize().y));
	caret.setOrigin(sf::Vector2f(0, caret.getSize().y / 2));
	caret.setPosition(text_label.findCharacterPos(vcp));
	caret.move(sf::Vector2f(0, text_area.getSize().y / 2));

		
		if (is_active)
		{
			//keyboard input
			if (application.recent_keyboard_input.length() != 0)
			{
				if (rcp == inputed_text.length()) { recent_input_event = push_back; }
				else { recent_input_event = insert; }
			}
			//remove sign
			else if (application.two_recent_keys_pressed.first.scancode  == sf::Keyboard::Scancode::Backspace or \
					 application.two_recent_keys_pressed.second.scancode == sf::Keyboard::Scancode::Backspace)
			{
				if (rcp == inputed_text.length()) { recent_input_event = pop_back; }
				else { recent_input_event = erase; }
			}
			//move right
			else if (application.two_recent_keys_pressed.first.scancode  == sf::Keyboard::Scancode::Right or \
					 application.two_recent_keys_pressed.second.scancode == sf::Keyboard::Scancode::Right)
			{
				recent_input_event = move_rigth;
			}
			//move left
			else if (application.two_recent_keys_pressed.first.scancode  == sf::Keyboard::Scancode::Left or \
					 application.two_recent_keys_pressed.second.scancode == sf::Keyboard::Scancode::Left)
			{
				recent_input_event = move_left;
			}
			
			handle_input_event(the_core);

		}


		recent_input_event = unknown;
}

