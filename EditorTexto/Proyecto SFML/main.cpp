#include <SFML/Graphics.hpp>
#include <iostream>
#include "./TextBox.h"




int main() {
    sf::RenderWindow window;
    sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 2) - 445, (sf::VideoMode::getDesktopMode().height / 2) - 480);
    window.create(sf::VideoMode(900, 900), "Editor de texto", sf::Style::Titlebar | sf::Style::Close);
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);
   
    sf::Font cascadiacode;
    cascadiacode.loadFromFile("C:/WINDOWS/FONTS/CASCADIACODE.TTF");
    TextBox textbox1(15, sf::Color::White, true, { 100,100 });
   textbox1.setFont(cascadiacode);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
            case sf::Event::TextEntered:
                textbox1.typedOn(event);

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) 
                {
                    int direction = event.key.code;
                    textbox1.movePosition(direction);

                }
              break;
            default:
               break;
            }
        }
        window.clear();
        textbox1.drawTo(window);
        window.display();

        }
    return 0;
}



//tarea: agregar la propiedad name al text, y que por medio de las flechitas me pueda mover y editar el texto y lo quiere en el mismo evento

///https://gameprogrammingpatterns.com/observer.html ***Keypresed****