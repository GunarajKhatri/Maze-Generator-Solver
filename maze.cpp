#include "maze.h"
#include <iostream>
Maze::Maze(int width, int height) : width(width), height(height) {
    initialize();
}

void Maze::initialize() {
    maze.clear();
    maze.resize(height, std::vector<int>(width, 1));

    startX = std::rand() % (width / 2) * 2;
    startY = std::rand() % (height / 2) * 2;

    do {
        endX = std::rand() % (width / 2) * 2;
        endY = std::rand() % (height / 2) * 2;
    } while (endX == startX && endY == startY);

    generateMaze(startX, startY);

    maze[startY][startX] = 2;
    maze[endY][endX] = 3;
}

void Maze::generateMaze(int x, int y) {
    maze[y][x] = 0;

    std::vector<int> directions = {0, 1, 2, 3};
    std::random_shuffle(directions.begin(), directions.end());

    for (int direction : directions) {
        int nx = x + 2 * (direction == 1) - 2 * (direction == 3);
        int ny = y + 2 * (direction == 2) - 2 * (direction == 0);

        if (isSafe(nx, ny) && maze[ny][nx] == 1) {
            maze[y + (ny - y) / 2][x + (nx - x) / 2] = 0;
            generateMaze(nx, ny);
        }
    }
}

bool Maze::isSafe(int x, int y) {
    return (x >= 0 && x < width && y >= 0 && y < height);
}

bool Maze::dfs(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height || (maze[y][x] != 0 && maze[y][x] != 2 && maze[y][x]!=3)) {
        return false;
    }      

    if (x == endX && y == endY) {
        return true;
    }

    solutionPath.push_back({x, y});
    maze[y][x] = 4;  // Mark visited cells during DFS  

    // Explore in all directions
    if (isSafe(x + 1, y) && dfs(x + 1, y)) {
        return true;
    }
    if (isSafe(x - 1, y) && dfs(x - 1, y)) {
        return true;
    }
    if (isSafe(x, y + 1) && dfs(x, y + 1)) {
        return true;
    }
    if (isSafe(x, y - 1) && dfs(x, y - 1)) {
        return true;
    }

    // Backtrack if no path found
    solutionPath.pop_back();
    return false;
}

void Maze::solveDFS() {
    solutionPath.clear();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (maze[i][j] == 4) {
               maze[i][j]=0;
            } ;
        }
    }
    int x=startX;
    int y=startY;
    std::cout<<x<<" "<<y<<std::endl;  // start and end point coordinates
    dfs(x , y);
}

void Maze::visualizeSolution(sf::RenderWindow& window) {
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    // Draw the maze
    draw(window);

    // Draw the  solution path
    for (const auto& point : solutionPath) {
        int x = point.first;
        int y = point.second;
        square.setPosition(x * CELL_SIZE, y * CELL_SIZE);
        square.setFillColor(sf::Color::Yellow);  
        window.draw(square);

        window.display();

        // Introduce a delay for a smoother animation
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void Maze::draw(sf::RenderWindow& window) {
    sf::RectangleShape square;
    square.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            square.setPosition(j * CELL_SIZE, i * CELL_SIZE);

            if (maze[i][j] == 1) {
                square.setFillColor(sf::Color::Black); // color for wall 
            } else if (maze[i][j] == 2) {
                square.setFillColor(sf::Color::Green);  // color for start point 
            } else if (maze[i][j] == 3) {
                square.setFillColor(sf::Color::Red); // // color for end point 
            } else if (maze[i][j] == 4) {
                square.setFillColor(sf::Color::Blue);  // color for visited paths
            } else {
                square.setFillColor(sf::Color::White); //// color for wall free path 
            }

            window.draw(square);
        }
    }
}
