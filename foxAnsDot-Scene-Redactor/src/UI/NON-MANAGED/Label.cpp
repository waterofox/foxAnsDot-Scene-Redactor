#include "Label.h"

void Label::on_intersection(Core* the_core, Scene_Component* component){}

sf::Drawable* Label::as_drawable() { return this; }

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body);
	target.draw(*label,states);
}

void Label::update(Core* the_core) 
{
	label->setPosition(body.getPosition());
	body.setSize(label->getLocalBounds().size);
}

void Label::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	label->setFont(*std::get<sf::Font*>(resource));
}

sf::FloatRect Label::get_component_render_bounds()
{
	return body.getGlobalBounds();
}

sf::FloatRect Label::get_component_bounds()
{
	return body.getGlobalBounds();
}

Label::Label() //: sf::Text(defualt_font, "label")
{
	body.setFillColor(sf::Color::Transparent);
	label = new sf::Text(defualt_font, "label");
	this->get_type_of_resource() = Resource_Manager::resource_type::font;
}

Label::Label(const std::string& text) //: sf::Text(defualt_font, text)
{
	body.setFillColor(sf::Color::Transparent);
	label = new sf::Text(defualt_font, text);
	this->get_type_of_resource() = Resource_Manager::resource_type::font;
}

Label::~Label() {
	if (label != nullptr) { delete label; } 
}
