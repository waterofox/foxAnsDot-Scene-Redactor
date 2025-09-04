#pragma once
//SDK
#include <foxAndDot-SDK/Core.h>

#define APPLICATION 	Application* casted_application = static_cast<Application*>(the_core); \
						Application& application = (*casted_application);

class Button;
class Input_Line;

class Application : public Core
{

private:

	Input_Line* test_ptr = nullptr;

public:

	sf::Vector2f viewPosition = sf::Vector2f(0, 0);

	enum system_fonts
	{
		IBM_Plex_Mono_Medium,
		IBM_PLex_Mono_Regular,
		IBM_PLex_Mono_Bold
	};
	
	//--------------------------------

	std::queue<sf::Event::MouseButtonPressed> recent_clicks;

	bool remove_sign = false;
	std::string recent_keyboard_input = "";

	//--------------------------------
public:
	Application();
	~Application();
	
	
	std::queue<sf::Event::MouseButtonPressed>& get_recent_clicks();
};

