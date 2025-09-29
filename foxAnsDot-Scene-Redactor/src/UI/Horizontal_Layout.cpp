#include "Horizontal_Layout.h"

void Horizontal_Layout::layout_members()
{
	int parts = 0;
	float one_part = 0;
	sf::Vector2f new_component_size = sf::Vector2f(0,0);
	float full_members_width = 0;

	for (int i = 0; i < members_vector.size(); ++i)
	{
		UI_Component*& component = members_vector[i];
		parts += members[component];
	}
	one_part = body.getSize().x / float(parts);
	for (int i = 0; i < members_vector.size(); ++i)
	{
		UI_Component*& component = members_vector[i];

		new_component_size.y = body.getSize().y;
		new_component_size.x = one_part * members[component];

		component->handle_new_size(new_component_size);
		component->body.setSize(new_component_size);

		full_members_width += new_component_size.x;
	}

	switch (this->layout_align)
	{
	case Layout::left_top: 
	{
		sf::Vector2f last_pos = sf::Vector2f(body.getPosition());
		for (int i = 0; i < members_vector.size(); ++i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			last_pos.x += component->body.getSize().x;
		}
	} break;
	case Layout::rigth_top: 
	{
		sf::Vector2f last_pos = sf::Vector2f(body.getPosition().x + body.getSize().x,body.getPosition().y);
		for (int  i  = members_vector.size()-1; i >= 0; --i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			component->body.move(sf::Vector2f(-(component->body.getSize().x), 0));

			last_pos.x -= component->body.getSize().x;
		}
	}break;
	case Layout::top_center: 
	{
		sf::Vector2f last_pos = sf::Vector2f(body.getGlobalBounds().getCenter());
		last_pos.y = body.getPosition().y;
		last_pos.x -= full_members_width / 2;

		for (int i = 0; i < members_vector.size(); ++i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);

			last_pos.x += component->body.getSize().x;
		}
	} break;
	case Layout::left: 
	{
		sf::Vector2f last_pos = sf::Vector2f(body.getPosition().x, body.getGlobalBounds().getCenter().y);
		for (int i = 0; i < members_vector.size(); ++i)
		{
			UI_Component*& component = members_vector[i];
			
			component->body.setPosition(last_pos);
			component->body.move(sf::Vector2f(0, -(component->body.getSize().y / 2)));

			last_pos.x += component->body.getSize().x;
		}
	} break;
	case Layout::rigth: 
	{
		sf::Vector2f last_pos = sf::Vector2f(body.getPosition().x + body.getSize().x, body.getGlobalBounds().getCenter().y);

		for (int i = members_vector.size() - 1; i >= 0; --i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			component->body.move(sf::Vector2f(-(component->body.getSize().x), -(component->body.getSize().y / 2)));

			last_pos.x -= component->body.getSize().x;
		}
	} break;
	case Layout::center: 
	{
		sf::Vector2f last_pos = sf::Vector2f(body.getGlobalBounds().getCenter());
		last_pos.x -= full_members_width / 2;

		for (int i = 0; i < members_vector.size(); ++i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			component->body.move(sf::Vector2f(0, -(component->body.getSize().y / 2)));

			last_pos.x += component->body.getSize().x;
		}

	} break;
	case Layout::left_bottom:
	{
		sf::Vector2f last_pos = sf::Vector2f(body.getPosition());
		last_pos.y += body.getSize().y;

		for (int i = 0; i < members_vector.size(); ++i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			component->body.move(sf::Vector2f(0, -(component->body.getSize().y)));

			last_pos.x += component->body.getSize().x;
		}

		
	} break;
	case Layout::rigth_bottom: 
	{
		sf::Vector2f last_pos = sf::Vector2f(body.getPosition().x + body.getSize().x, body.getPosition().y + body.getSize().x);
		for (int i = members_vector.size() - 1; i >= 0; --i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			component->body.move(sf::Vector2f(-(component->body.getSize().x), -(component->body.getSize().y)));

			last_pos.x -= component->body.getSize().x;
		}
	} break;
	case Layout::bottom_center: 
	{
		sf::Vector2f last_pos = sf::Vector2f(body.getGlobalBounds().getCenter());
		last_pos.y = body.getPosition().y;
		last_pos.x -= full_members_width / 2;

		for (int i = 0; i < members_vector.size(); ++i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			component->body.move(sf::Vector2f(0, -(component->body.getSize().x)));

			last_pos.x += component->body.getSize().x;
		}
	} break;
	default:
		break;
	}
}

Horizontal_Layout::Horizontal_Layout()
{
	body.setFillColor(sf::Color::Transparent);
	body.setOutlineColor(sf::Color::Green);
	body.setOutlineThickness(5);
}

Horizontal_Layout::~Horizontal_Layout()
{
}
