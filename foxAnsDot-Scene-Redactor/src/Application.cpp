#include "Application.h"

//UI
#include "UI/MANAGED/Input_Line.h"
#include "UI/LAYOUT/Horizontal_Layout.h"
#include "UI/LAYOUT/Vertical_Layout.h"
#include "UI/MANAGED/Scrollbar.h"
#include "UI/NON-MANAGED/Icon.h"
#include "SceneRedactor-UI/Com_Bar_Element.h"
#include "UI/MANAGED/Button_Icon.h"

void process_event_function(Core* the_core);
void zaticka(Core* the_core, Scene_Component* component);
void Application::init_resources()
{
	resource_manager.add_font("src\\resources\\fonts\\Monaspace Neon\\MonaspaceNeon-Medium.otf", MonaspaceNeon_Medium);
	resource_manager.font(MonaspaceNeon_Medium).setSmooth(false);

	resource_manager.add_texture("src\\resources\\icons\\component_icon.png",scene_component_icon);

	resource_manager.add_texture("src\\resources\\icons\\open_folder_icon.png", open_folder_icon);
	resource_manager.add_texture("src\\resources\\icons\\closed_folder_icon.png", closed_folder_icon);
	resource_manager.add_texture("src\\resources\\icons\\save_icon.png", save_icon);
	resource_manager.add_texture("src\\resources\\icons\\save_all_icon.png", save_all_icon);

	resource_manager.add_texture("src\\resources\\icons\\ctrlZ_icon.png", ctrlZ_icon);
	resource_manager.add_texture("src\\resources\\icons\\ctrlY_icon.png", ctrlY_icon);

	resource_manager.add_texture("src\\resources\\icons\\cursor_icon.png", cursor_icon);
	resource_manager.add_texture("src\\resources\\icons\\move_icon.png", move_icon);
	resource_manager.add_texture("src\\resources\\icons\\zoom_icon.png", zoom_icon);

	resource_manager.add_texture("src\\resources\\icons\\test.png", test);
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
	//init layouts
	application_layout = new Vertical_Layout();
	application_layout->make_main();
	
	command_menu_layout = new Horizontal_Layout();
	command_menu_layout->set_max_heigth(config.display_width / 50);
	command_menu_layout->set_align(Layout::align::left);
	application_layout->add_component(command_menu_layout);

	work_area_layout = new Horizontal_Layout();
	work_area_layout->set_align(Layout::align::rigth_top);
	application_layout->add_component(work_area_layout);

	scene_area_layout = new Vertical_Layout();
	work_area_layout->add_component(scene_area_layout);

	tools_menu_layout = new Horizontal_Layout();
	tools_menu_layout->set_max_heigth(config.display_width / 40);
	tools_menu_layout->set_align(Layout::align::left);
	scene_area_layout->add_component(tools_menu_layout);

	info_area_layout = new Vertical_Layout();
	info_area_layout->set_max_width(config.display_width / 6);
	work_area_layout->add_component(info_area_layout);

	//layouts style
	command_menu_layout->body.setFillColor(LINE_COLOR);

	work_area_layout->body.setFillColor(sf::Color::White);

	tools_menu_layout->body.setFillColor(BASE_COLOR);
	tools_menu_layout->body.setOutlineColor(sf::Color::Black);
	tools_menu_layout->body.setOutlineThickness(1);

	info_area_layout->body.setFillColor(BASE_COLOR);
	info_area_layout->body.setOutlineColor(sf::Color::Black);
	info_area_layout->body.setOutlineThickness(-1);

	//init ui
	//command buttons
	command_menu_buttons[0] = new Button("File",zaticka);
	command_menu_buttons[1] = new Button("Edit", zaticka);
	command_menu_buttons[2] = new Button("View", zaticka);
	command_menu_buttons[3] = new Button("Help", zaticka);

	for (int i = 0; i < 4; ++i)
	{
		Button& but = *command_menu_buttons[i];

		but.get_resource() = system_fonts::MonaspaceNeon_Medium;

		but.base_color    = LINE_COLOR;
		but.hovered_color = LIGHT_LINE_COLOR;
		but.active_color  = DARK_LINE_COLOR;
		but.get_label().label->setFillColor(sf::Color::White);
		but.body.setOutlineThickness(0);

		but.set_max_width(config.display_width / 30);
		but.set_min_width(config.display_width / 50);
		but.get_label().label->setCharacterSize(int(config.display_width / 125));

		but.name() = but.get_label().label->getString() + "_button";

		command_menu_layout->add_component(&but);
	}

	//tools buttons

	{
		int         button_icons[8] = {open_folder_icon,save_icon,save_all_icon,ctrlZ_icon,ctrlY_icon,cursor_icon,move_icon,zoom_icon};
		std::string button_names[8] = { "folder_buton","save_button","save_all_button","ctrlZ_button","ctrlY_button","cursor_button","move_button","zoom_button"};

		for (int i = 0; i < 8; ++i)
		{
			tools_menu_buttons[i] = new Button_Icon(zaticka);
			Button_Icon& but = *tools_menu_buttons[i];

			but.base_color    = BASE_COLOR;
			but.hovered_color = DARK_BASE_COLOR;
			but.active_color  = DARK_DARK_BASE_COLOR;
			but.body.setOutlineThickness(0);

			but.get_resource() = button_icons[i];
			but.name() = button_names[i];

			but.set_max_heigth(config.display_width/60);
			but.set_max_width(config.display_width / 60);

			Application::resource_manager.texture(button_icons[i]).setSmooth(true);

			tools_menu_layout->add_component(&but);
		}
	}

	//build scene;

	Core::lay_type background;
	background.emplace("work_area_layout", work_area_layout);

	//------------------------------------------------------------
	Core::lay_type layouts;
	layouts.emplace("application_layout", application_layout);

	layouts.emplace("commands_layout", command_menu_layout);

	layouts.emplace("scene_layout", scene_area_layout);
	layouts.emplace("info_area_layout", info_area_layout);

	layouts.emplace("tools_layout", tools_menu_layout);

	//------------------------------------------------------------
	Core::lay_type ui;
	for (int i = 0; i < 4;++i)
	{
		Button& but = *command_menu_buttons[i];
		ui.emplace(but.name(), &but);
	}

	for (int i = 0; i < 8; ++i)
	{
		Button_Icon& but = *tools_menu_buttons[i];
		ui.emplace(but.name(), &but);
	}



	scene.push_back(background);
	scene.push_back(layouts);
	scene.push_back(ui);
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
