#include "Label.h"

void Label::on_intersection(Core* the_core, Scene_Component* component){}

sf::Drawable* Label::as_drawable() { return this; }

void Label::update(Core* the_core) {}

void Label::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	this->setFont(*std::get<sf::Font*>(resource));
}

sf::FloatRect Label::get_component_render_bounds()
{
	return this->getGlobalBounds();
}

sf::FloatRect Label::get_component_bounds()
{
	return this->getGlobalBounds();
}

Label::Label() : sf::Text(defualt_font, "label")
{
	this->get_type_of_resource() = Resource_Manager::resource_type::font;
}

Label::Label(const std::string& text) : sf::Text(defualt_font, text)
{
	this->get_type_of_resource() = Resource_Manager::resource_type::font;
}

Label::~Label(){}
