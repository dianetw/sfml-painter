#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::VideoMode mode(642, 640);
    sf::RenderWindow window(mode, "Painter");

    sf::Texture background;
    background.loadFromFile("background.png");
    sf::Sprite backgroundSprite(background);
    backgroundSprite.setPosition(0.f, 40.f);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cout << "arial.ttf is not found." << std::endl;
        return EXIT_FAILURE;
    }

    sf::String str("File saved.");
    sf::Text text;
    text.setString(str);
    text.setFillColor(sf::Color(128, 128, 128));
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(sf::Vector2f(window.getSize().x - text.getGlobalBounds().width, 20));

    // circle brush
    sf::CircleShape cursor(10);
    cursor.setOrigin(10.f, 10.f);
    cursor.setFillColor(sf::Color::Black);

    // retangle brush
    sf::RectangleShape rectangle(sf::Vector2f(20, 20));
    rectangle.setOrigin(10.f, 10.f);
    rectangle.setFillColor(sf::Color::Black);

    enum class BrushShape { CIRCLE, RECTANGLE };
    BrushShape brush = BrushShape::CIRCLE;

    sf::RenderTexture canvasTexture;
    canvasTexture.create(600, 560);
    canvasTexture.clear(sf::Color::White);
    canvasTexture.display();

    sf::Sprite canvasSprite(canvasTexture.getTexture());
    sf::Vector2f canvasOffset(20, 60);
    canvasSprite.setPosition(canvasOffset);

    std::vector<sf::Color> colors = {
        sf::Color(0, 0, 0),        // black
        sf::Color(255, 255, 255),  // white
        sf::Color(220, 20, 60),    // crimson
        sf::Color(255, 0, 0),      // red
        sf::Color(255, 69, 0),     // orange red
        sf::Color(255, 165, 0),    // orange
        sf::Color(255, 215, 0),    // gold
        sf::Color(255, 255, 0),    // yellow
        sf::Color(154, 205, 50),   // yellow green
        sf::Color(107, 142, 35),   // olive drab
        sf::Color(173, 255, 47),   // green yellow
        sf::Color(0, 255, 0),      // green (lime)
        sf::Color(0, 128, 0),      // green
        sf::Color(0, 255, 255),    // cyan
        sf::Color(0, 191, 255),    // deep sky blue
        sf::Color(0, 0, 255),      // blue
        sf::Color(0, 0, 139),      // dark blue
        sf::Color(138, 43,226),    // blue violet
        sf::Color(147, 112, 219),  // medium purple
        sf::Color(139, 0, 139),    // dark magenta
        sf::Color(128, 0, 128),    // purple
        sf::Color(255, 0, 255)     // magenta
    };

    // palette
    std::vector<sf::RectangleShape> swatch;
    for (size_t i = 0; i < colors.size(); i++) {
        sf::RectangleShape shape({ 20, 20 });
        shape.setOutlineColor(sf::Color(230, 230, 230));
        shape.setOutlineThickness(2);
        shape.setFillColor(colors[i]);
        shape.setPosition(float(20 + i * 20), 10.f);
        swatch.push_back(shape);
    }

    bool isSave = false;
    bool clearWindow = false;
    while (window.isOpen()) {
        sf::Event evt;
        if (window.pollEvent(evt)) {
            switch (evt.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                for (const auto& color : swatch) {
                    //if (color.getGlobalBounds().contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
                    //    cursor.setFillColor(color.getFillColor());
                    //}
                    if (color.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
                        if (brush == BrushShape::CIRCLE) {
                            cursor.setFillColor(color.getFillColor());
                        }
                        else {
                            rectangle.setFillColor(color.getFillColor());
                        }
                    }
                }
                break;
            case sf::Event::KeyPressed:
                std::cout << evt.key.code << std::endl;
                switch (evt.key.code) {
                case sf::Keyboard::S:
                    if (canvasTexture.getTexture().copyToImage().saveToFile("test.png")) {
                        isSave = true;
                    }
                    break;
                case sf::Keyboard::Num1:
                    if (brush == BrushShape::CIRCLE) {
                        cursor.setRadius(10.f);
                    }
                    else {
                        rectangle.setSize(sf::Vector2f(20, 20));
                    }
                    break;
                case sf::Keyboard::Num2:
                    if (brush == BrushShape::CIRCLE) {
                        cursor.setRadius(15.f);
                    }
                    else {
                        rectangle.setSize(sf::Vector2f(30, 30));
                    }
                    break;
                case sf::Keyboard::Num3:
                    if (brush == BrushShape::CIRCLE) {
                        cursor.setRadius(20.f);
                    }
                    else {
                        rectangle.setSize(sf::Vector2f(40, 40));
                    }
                    break;
                case sf::Keyboard::Num4:
                    if (brush == BrushShape::CIRCLE) {
                        cursor.setRadius(25.f);
                    }
                    else {
                        rectangle.setSize(sf::Vector2f(50, 50));
                    }
                    break;
                case sf::Keyboard::Num5:
                    if (brush == BrushShape::CIRCLE) {
                        cursor.setRadius(30.f);
                    }
                    else {
                        rectangle.setSize(sf::Vector2f(60, 60));
                    }
                    break;
                case sf::Keyboard::R:
                    if (brush == BrushShape::CIRCLE) {
                        brush = BrushShape::RECTANGLE;
                    }
                    break;
                case sf::Keyboard::C:
                    if (brush == BrushShape::RECTANGLE) {
                        brush = BrushShape::CIRCLE;
                    }
                    break;
                case sf::Keyboard::Delete:
                    canvasTexture.clear(sf::Color::White);
                    break;
                }
                break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            auto pos = sf::Mouse::getPosition(window);
            sf::Vector2f newPos = sf::Vector2f(pos) - canvasOffset;
            if (brush == BrushShape::CIRCLE) {
                cursor.setPosition(newPos);
                canvasTexture.draw(cursor);
            } else {
                rectangle.setPosition(newPos);
                canvasTexture.draw(rectangle);
            }
            canvasTexture.display();
            isSave = false;
        }

        window.clear(sf::Color::White);

        // draw palette
        for (const auto& s : swatch) {
            window.draw(s);
        }
        window.draw(backgroundSprite);
        window.draw(canvasSprite);
        if (isSave) {
            window.draw(text);
        }

        auto mousePos = sf::Mouse::getPosition(window);
        switch (brush) {
        case BrushShape::CIRCLE:
            cursor.setPosition(sf::Vector2f(mousePos));
            window.draw(cursor);
            break;
        case BrushShape::RECTANGLE:
            rectangle.setPosition(sf::Vector2f(mousePos));
            window.draw(rectangle);
            break;
        }

        window.display();
    }
}