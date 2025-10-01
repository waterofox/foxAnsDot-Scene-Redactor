#pragma once
#include "base/UI_Component.h"
#include "Label.h"

class Application;

class Button : public UI_Component
{
private:
	bool is_active = false;

	Label button_label;

	Core::slot_type on_click = nullptr;

protected:
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;
	void update(Core* the_core) override;
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

public:
	sf::FloatRect get_component_render_bounds()  override;
	sf::FloatRect get_component_bounds()		 override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Button();
	Button(const std::string& button_text, Core::slot_type on_click);
	
	~Button();

	Label& get_label();

};
