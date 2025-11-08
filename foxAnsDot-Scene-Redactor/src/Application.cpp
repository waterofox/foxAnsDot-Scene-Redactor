#include "Application.h"

//UI
#include "UI/MANAGED/Input_Line.h"
#include "UI/LAYOUT/Horizontal_Layout.h"
#include "UI/LAYOUT/Vertical_Layout.h"
#include "UI/MANAGED/Scrollbar.h"
#include "UI/NON-MANAGED/Icon.h"
#include "SceneRedactor-UI/Com_Bar_Element.h"

void process_event_function(Core* the_core);
void zaticka(Core* the_core, Scene_Component* component);
void Application::init_resources()
{
	resource_manager.add_font("src\\resources\\fonts\\Monaspace Neon\\MonaspaceNeon-Medium.otf", MonaspaceNeon_Medium);
	resource_manager.font(MonaspaceNeon_Medium).setSmooth(false);

	resource_manager.add_texture("src\\resources\\icons\\component_icon.png",scene_component_icon);
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
	parse_config();
	//application
	this->set_process_events_function(process_event_function);
	init_resources();
	init_handling_fields();

	//view
	sf::View& camera = this->get_camera();

	camera.setCenter(sf::Vector2f(0, 0));
	this->set_camera_mod(Core::camera_settings::static_camera);

	//INTERFACE FKLKJFJSFJSDKFLSLJFSLKD
	
	init_interface();

	this->run(800, 800, "foxAndDot Scene Redactor", sf::State::Windowed);
}

Application::~Application(){}

void Application::clear_pressed_fields()
{
	recent_mous_pressed_evnt.button = sf::Mouse::Button::Left;
	recent_mous_pressed_evnt.position = sf::Vector2i(-1, -1);

	recent_keyboard_input = "";
}

void Application::parse_config()
{
	std::ifstream config(config_path);
	if (!config.is_open())
	{
		std::cout << "NO CONFIG FILE\n";
		return;
	}

	std::string buffer;
	config >> buffer; //DISPLAY
	config >> buffer >> this->config.display_heigth;
	config >> buffer >> this->config.display_width;

}

void Application::init_interface()
{
	application_layout = new Vertical_Layout();
	application_layout->make_main();

	//buttons
	command_menu_buttons = new std::vector<Button*>(3);

	(*command_menu_buttons)[0] = new Button("file", zaticka);
	(*command_menu_buttons)[0]->name() = "file_button";
	(*command_menu_buttons)[1] = new Button("scene", zaticka);
	(*command_menu_buttons)[1]->name() = "scene_button";
	(*command_menu_buttons)[2] = new Button("settings", zaticka);
	(*command_menu_buttons)[2]->name() = "settings_button";


	command_menu_layout = new Horizontal_Layout();
	for (int i = 0; i < command_menu_buttons->size(); ++i)
	{
		(*command_menu_buttons)[i]->set_max_width(200);
		(*command_menu_buttons)[i]->get_resource() = system_fonts::MonaspaceNeon_Medium;
		command_menu_layout->add_component((*command_menu_buttons)[i]);
	}
	command_menu_layout->set_align(Layout::align::left);
	command_menu_layout->set_max_heigth(config.display_width / 75);
	command_menu_layout->set_min_heigth(config.display_width / 75);
	
	application_layout->add_component(command_menu_layout);

	//components bar
	info_area_layout = new Vertical_Layout();

	components_bar = new Scrollbar();
	components_bar->set_max_heigth(600);
	components_bar->get_type_of_resource() = Resource_Manager::resource_type::font;
	components_bar->get_resource() = system_fonts::MonaspaceNeon_Medium;

	info_area_layout->add_component(components_bar);
	info_area_layout->set_min_width(200);
	info_area_layout->set_max_width(500);

	work_area_layout = new Horizontal_Layout();
	scene_area_layout = new Horizontal_Layout;

	work_area_layout->add_component(scene_area_layout);
	work_area_layout->add_component(info_area_layout);

	work_area_layout->set_align(Layout::align::rigth);

	application_layout->add_component(work_area_layout);
	
	//SCENE

	Core::lay_type layouts_lay;
	layouts_lay.emplace("main", application_layout);
	layouts_lay.emplace("commands_menu", command_menu_layout);
	layouts_lay.emplace("work_area", work_area_layout);
	layouts_lay.emplace("scene_area", scene_area_layout);
	layouts_lay.emplace("info_area", info_area_layout);

	Core::lay_type base_ui_lay;
	for (int i = 0; i < command_menu_buttons->size(); ++i) 
	{
		base_ui_lay.emplace((*command_menu_buttons)[i]->name(),(*command_menu_buttons)[i]);
	}



	base_ui_lay.emplace("components_bar", components_bar);

	scene.push_back(layouts_lay);
	scene.push_back(base_ui_lay);
}


void process_event_function(Core* the_core)
{

	APPLICATION

		application.clear_pressed_fields();

	if (!application.started)
	{
		application.resized = false;
	}

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
		
		application.resized = true;
		
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
