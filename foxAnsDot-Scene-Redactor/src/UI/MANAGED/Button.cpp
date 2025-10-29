#include "Button.h"
#include "../../Application.h";


void Button::on_intersection(Core* the_core, Scene_Component* component) {}

sf::Drawable* Button::as_drawable()
{
	return this;
}

void Button::update(Core* the_core)
{

	//centering label
	//-----------------------------------------------------------------------------------------

	//text area position
	text_area.setSize(sf::Vector2f(button_label.label->getGlobalBounds().size.x, button_label.label->getCharacterSize()));
	text_area.setOrigin(sf::Vector2f(0, text_area.getSize().y / 2));
	text_area.setPosition(body.getPosition());
	text_area.move(sf::Vector2f((body.getSize().x - text_area.getSize().x) / 2, body.getSize().y / 2));
	//text position
	button_label.body.setPosition(text_area.getPosition());
	button_label.body.move(sf::Vector2f(0, text_area.getSize().y / -2));

	button_label.update(the_core);



	//coloring
	//------------------------------------------------------------------------------------------

	sf::Vector2f cursor = the_core->mapPixelToCoords(sf::Mouse::getPosition(*the_core));
	if (body.getGlobalBounds().contains(cursor))
	{
		if (body.getFillColor() != active_color) { body.setFillColor(hovered_color); }
	}
	else { body.setFillColor(base_color); }

	//click handling
	//------------------------------------------------------------------------------------------

	APPLICATION
		if (application.recent_mous_pressed_evnt.position.x == -1) { return; }
		sf::Event::MouseButtonPressed& recent_click = application.recent_mous_pressed_evnt;
	if (body.getGlobalBounds().contains(application.mapPixelToCoords(recent_click.position)))
	{
		if (on_click != nullptr) { on_click(the_core, this); }
		body.setFillColor(active_color);
	}

	//------------------------------------------------------------------------------------------

}

void Button::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	button_label.update_resource(resource);
}

sf::FloatRect Button::get_component_render_bounds()
{
	return body.getGlobalBounds();
}

sf::FloatRect Button::get_component_bounds()
{
	return body.getGlobalBounds();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body,states);
	target.draw(button_label,states);
}

Button::Button()
{
	//bounds
	body.setSize(sf::Vector2f(100, 50));

	//color
	body.setFillColor(sf::Color(211, 211, 211, 255));
	body.setOutlineColor(sf::Color::Black);
	body.setOutlineThickness(5);

	//label
	button_label.label->setFillColor(sf::Color::Black);
	button_label.label->setCharacterSize(18);

}

Button::Button(const std::string& button_text, Core::slot_type on_click) : Button()
{
	//resource
	type_of_resource = Resource_Manager::resource_type::font; //for label
	button_label.label->setString(button_text);

	this->on_click = on_click;
}

Button::~Button() {}

Label& Button::get_label()
{
	return button_label;
}
