#include "Icon.h"
Icon::Icon()
{
	body.setFillColor(sf::Color::Transparent);
	icon = new sf::Sprite(icons_texture);
	this->get_type_of_resource() = Resource_Manager::resource_type::texture;
}
Icon::~Icon()
{
	delete icon;
	icon = nullptr;
}

void Icon::on_intersection(Core* the_core, Scene_Component* component){}

sf::Drawable* Icon::as_drawable()
{
	return this;
}

void Icon::update(Core* the_core)
{
	icon->setPosition(body.getPosition());

	icon->setTextureRect(sf::IntRect(sf::Vector2i(0,0),sf::Vector2i(32,32)));
	double ratio_x = body.getSize().x / icon->getTexture().getSize().x;
	double ratio_y = body.getSize().y / icon->getTexture().getSize().y;

	icon->setScale(sf::Vector2f(ratio_x, ratio_y));
}

void Icon::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource)
{
	icon->setTexture(*std::get<sf::Texture*>(resource));
}

sf::FloatRect Icon::get_component_render_bounds()
{
	return body.getGlobalBounds();
}

sf::FloatRect Icon::get_component_bounds()
{
	return body.getGlobalBounds();
}

void Icon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body);
	target.draw(*icon,states);
}
