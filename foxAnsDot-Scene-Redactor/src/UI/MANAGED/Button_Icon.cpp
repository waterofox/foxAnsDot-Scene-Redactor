#include "Button_Icon.h"

void Button_Icon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Button::draw(target, states);
	target.draw(icon, states);
}

void Button_Icon::update(Core* the_core)
{

	icon.body.setSize(body.getSize());
	icon.body.setPosition(body.getPosition());

	icon.update(the_core);

	Button::update(the_core);
}

void Button_Icon::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	icon.update_resource(resource);
}

Button_Icon::Button_Icon() : Button()
{
	get_type_of_resource() = Resource_Manager::resource_type::texture;
}

Button_Icon::Button_Icon(Core::slot_type on_click) : Button("",on_click)
{
	get_type_of_resource() = Resource_Manager::resource_type::texture;
}

Button_Icon::~Button_Icon()
{
}
