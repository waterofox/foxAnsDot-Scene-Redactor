#include "Application.h"

void process_event_function(Core* the_core);

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

	//scene
	testLabel.get_resource() = IBM_Plex_Mono_Medium;
	testLabel.setFillColor(sf::Color::White);
	testLabel.setPosition(sf::Vector2f(0, 0));

	Core::lay_type lay0; lay0["test"] = &testLabel;
	this->scene.push_back(lay0);



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
		application.get_recent_clicks().push(evnt);
	};
	const auto onResize = [&application](const sf::Event::Resized evnt) {
		sf::View& camera = application.get_camera();

		float aspectRatio = float(evnt.size.x) / float(evnt.size.y);

		camera.setSize(sf::Vector2f(800,800 / aspectRatio));
	};

	application.handleEvents(onClose, onClick, onResize);
}
