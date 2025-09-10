#include "Application.h"

//UI
#include "UI/Button.h"
#include "UI/Input_Line.h"

void process_event_function(Core* the_core);
void confirm_input_slot(Core* the_core,Scene_Component* component);

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

	resource_manager.add_font("src\\resources\\fonts\\IBM Plex Mono\\IBMPlexMono-Regular.ttf", IBM_PLex_Mono_Regular);

	resource_manager.add_font("src\\resources\\fonts\\IBM Plex Mono\\IBMPlexMono-Bold.ttf", IBM_PLex_Mono_Bold);

	resource_manager.add_font("src\\resources\\fonts\\Monaspace Neon\\MonaspaceNeon-Medium.otf", MonaspaceNeon_Medium);
	resource_manager.font(MonaspaceNeon_Medium).setSmooth(false);
	//scene
	
	input = new Input_Line();
	input->get_type_of_resource() = Resource_Manager::resource_type::font;
	input->get_resource() = MonaspaceNeon_Medium;

	input->body.setPosition(sf::Vector2f(-300, 0));
	input->body.setSize(sf::Vector2f(300, 50))
		;
	confirm_input = new Button("confirm", confirm_input_slot);

	confirm_input->get_type_of_resource() = Resource_Manager::resource_type::font;
	confirm_input->get_resource() = MonaspaceNeon_Medium;

	Core::lay_type lay0; lay0["input"] = input; lay0["button"] = confirm_input;
	scene.push_back(lay0);

	this->run(800, 800, "Fox&Dot Scene Redactor", sf::State::Windowed);
	

}

Application::~Application()
{
}

std::queue<sf::Event::MouseButtonPressed>& Application::get_recent_clicks() { return this->recent_clicks; }

void process_event_function(Core* the_core)
{

	APPLICATION

		if (!application.recent_clicks.empty())
		{
			application.recent_clicks.pop();
		}
		if (application.started)
		{
			application.started = false;
			sf::View& camera = application.get_camera();

			float aspectRatio = float(800) / float(800);

			camera.setSize(sf::Vector2f(800, 800 / aspectRatio));
		}

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
		if (evnt.unicode != '\b') 
		{
			application.recent_keyboard_input = evnt.unicode;
		}
	};
	const auto onKeyPressed = [&application](const sf::Event::KeyPressed evnt) {
		
		application.recent_key_pressed = evnt;

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

	application.handleEvents(onClose, onClick, onResize, onKeyboardInput, onKeyPressed);
}
void confirm_input_slot(Core* the_core, Scene_Component* component)
{
	APPLICATION
		Input_Line* line = static_cast<Input_Line*>(application.get_component("input"));
	std::cout << line->get_text() << '\n';
	line->clear();
}
