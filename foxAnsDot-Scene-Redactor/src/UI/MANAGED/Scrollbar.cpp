#include "Scrollbar.h"
#include "../../Application.h"

void Scrollbar::handle_buttons(Core* the_core, Scene_Component* button)
{
	if (button->name() == "UP")
	{
		--top_border;
		if (top_border < 0) { top_border = 0; return; }

	}
	else
	{
		++top_border;
		if (top_border + (showed_members_count - 1) > bar_members.size()) { --top_border; return; }
	}
	is_scrolled = true;
}

void Scrollbar::update(Core* the_core)
{
	APPLICATION

	slider_area.set_min_width(application.config.display_width / 75);
	slider_area.set_max_width(application.config.display_width / 75);

	to_up->set_min_heigth(application.config.display_width / 75);
	to_up->set_max_heigth(application.config.display_width / 75);

	to_down->set_min_heigth(application.config.display_width / 75);
	to_down->set_max_heigth(application.config.display_width / 75);

	if (is_scrolled)
	{
		for (int i = 0; i < bar_members.size(); ++i)
		{
			bar.remove_component(bar_members[i]);
		}
		is_scrolled = false;
	}

	for (int i = 0; i < bar_members.size(); ++i)
	{
		bar_members[i]->set_max_heigth(body.getSize().y / float(showed_members_count));
		//возможно потребуется ограниченеи и минимальной высоты
		if (i >= top_border and i < top_border + showed_members_count) 
		{
			bar.add_component(bar_members[i]);
			bar_members[i]->set_visble(true);
			bar_members[i]->set_updateble(true);
		}
		else
		{
			bar.remove_component(bar_members[i]);
			bar_members[i]->set_visble(false);
			bar_members[i]->set_updateble(false);
		}
	}
	
	
	Horizontal_Layout::update(the_core);

	to_up->update(the_core);
	to_down->update(the_core);

	slider_area.update(the_core);

	top_section.update(the_core);
	bottom_section.update(the_core);

	to_up->set_max_heigth(top_section.body.getSize().x);
	to_down->set_max_heigth(bottom_section.body.getSize().x);

	bar.update(the_core);

	
}

void Scrollbar::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body,states);
	target.draw(slider_area.body,states);
	target.draw(*to_up, states);
	target.draw(*to_down, states);
}

void Scrollbar::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	to_up->update_resource(resource);
	to_down->update_resource(resource);
}

Scrollbar::Scrollbar()
{
	//buttons 

	to_up = new Button("-", [this](Core* the_core, Scene_Component* button) {
		this->handle_buttons(the_core, button);
		});
	to_up->hovered_color = sf::Color::White;
	to_down = new Button("+", [this](Core* the_core, Scene_Component* button) {
		this->handle_buttons(the_core, button);
		});
	to_down->hovered_color = sf::Color::White;
	
	to_up->name() = "UP";
	to_down->name() = "DOWN";

	  to_up->body.setOutlineThickness(-2);
	  to_down->body.setOutlineThickness(-2);

	to_up->set_min_heigth(2560/75);
	to_down->set_min_heigth(2560/75);
	to_up->set_max_heigth(2560/75);
	to_down->set_max_heigth(2560/75);
	


	//body
	this->body.setFillColor(sf::Color(169, 169, 169));
	this->body.setOutlineColor(sf::Color::Black);
	this->body.setOutlineThickness(-3);

	this->set_align(Layout::align::rigth);

	//slider area
	slider_area.body.setFillColor(sf::Color(128, 128, 128));
	
	top_section.set_align(align::top);
	top_section.add_component(to_up);

	bottom_section.set_align(align::bottom);
	bottom_section.add_component(to_down);

	slider_area.set_max_width(2560/75);
	slider_area.set_min_width(2560/75);

	slider_area.add_component(&top_section);
	slider_area.add_component(&bottom_section);

	//widget
	this->add_component(&bar);
	this->add_component(&slider_area);
}

void Scrollbar::set_showed_elements_count(const int& arg)
{
	this->showed_members_count = arg;
}

void Scrollbar::add_element(UI_Component* new_component)
{
	bar_members.push_back(new_component);
}

void Scrollbar::remove_element(UI_Component* component)
{
	for (int i = 0; i < bar_members.size(); ++i)
	{
		if (bar_members[i] == component) { bar_members.erase(bar_members.begin() + i);  break; }
	}
}
