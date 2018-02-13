
//
// Generates a maze on a grid using a depth search first algorithm. Inspired by The Coding Train on YouTube,
// where he creates this in p5.js
//

#include <SFML/Graphics.hpp>
#include <vector>
#include "cell.hpp"
#include <iostream>
#include <random>
#include <ctime>
#include <stack>

void removeWalls(Cell *a, Cell *b)
{
    int x = a->getI() - b->getI();
    
    if (x == 1)
    {
        a->m_walls[Cell::LEFT] = false;
        b->m_walls[Cell::RIGHT] = false;
    }
    else if (x == -1)
    {
        a->m_walls[Cell::RIGHT] = false;
        b->m_walls[Cell::LEFT] = false;
    }
    
    int y = a->getJ() - b->getJ();
    
    if (y == 1)
    {
        a->m_walls[Cell::TOP] = false;
        b->m_walls[Cell::BOTTOM] = false;
    }
    else if (y == -1)
    {
        a->m_walls[Cell::BOTTOM] = false;
        b->m_walls[Cell::TOP] = false;
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    rand(); // discard first result
    
    int cols;
    int rows;
    int cSize = 10;
    std::vector<Cell> grid;
    
    const int width { 400 };
    const int height { 400 };
    
    std::stack<Cell*> stack;
    
    sf::RenderTexture renderTexture;
    renderTexture.create(width, height);
    
    sf::RenderWindow window(sf::VideoMode(width, height), "Maze Generator");
    window.setFramerateLimit(30);
    
    cols = width / cSize;
    rows = height / cSize;
    
    for (int j = 0; j < rows; ++j)
        for (int i = 0; i < cols; ++i)
        {
            grid.push_back(Cell(i, j, cSize));
        }
    
    Cell *current = &grid[0];
    
    // std::cout << current.getVisited() << '\n';
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }
        
        renderTexture.clear(sf::Color::Black);
        
        for (int i = 0; i < grid.size(); ++i)
        {
            grid[i].draw(renderTexture);
        }
        
        current->highlight(renderTexture);
        
        renderTexture.display();
        
        const sf::Texture& texture = renderTexture.getTexture();
        sf::Sprite gridDrawable(texture);
        
        window.clear(sf::Color::Black);
        window.draw(gridDrawable);
        window.display();
        
        current->setVisited();
        
        try
        {
            // Step 1
            Cell *next = &current->checkNeighbors(grid, cols, rows);
            next->setVisited();
            
            // Step 2
            stack.push(current);
            
            // Step 3
            removeWalls(current, next);
            
            // Step 4
            current = next;
        }
        catch (int err) // if we have no neighbors left
        {
            if (stack.size() > 0)
            {
                current = stack.top();
                stack.pop();
            }
        }
        
        
    }

    return EXIT_SUCCESS;
}
