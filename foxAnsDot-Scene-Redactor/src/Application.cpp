#include "Application.h"

//UI
#include "UI/Button.h"
#include "UI/Input_Line.h"

void process_event_function(Core* the_core);
void confirm_input_slot(Core* the_core, Scene_Component* component);
void Application::init_resources()
{
	resource_manager.add_font("src\\resources\\fonts\\Monaspace Neon\\MonaspaceNeon-Medium.otf", MonaspaceNeon_Medium);
	resource_manager.font(MonaspaceNeon_Medium).setSmooth(false);
}
void Application::clear_key(Application& application,const sf::Keyboard::Scancode& scancode)
{
	if (application.two_recent_keys_pressed.first.scancode == scancode)
	{
		application.two_recent_keys_pressed.first = application.two_recent_keys_pressed.second;
		application.two_recent_keys_pressed.first.scancode = sf::Keyboard::Scancode::Unknown;
	}
	else
	{
		application.two_recent_keys_pressed.second.scancode = sf::Keyboard::Scancode::Unknown;
	}
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
	init_resources();
	init_handling_fields();

	//view
	sf::View& camera = this->get_camera();
	camera.setCenter(sf::Vector2f(0, 0));
	this->set_camera_mod(Core::camera_settings::static_camera);



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

Application::~Application(){}

void Application::clear_pressed_fields()
{
	recent_mous_pressed_evnt.button = sf::Mouse::Button::Left;
	recent_mous_pressed_evnt.position = sf::Vector2i(-1, -1);

	recent_keyboard_input = "";
}


void process_event_function(Core* the_core)
{

	APPLICATION

		application.clear_pressed_fields();

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
	const auto onClickReleased = [&application](const sf::Event::MouseButtonReleased& evnt)
	{
			application.recent_mous_released_evnt = evnt;

			sf::Event::MouseButtonPressed& recent_pressed = application.recent_mous_pressed_evnt;

			if (application.recent_mous_pressed_evnt.position.x != -1 and recent_pressed.button == evnt.button)
			{
				application.recent_mous_pressed_evnt.position = sf::Vector2i(-1, -1);
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
		

		if (application.two_recent_keys_pressed.first.scancode == sf::Keyboard::Scancode::Unknown)
		{
			application.two_recent_keys_pressed.first = evnt;
		}
		else
		{
			if (application.two_recent_keys_pressed.second.scancode == sf::Keyboard::Scancode::Unknown)
			{
				application.two_recent_keys_pressed.second = evnt;
			}
			else
			{
				application.two_recent_keys_pressed.first = application.two_recent_keys_pressed.second;
				application.two_recent_keys_pressed.second = evnt;
			}
		}
		
	};

	const auto onKeyReleased = [&application](const sf::Event::KeyReleased evnt) {
		if (application.two_recent_keys_released.first.scancode == sf::Keyboard::Scancode::Unknown)
		{
			application.two_recent_keys_released.first = evnt;
		}
		else
		{
			if (application.two_recent_keys_released.second.scancode == sf::Keyboard::Scancode::Unknown)
			{
				application.two_recent_keys_released.second = evnt;
			}
			else
			{
				application.two_recent_keys_released.first = application.two_recent_keys_released.second;
				application.two_recent_keys_released.second = evnt;
			}
		}
		
		
		Application::clear_key(application, evnt.scancode);

	};

	//ON KEY RELEASED

	application.handleEvents(onClose, onClickPressed,onClickReleased, onResize, onKeyboardInput, onKeyPressed,onKeyReleased);
}
void confirm_input_slot(Core* the_core, Scene_Component* component)
{
	APPLICATION
		Input_Line* line = static_cast<Input_Line*>(application.get_component("input"));
	std::cout << line->get_text() << '\n';
	line->clear();
}