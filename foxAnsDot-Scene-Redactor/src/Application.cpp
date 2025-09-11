#include "Application.h"

//UI
#include "UI/Button.h"
#include "UI/Input_Line.h"

void process_event_function(Core* the_core);

void Application::init_resources()
{
	resource_manager.add_font("src\\resources\\fonts\\Monaspace Neon\\MonaspaceNeon-Medium.otf", MonaspaceNeon_Medium);
	resource_manager.font(MonaspaceNeon_Medium).setSmooth(false);
}
void Application::init_handling_fields()
{
	//mous
	recent_mous_pressed_evnt.button = sf::Mouse::Button::Left;
	recent_mous_pressed_evnt.position = sf::Vector2i(-1, -1);

	recent_mous_released_evnt.button = sf::Mouse::Button::Left;
	recent_mous_released_evnt.position = sf::Vector2i(-1, -1);

	//keyboard
	recent_keyboard_input = "";
	
	two_recent_keys_pressed.first.scancode = sf::Keyboard::Scancode::Unknown;
	two_recent_keys_pressed.second.scancode = sf::Keyboard::Scancode::Unknown;

	two_recent_keys_released.first.scancode = sf::Keyboard::Scancode::Unknown;
	two_recent_keys_released.second.scancode = sf::Keyboard::Scancode::Unknown;
}

void Application::run(const unsigned int& window_width, const unsigned int& window_height, const std::string& title, const sf::State& state)
{
	float aspectRatio = float(default_window_width) / float(default_window_height);

	get_camera().setSize(sf::Vector2f(default_window_width, default_window_height / aspectRatio));

	Core::run(window_width, window_height, title, state);
}

Application::Application()
{
	//application
	this->set_process_events_function(process_event_function);

	//view
	sf::View& camera = this->get_camera();
	camera.setCenter(sf::Vector2f(0, 0));
	this->set_camera_mod(Core::camera_settings::static_camera);
	




	this->run(800, 800, "Fox&Dot Scene Redactor", sf::State::Windowed);
}

Application::~Application(){}

void process_event_function(Core* the_core)
{

	APPLICATION

	//ON CLOSE
	const auto onClose = [&application](const sf::Event::Closed&) 
	{
		application.close();
	};

	//ON CLICK (PRESSED)
	const auto onClickPressed = [&application](const sf::Event::MouseButtonPressed& evnt) 
	{
			application.recent_mous_pressed_evnt = evnt;

			sf::Event::MouseButtonReleased& recent_released = application.recent_mous_released_evnt;

			if (application.recent_mous_released_evnt.position.x != -1 and recent_released.button == evnt.button)
			{
				application.recent_mous_released_evnt.position = sf::Vector2i(-1, -1);
			}
	};
	//ON CLICK (RELEASED)
	const auto onClickReleased = [&application](const sf::Event::MouseButtonPressed& evnt)
	{
			application.recent_mous_pressed_evnt = evnt;

			sf::Event::MouseButtonReleased& recent_released = application.recent_mous_released_evnt;

			if (application.recent_mous_released_evnt.position.x != -1 and recent_released.button == evnt.button)
			{
				application.recent_mous_released_evnt.position = sf::Vector2i(-1, -1);
			}
	};

	//ON RESIZE
	const auto onResize = [&application](const sf::Event::Resized evnt) {
		sf::View& camera = application.get_camera();

		float aspectRatio = float(evnt.size.x) / float(evnt.size.y);

		camera.setSize(sf::Vector2f(800,800 / aspectRatio));
	};
	
	//ON KEYBOARD INPUT
	const auto onKeyboardInput = [&application](const sf::Event::TextEntered evnt) {
		if (evnt.unicode != '\b') 
		{
			application.recent_keyboard_input = evnt.unicode;
		}
	};

	//ON KEY PRESSED
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

	//ON KEY RELEASED

	application.handleEvents(onClose, onClick, onResize, onKeyboardInput, onKeyPressed);
}