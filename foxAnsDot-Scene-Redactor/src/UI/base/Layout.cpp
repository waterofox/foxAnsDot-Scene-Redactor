#include "Layout.h"
#include "../../Application.h"

void Layout::update(Core* the_core)
{
	APPLICATION
	if (main_layout)
	{
			body.setPosition(application.mapPixelToCoords(sf::Vector2i(0,0)));
			sf::Vector2f newSize = sf::Vector2f(application.getSize());
			
			handle_new_size(newSize);
			body.setSize(newSize);
	}
	if (application.resized)
	{
		layout_members();
	}
}

void Layout::on_intersection(Core* the_core, Scene_Component* component) {}

sf::Drawable* Layout::as_drawable() { return this; }

void Layout::update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) {}

sf::FloatRect Layout::get_component_render_bounds()
{
	return body.getGlobalBounds();
}

sf::FloatRect Layout::get_component_bounds()
{
	return body.getGlobalBounds();
}

void Layout::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(body,states);
}

Layout::Layout()
{
	layout_align = align::left_top;
	this->get_type_of_resource() = Resource_Manager::resource_type::no_resource;

	body.setFillColor(sf::Color::Transparent);
}

void Layout::add_component(UI_Component* component_ptr)
{
	members[component_ptr] = 1;
	members_vector.push_back(component_ptr);
}

void Layout::add_component(UI_Component* component_ptr, const int& ratio)
{
	members[component_ptr] = ratio;
	members_vector.push_back(component_ptr);
}

void Layout::set_component_ratio(UI_Component* component_ptr, const int& ratio)
{
	auto component = members.find(component_ptr);
	if (component != members.end())
	{
		(*component).second = ratio;
	}
}

void Layout::remove_component(UI_Component* component)
{
	if(members.find(component) != members.end())
	{
		members.erase(component);
		for (int i = 0; i < this->members_vector.size(); ++i)
		{
			if (members_vector[i] == component) { members_vector.erase(members_vector.begin() + i); break; }
		}
	}
}

void Layout::make_main()
{
	main_layout = true;
}

void Layout::make_regular()
{
	main_layout = false;
}

void Layout::set_align(const Layout::align& arg)
{
	layout_align = arg;
}
