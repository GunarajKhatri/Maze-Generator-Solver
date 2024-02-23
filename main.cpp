
#include <SFML/Graphics.hpp>
#include <iostream>
#include "maze.h"

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Maze Generation and Solving");

    Maze maze(WIDTH / CELL_SIZE, HEIGHT / CELL_SIZE);

    sf::RectangleShape generateButton(sf::Vector2f(150, 30));
    generateButton.setPosition(200, HEIGHT - 40);  // Adjusted button position
    generateButton.setFillColor(sf::Color::Blue);

    sf::RectangleShape solveButton(sf::Vector2f(150, 30));
    solveButton.setPosition(360, HEIGHT - 40);  // Adjusted button position
    solveButton.setFillColor(sf::Color::Green);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return 1;
    }

    sf::Text generateButtonText("Generate Maze", font, 16);
    generateButtonText.setPosition(210, HEIGHT - 38);
    generateButtonText.setFillColor(sf::Color::White);

    sf::Text solveButtonText("Solve Maze", font, 16);
    solveButtonText.setPosition(380, HEIGHT - 38);
    solveButtonText.setFillColor(sf::Color::White);

    bool visualizeSolutionFlag = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                // Check if the mouse click is within the generate button area
                if (event.mouseButton.x >= 200 && event.mouseButton.x <= 350 &&
                    event.mouseButton.y >= HEIGHT - 40 && event.mouseButton.y <= HEIGHT - 10) {
                    maze.initialize();
                    visualizeSolutionFlag = false;
                }

                // Check if the mouse click is within the solve button area
                if (event.mouseButton.x >= 360 && event.mouseButton.x <= 510 &&
                    event.mouseButton.y >= HEIGHT - 40 && event.mouseButton.y <= HEIGHT - 10) {
                    if (!visualizeSolutionFlag) {
                        maze.solveDFS();
                        visualizeSolutionFlag = true;
                    }
                }
            }
        }

        if (visualizeSolutionFlag) {
            maze.visualizeSolution(window);
            visualizeSolutionFlag = false;  // Reset the flag after visualization
        } else {
            maze.draw(window);
            window.draw(generateButton);
            window.draw(generateButtonText);
            window.draw(solveButton);
            window.draw(solveButtonText);
        }

        window.display();
    }

    return 0;
}
