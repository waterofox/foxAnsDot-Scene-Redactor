#include "Application.h"

//UI
#include "UI/Button.h"

void process_event_function(Core* the_core);
void test_button_slot(Core* the_core,Scene_Component* component);

Application::Application()
{
	//window
	this->set_process_events_function(process_event_function);

	//view
	sf::View& camera = this->get_camera();

	camera.setCenter(sf::Vector2f(0, 0));
	this->set_camera_mod(Core::camera_settings::static_camera);

	//defualt resources
	resource_manager.add_font("src\\resources\\fonts\\IBM Plex Mono\\IBMPlexMono-Medium.ttf", IBM_Plex_Mono_Medium);
	resource_manager.font(IBM_Plex_Mono_Medium).setSmooth(false);

	resource_manager.add_font("src\\resources\\fonts\\IBM Plex Mono\\IBMPlexMono-Regular.ttf", IBM_PLex_Mono_Regular);
	resource_manager.font(IBM_PLex_Mono_Regular).setSmooth(false);

	resource_manager.add_font("src\\resources\\fonts\\IBM Plex Mono\\IBMPlexMono-Bold.ttf", IBM_PLex_Mono_Bold);
	resource_manager.font(IBM_PLex_Mono_Bold).setSmooth(false);

	//scene

	test.get_resource() = IBM_PLex_Mono_Bold;
	test.get_type_of_resource() = Resource_Manager::resource_type::font;

	Core::lay_type lay1; lay1["test"] = &test;

	scene.push_back(lay1);

	this->run(800, 800, "Fox&Dot Scene Redactor", sf::State::Windowed);
	

}

Application::~Application()
{
}

std::queue<sf::Event::MouseButtonPressed>& Application::get_recent_clicks() { return this->recent_clicks; }

void process_event_function(Core* the_core)
{

	APPLICATION

	const auto onClose = [&application](const sf::Event::Closed&) {
		application.close();
	};
	const auto onClick = [&application](const sf::Event::MouseButtonPressed& evnt) {

		if (!application.recent_clicks.empty()) { application.recent_clicks.pop(); }
		
		application.get_recent_clicks().push(evnt);
	};
	const auto onResize = [&application](const sf::Event::Resized evnt) {
		sf::View& camera = application.get_camera();

		float aspectRatio = float(evnt.size.x) / float(evnt.size.y);

		camera.setSize(sf::Vector2f(800,800 / aspectRatio));
	};
	const auto onKeyboardInput = [&application](const sf::Event::TextEntered evnt) {
		application.recent_keyboard_input = evnt.unicode;
	};
	const auto onKeyPressed = [&application](const sf::Event::KeyPressed evnt) {
		switch (evnt.scancode)
		{
		case sf::Keyboard::Scancode::Backspace: {
			application.remove_sign = true; 
			if (application.recent_keyboard_input.length() != 0) 
			{
				application.recent_keyboard_input = "";
				application.remove_sign = false;
			}
		}
		default:
			break;
		}
	};

	application.handleEvents(onClose, onClick, onResize, onKeyboardInput,onKeyPressed);
}
void test_button_slot(Core* the_core, Scene_Component* component)
{
	std::cout << "Button!\n";
}