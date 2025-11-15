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

//system colors
#define       BASE_COLOR sf::Color(216 ,216,216 )
#define DARK_DARK_BASE_COLOR sf::Color(136 ,136,136)
#define  DARK_BASE_COLOR sf::Color(170 ,170, 170 )
#define       LINE_COLOR sf::Color(33,37,255)
#define LIGHT_LINE_COLOR sf::Color(60,63,255)
#define  DARK_LINE_COLOR sf::Color(0,4,228)

class Vertical_Layout;
class Horizontal_Layout;
class Scrollbar;
class Button;
class Button_Icon;
class Com_Bar_Element;
class Icon;


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
		scene_component_icon,
		open_folder_icon,
		closed_folder_icon,
		save_icon,
		save_all_icon,
		ctrlZ_icon,
		ctrlY_icon,
		cursor_icon,
		move_icon,
		zoom_icon,
		test,
	};
private:
	void init_resources();

//---------------------------------------------------------------
	//INTERFACE COMPONENTS & MODELS

	//layouts
	Vertical_Layout  *   application_layout  = nullptr;
	Horizontal_Layout*   command_menu_layout = nullptr;
	Horizontal_Layout* tools_menu_layout     = nullptr;
	Horizontal_Layout*   work_area_layout    = nullptr;
	Vertical_Layout*   scene_area_layout   = nullptr;
	Vertical_Layout  *   info_area_layout    = nullptr;

	//ui
	Scrollbar* components_bar = nullptr;
	//std::vector<Icon>* tools_buttons = nullptr;
//	std::map<std::string, Com_Bar_Element*>* elements_in_scrollbar;


	Button* command_menu_buttons[4];
	Button_Icon* tools_menu_buttons[8];
	
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

