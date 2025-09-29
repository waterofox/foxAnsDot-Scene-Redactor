#pragma once
//SDK
#include <foxAndDot-SDK/Core.h>

#define APPLICATION 	Application* casted_application = static_cast<Application*>(the_core); \
						Application& application = (*casted_application);

#define default_window_width 800
#define default_window_height 800

#define window_title "foxAndDot SDK - Scen Redactor"

class Button;
class Input_Line;
class Horizontal_Layout;


class Application : public Core
{

private:
	Button* button = nullptr;
	Button* button2 = nullptr;
	Horizontal_Layout* main_layout = nullptr;


public:

	static void clear_key(Application&,const sf::Keyboard::Scancode& scancode);

	//on start
	bool started = true;

	//position on scene
	sf::Vector2f viewPosition = sf::Vector2f(0, 0);

//---------------------------------------------------------------
	//resources
	enum system_fonts
	{
		MonaspaceNeon_Medium
	};
private:
	void init_resources();
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
public:
	Application();
	~Application();
};

