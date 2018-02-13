#include <SFML/Graphics.hpp>
#include "config.hpp"
#include <vector>
#include "cell.hpp"
#include "ant.hpp"
#include <random>
#include <ctime>

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand();
    Config config;
    config.width = 800;
    config.height = 600;
    config.cellSize = 1;
    config.cols = config.width / config.cellSize;
    config.rows = config.height / config.cellSize;
    
    std::vector<Cell> grid;
    
    for (int j = 0; j < config.rows; ++j)
        for (int i = 0; i < config.cols; ++i)
        {
            grid.push_back(Cell(i, j, config));
        }
    
    std::vector<Ant> ants;
    
    for (int i = 0; i < 301; ++i)
    {
        ants.push_back(Ant(config));
    }
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(config.width, config.height), "Langton's Ant");
    
    sf::RenderTexture texture;
    texture.create(config.width, config.height);
    
    for (auto &cell : grid)
    {
        cell.draw(texture, sf::Color::Black);
    }
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear screen
        window.clear(sf::Color::Black);
        
        for (auto &ant : ants)
        {
            if (grid[ant.getIndex()].getState() == Cell::ON)
            {
                ant.turnRight();
                grid[ant.getIndex()].flip();
                grid[ant.getIndex()].draw(texture, ant.getColor());
                ant.move();
                
            }
            else
            {
                ant.turnLeft();
                grid[ant.getIndex()].flip();
                grid[ant.getIndex()].draw(texture, ant.getColor());
                ant.move();
            }
        }
        texture.display();

        const sf::Texture& tex = texture.getTexture();
        sf::Sprite gridDrawable(tex);
        window.draw(gridDrawable);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
