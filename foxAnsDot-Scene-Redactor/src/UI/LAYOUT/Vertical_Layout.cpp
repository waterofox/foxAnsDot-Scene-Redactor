#include "Vertical_Layout.h"

void Vertical_Layout::layout_members()
{
	int parts = 0;
	float one_part = 0;
	sf::Vector2f new_component_size = sf::Vector2f(0, 0);
	float full_members_heigth = 0;

	bool resize_flag = false;

	vertical_free_space = body.getSize().y;

	for (int i = 0; i < members_vector.size(); ++i)
	{
		UI_Component*& component = members_vector[i];
		parts += members[component];
	}

	one_part = body.getSize().y / float(parts);
	for (int i = 0; i < members_vector.size(); ++i)
	{
		if (resize_flag)
		{
			parts = 0;

			for (int j = i; j < members_vector.size(); ++j)
			{
				UI_Component*& component = members_vector[j];
				parts += members[component];
			}
			one_part = vertical_free_space / float(parts);

			resize_flag = false;
		}


		UI_Component*& component = members_vector[i];

		new_component_size.x = body.getSize().x;
		new_component_size.y = one_part * members[component];

		sf::Vector2f valid_size = new_component_size;
		component->handle_new_size(valid_size);
		component->body.setSize(valid_size);

		if (valid_size.y > new_component_size.y)
		{
			resize_flag = true;

		}
		else if (valid_size.y < new_component_size.y)
		{
			resize_flag = true;
		}

		full_members_heigth += new_component_size.y;
		vertical_free_space -= valid_size.y;
	}

	switch (this->layout_align)
	{
	case Layout::left:
	{
		sf::Vector2f last_pos = body.getPosition();
		for (int i = 0; i < members_vector.size(); ++i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			last_pos.y += component->body.getSize().y;
		}
	} break;
	case Layout::rigth:
	{
		sf::Vector2f last_pos = body.getPosition();
		last_pos.x += body.getSize().x;

		for (int i = 0; i < members_vector.size(); ++i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			component->body.move(sf::Vector2f(-(component->body.getSize().x), 0));

			last_pos.y += component->body.getSize().y;
		}
	}break;
	case Layout::center:
	{
		sf::Vector2f last_pos = body.getGlobalBounds().getCenter();
		last_pos.y = body.getPosition().y;

		for (int i = 0; i < members_vector.size(); ++i)
		{
			UI_Component*& component = members_vector[i];

			component->body.setPosition(last_pos);
			component->body.move(sf::Vector2f(-(component->body.getSize().x / 2), 0));
			
			last_pos.y += component->body.getSize().y;
		}
	} break;
	default:
		break;
	}
}

Vertical_Layout::Vertical_Layout() : Layout()
{
	layout_align = Layout::left;
}

Vertical_Layout::~Vertical_Layout()
{
}
