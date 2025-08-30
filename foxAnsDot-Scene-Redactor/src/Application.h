
//SDK
#include <foxAndDot-SDK/Core.h>

//UI
#include "UI/Label.h"

#define APPLICATION 	Application* casted_application = static_cast<Application*>(the_core); \
						Application& application = (*casted_application);

class Application : public Core
{

private:

	Label testLabel;
public:

	sf::Vector2f viewPosition = sf::Vector2f(0, 0);

	enum system_fonts
	{
		IBM_Plex_Mono_Medium
	};
	
	//--------------------------------

	std::queue<sf::Event::MouseButtonPressed> recent_clicks;

	//--------------------------------

public:
	Application();
	~Application();
	
	std::queue<sf::Event::MouseButtonPressed>& get_recent_clicks();
};

