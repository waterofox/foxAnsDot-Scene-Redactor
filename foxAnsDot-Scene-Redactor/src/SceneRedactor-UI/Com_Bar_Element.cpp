#include "Com_Bar_Element.h"
#include "../Application.h"

void Com_Bar_Element::handle_click(Core* the_core, Scene_Component* component)
{

}

void Com_Bar_Element::update(Core* the_core)
{
	body_button->body.setSize(body.getSize());
	body_button->body.setPosition(body.getPosition());

	el_icon.update(the_core);
	el_icon.set_max_width(body.getSize().y);

	name_of_component.update(the_core);
	body_button->update(the_core);

	Horizontal_Layout::update(the_core);

}

Com_Bar_Element::Com_Bar_Element()
{
	this->set_align(left);

	this->add_component(&el_icon);
	this->add_component(&name_of_component);


	body_button = new Button("", [this](Core* the_core, Scene_Component* button) {
		this->handle_click(the_core, button);
		});

	body_button->base_color = sf::Color(26, 26, 26);
	body_button->hovered_color = sf::Color(41, 41, 41);
	body_button->active_color = sf::Color(59,59,59);

	body_button->body.setOutlineThickness(0);

	name_of_component.active_color = sf::Color::Transparent;
	name_of_component.base_color = sf::Color::Transparent;
	name_of_component.hovered_color = sf::Color::Transparent;
	name_of_component.body.setOutlineThickness(0);
	name_of_component.text_label.label->setFillColor(sf::Color::White);
	name_of_component.caret.setFillColor(sf::Color::White);
}

void Com_Bar_Element::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*body_button, states);
	target.draw(el_icon, states);
	target.draw(name_of_component,states);
}

void Com_Bar_Element::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	std::variant<sf::Texture*, sf::Font*> second_resource = &Application::resource_manager.font(Application::system_fonts::MonaspaceNeon_Medium);
	body_button->update_resource(second_resource);
	el_icon.update_resource(resource);
	name_of_component.update_resource(second_resource);
}

Com_Bar_Element::~Com_Bar_Element()
{
	delete body_button;
	body_button = nullptr;

}
