#include "Button.h"
#include "../Application.h";

#define LIGHT_GREY sf::Color(211, 211, 211, 255)
#define  DARK_GREY sf::Color(169, 169, 169, 255)
#define  GAINSBORO sf::Color(220, 220, 220, 255)

void Button::on_intersection(Core* the_core, Scene_Component* component) {}

sf::Drawable* Button::as_drawable()
{
	return this;
}

void Button::update(Core* the_core)
{
	//centering label
	//------------------------------------------------------------------------------------------

	sf::Vector2f label_size = button_label.getGlobalBounds().size;
	button_label.setOrigin(label_size / 2.f);

	button_label.setPosition(body.getGlobalBounds().getCenter());
	button_label.move(sf::Vector2f(0, -label_size.y / 4.f));

	//coloring
	//------------------------------------------------------------------------------------------

	sf::Vector2f cursor = the_core->mapPixelToCoords(sf::Mouse::getPosition(*the_core));
	if (body.getGlobalBounds().contains(cursor))
	{
		if (body.getFillColor() != DARK_GREY) { body.setFillColor(sf::Color::White); }
	}
	else { body.setFillColor(LIGHT_GREY); }

	//click handling
	//------------------------------------------------------------------------------------------

	APPLICATION
		if (application.recent_clicks.empty()) { return; }
		sf::Event::MouseButtonPressed& recent_click = application.recent_clicks.front();
	if (body.getGlobalBounds().contains(application.mapPixelToCoords(recent_click.position)))
	{
		if (on_click != nullptr) { on_click(the_core, this); }
		body.setFillColor(DARK_GREY);
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
	button_label.setFillColor(sf::Color::Black);
	button_label.setCharacterSize(18);

}

Button::Button(const std::string& button_text, Core::slot_type on_click) : Button()
{
	//resource
	type_of_resource = Resource_Manager::resource_type::font; //for label
	button_label.setString(button_text);

	this->on_click = on_click;
}

Button::~Button() {}

Label& Button::get_label()
{
	return button_label;
	//Визулка хуйню творит
}
