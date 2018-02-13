
#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <vector>
#include "cell.hpp"
#include <ctime>
#include "randnum.hpp"
#include <iostream>

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand(); // discard first number
    
    Config config;
    config.height = 360;
    config.width = 640;
    config.cellSize = 5;
    config.cols = config.width / config.cellSize;
    config.rows = config.height / config.cellSize;
    
    std::vector<Cell> grid;
    
    sf::RenderWindow window(sf::VideoMode(config.width, config.height), "Conway's Game of Life");
    window.setFramerateLimit(20);
    
    // make the grid
    for (int j = 0; j < config.rows; ++j)
        for (int i = 0; i < config.cols; ++i)
        {
            grid.push_back(Cell(i, j, config));
        }
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        
        std::vector<Cell> nextGen;
        
        for(Cell cell : grid)
        {
            cell.draw(window);
            Cell newCell = cell;
            newCell.updateState(cell.getAliveNeighbors(grid));
            nextGen.push_back(newCell);
        }
        
        std::cout << grid.size() << '\n';
        
        grid = nextGen;

    
        window.display();
    }
}
