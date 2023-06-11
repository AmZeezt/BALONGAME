#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace sf;

int main() {

	//Window declaration
	RenderWindow window(VideoMode(800, 600), "BALONG", Style::Titlebar | Style::Close);
	Event ev;

	//Game loop
	while (window.isOpen())
	{
		//App status listener
		while (window.pollEvent(ev))
		{
			switch (ev.type) {
			//Close event
			case Event::Closed:
				window.close();
				break;
			//Key Close events
			case Event::KeyPressed:
				if (ev.key.code == Keyboard::Escape)
					window.close();
			}
		}

		//App updater

		//App renderer
		window.clear(); //Scrap frame

		//Draw

		window.display(); //Render frame
	}


	//Proper close
	return 0;
}