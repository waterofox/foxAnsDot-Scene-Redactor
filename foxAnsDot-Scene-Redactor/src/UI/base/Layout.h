#pragma once

#include <map>
#include "UI_Component.h"

class Layout : public UI_Component
{
public:
	enum align
	{
		left, rigth, top, bottom, left_top, left_bottom, rigth_top, rigth_bottom, center
	};
protected:
	//general properties
	bool main_layout = false;

	//align
	align layout_align = align::left;
	//members
	std::map<UI_Component*,int> members;
	std::vector<UI_Component*>  members_vector; //порядок компонентов;
	
	virtual void layout_members() = 0;
public:
	//sdk update
	void update(Core* the_core) override;
protected:
	//sdk
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

	virtual sf::FloatRect get_component_render_bounds() override;
	virtual sf::FloatRect get_component_bounds() override;

	//sfml
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Layout();
	virtual ~Layout() = default;

	void add_component(UI_Component* component_ptr);
	void add_component(UI_Component* component_ptr, const int& ratio);
	void set_component_ratio(UI_Component* component_ptr, const int& ratio);

	void remove_component(UI_Component* component);

	void make_main();
	void make_regular();
	void set_align(const Layout::align& arg);
};

