#include <foxAndDot-SDK/Core.h>

class Label : public Scene_Component, public sf::Text
{

	static inline sf::Font defualt_font{}; //empty
protected:
	void on_intersection(Core* the_core, Scene_Component* component) override;
	sf::Drawable* as_drawable() override;

	void update(Core* the_core) override;

public:
	void update_resource(const std::variant<sf::Texture*, sf::Font*>& resource) override;

	sf::FloatRect get_component_render_bounds() override;
	sf::FloatRect get_component_bounds() override;

	
public:
	Label();
	Label(const std::string& text);
	~Label();

};