#include "Scrollbar.h"

void Scrollbar::handle_buttons(Core* the_core, Scene_Component* button)
{
	std::cout << "some code\n";
}

void Scrollbar::update(Core* the_core)
{

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
	to_down = new Button("+", [this](Core* the_core, Scene_Component* button) {
		this->handle_buttons(the_core, button);
		});
	
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

void Scrollbar::set_ratio(const sf::Vector2i& new_ratio)
{
}

void Scrollbar::add_element(const Layout*& new_component)
{
}

void Scrollbar::remove_element(const Layout*& component)
{
}
