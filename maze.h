#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <stack>


const int WIDTH = 890;
const int HEIGHT = 690;
const int CELL_SIZE = 10;

class Maze {
public:
    Maze(int width, int height);

    void generate(); 
    void initialize(); // Function to generate the maze
    void solveDFS();  // Function to solve the maze using recursive backtracking
    void visualizeSolution(sf::RenderWindow& window);  // Function to visualize the solution path
    void draw(sf::RenderWindow& window);

private:
    int width, height;
    std::vector<std::vector<int>> maze;
    std::vector<std::pair<int, int>> solutionPath;  // Store the solution path
    void generateMaze(int x, int y);
    bool dfs(int x, int y);
    bool isSafe(int x, int y);
    int startX,startY;
    int endX, endY;
};

#endif // MAZE_H
