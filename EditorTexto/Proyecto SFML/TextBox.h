#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextBox {
public:
    TextBox() {}
    TextBox(int size, sf::Color color, bool sel, sf::Vector2f pos) 
    {
        textbox.setCharacterSize(size);
        textbox.setFillColor(color);
        isSelected = sel;
        this->setPosition(pos);
        if (sel) 
        {
            textbox.setString("_");
        }
        else 
        {
            textbox.setString("");
        }
    }

    void setFont(sf::Font& font) 
    {
        textbox.setFont(font);
    }

    void setPosition(sf::Vector2f pos) 
    {
        textbox.setPosition(pos);
    }

    void setLimit(bool ToF, int lim) 
    {
        hasLimit = ToF;
        limit = lim;
    }

    void movePosition(int direction) 
    {
        int cursorPosition = text.tellp();

        if (direction == sf::Keyboard::Left && cursorPosition > 0) 
        {
            cursorPosition--;

        }
        else if (direction == sf::Keyboard::Right && cursorPosition < text.str().length()) 
        {
            cursorPosition++;
        }

        text.seekp(cursorPosition);

        std::string displayedText = text.str();
        displayedText.insert(cursorPosition, "_");
        textbox.setString(displayedText);
    }

    void setSelected(bool sel) 
    {
        isSelected = sel;
        if (!sel)
        {
            std::string t = text.str();
            std::string newT = "";
            for (int i = 0; i < t.length() - 1; i++)
            {
                newT += t[i];
            }
            textbox.setString(newT);
        }
    }

    std::string getText() 
    {
        return text.str();
    }

    void drawTo(sf::RenderWindow& window) 
    {
        window.draw(textbox);
    }


    void typedOn(sf::Event input) 
    {
        if (isSelected)
        {
            int charTyped = input.text.unicode;
            if (charTyped < 128)
            {
                if (hasLimit)
                {
                    if (text.str().length() <= limit) 
                    {
                        inputLogic(charTyped);
                    }
                    else if (text.str().length() > limit && charTyped == DELETE_KEY) 
                    {
                        deleteLastChar();
                    }
                }

                else
                {
                    inputLogic(charTyped);
                }
            }
        }
    }

private:
    sf::Text textbox;
    std::ostringstream text;
    int limit;
    bool hasLimit;
    bool isSelected = false;

    void inputLogic(int charTyped) {
        if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) 
        {
            text << static_cast<char>(charTyped);
        }
        else if (charTyped == DELETE_KEY) 
        {
            if (text.str().length() > 0)
            {
                deleteLastChar();
            }
            textbox.setString(text.str() + "_");
        }
        textbox.setString(text.str() + "_");
    }

    void deleteLastChar() 
    {
        std::string t = text.str();
        std::string newT = "";
        for (int i = 0; i < t.length() - 1; i++)
        {
            newT += t[i];
        }
        text.str("");
        text << newT;
        textbox.setString(text.str());
    }

};


