#pragma once
#include <fstream>
//SDK
#include <foxAndDot-SDK/Core.h>


#define config_path "config/config.txt"

#define APPLICATION 	Application* casted_application = static_cast<Application*>(the_core); \
						Application& application = (*casted_application);

#define default_window_width 800
#define default_window_height 800

#define window_title "foxAndDot SDK - Scen Redactor"

class Vertical_Layout;
class Horizontal_Layout;
class Scrollbar;
class Button;
class Com_Bar_Element;


class Application : public Core
{
	struct parsed_config
	{
		unsigned int display_heigth;
		unsigned int display_width;
	};
public:

	parsed_config config;

	static void clear_key(Application&,const sf::Keyboard::Scancode& scancode);

	//on start
	bool started = true;

	//resized

	bool resized = true;

	//position on scene
	sf::Vector2f viewPosition = sf::Vector2f(0, 0);

//---------------------------------------------------------------
	//resources
	enum system_fonts
	{
		MonaspaceNeon_Medium
	};
	enum system_icons
	{
		scene_component_icon
	};
private:
	void init_resources();

//---------------------------------------------------------------
	//INTERFACE COMPONENTS & MODELS

	//layouts
	Vertical_Layout  *   application_layout  = nullptr;
	Horizontal_Layout*   command_menu_layout = nullptr;
	Horizontal_Layout*   work_area_layout    = nullptr;
	Horizontal_Layout*   scene_area_layout   = nullptr;
	Vertical_Layout  *   info_area_layout    = nullptr;

	//ui
	Scrollbar* components_bar = nullptr;
//	std::map<std::string, Com_Bar_Element*>* elements_in_scrollbar;

	std::vector<Button*>* command_menu_buttons;

	
	void init_interface();
	
public:
//---------------------------------------------------------------
	//mous & keyboard handling
	sf::Event::MouseButtonPressed recent_mous_pressed_evnt;
	sf::Event::MouseButtonReleased recent_mous_released_evnt;

	std::string recent_keyboard_input;
	std::pair<sf::Event::KeyPressed, sf::Event::KeyPressed> two_recent_keys_pressed;   // for using combinations of keys. Like a (Ctrl + Left) for example
	std::pair<sf::Event::KeyReleased, sf::Event::KeyReleased> two_recent_keys_released;//
private:
	void init_handling_fields();
public:
	void clear_pressed_fields();
//---------------------------------------------------------------
private:
	void run(const unsigned int& window_width, const unsigned int& window_height, const std::string& title, const sf::State& state);
	void parse_config();
public:
	Application();
	~Application();
};

