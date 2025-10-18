#include "Application.h"

//UI
#include "UI/Input_Line.h"
#include "UI/Horizontal_Layout.h"
#include "UI/Vertical_Layout.h"
#include "UI/scrollbar/Scrollbar.h"

void process_event_function(Core* the_core);
void zaticka(Core* the_core, Scene_Component* component);
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

	//interface
	/*
	//main
	Vertical_Layout application_layout;
	application_layout.make_main();
	application_layout.body.setFillColor(sf::Color(22, 26, 31));
	application_layout.set_align(Layout::align::left);

	//command menu
	Horizontal_Layout command_menu;
	command_menu.set_min_heigth(50);
	command_menu.body.setFillColor(sf::Color(85,97,120));

	Input_Line line;
	line.set_max_width(800);
	line.set_max_heigth(50);

	line.get_resource() = MonaspaceNeon_Medium;
	line.get_type_of_resource() = Resource_Manager::resource_type::font;

	command_menu.add_component(&line);
	command_menu.set_align(Layout::align::center);

	//scene components & properties
	Vertical_Layout menu;
	menu.body.setFillColor(sf::Color(42, 49, 59));
	
	Scrollbar components;
	components.set_max_heigth(400);
	menu.add_component(&components);

	components.get_type_of_resource() = Resource_Manager::resource_type::font;
	components.get_resource() = MonaspaceNeon_Medium;



	//scene
	Horizontal_Layout scene_layout;

	//work_area
	Horizontal_Layout work_area;
	work_area.add_component(&scene_layout, 7);
	work_area.add_component(&menu, 2);


	application_layout.add_component(&command_menu,1);
	application_layout.add_component(&work_area,20);

	//build scene
	Core::lay_type layouts;
	Core::lay_type layouts2;
	Core::lay_type lay_of_ui_components;
	layouts.emplace("main_Layout", &application_layout);
	layouts2.emplace("command_menu", &command_menu);
	layouts2.emplace("work_layout", &work_area);
	layouts2.emplace("menu", &menu);

	lay_of_ui_components.emplace("input_line", &line);
	lay_of_ui_components.emplace("scene_components_bar", &components);


	scene.push_back(layouts);
	scene.push_back(layouts2);
	scene.push_back(lay_of_ui_components);
	*/
	
	Horizontal_Layout main_l;
	main_l.make_main();
	main_l.body.setFillColor(sf::Color::Magenta);

	lay_type lay; lay.emplace("test", &main_l);


	Vertical_Layout a; a.body.setFillColor(sf::Color::Green);
	a.set_max_width(100);

	Vertical_Layout b; b.body.setFillColor(sf::Color::Blue);
	//b.set_min_width(100);

	Vertical_Layout c; c.body.setFillColor(sf::Color::Red);
	//c.set_max_width(100);

	Vertical_Layout d; d.body.setFillColor(sf::Color::Cyan);
	//d.set_max_width(100);

	lay_type lay1; 
	lay1.emplace("A", &a);
	lay1.emplace("B", &b);
	lay1.emplace("C", &c);
	lay1.emplace("D", &d);

	main_l.add_component(&a);
	main_l.add_component(&b);
	main_l.add_component(&c);
	main_l.add_component(&d);


	scene.push_back(lay);
	scene.push_back(lay1);

	this->run(800, 800, "foxAndDot Scene Redactor", sf::State::Windowed);
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

		camera.setSize(sf::Vector2f(evnt.size.x, evnt.size.y));
		
		/*
		sf::View& camera = application.get_camera();

		float aspectRatio = float(evnt.size.x) / float(evnt.size.y);

		camera.setSize(sf::Vector2f(800,800 / aspectRatio));
		*/
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

void zaticka(Core* the_core, Scene_Component* component)
{
}
