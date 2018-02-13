//
//  cell.cpp
//  Maze Generator
//
//  Created by 21maffetone on 12/10/17.
//  Copyright © 2017 21maffetone. All rights reserved.
//

#include "cell.hpp"


void Cell::draw(sf::RenderTexture &rTexture)
{
    int x = m_i * m_size;
    int y = m_j * m_size;
    
    if(m_visited)
    {
        sf::RectangleShape cell(sf::Vector2f(m_size, m_size));
        cell.setPosition(x, y);

        cell.setFillColor(sf::Color(255, 0, 255, 100));

        rTexture.draw(cell);
    }
    
    if (m_walls[TOP])
    {
        sf::Vertex top[] = {
            sf::Vertex(sf::Vector2f(x, y)),
            sf::Vertex(sf::Vector2f(x + m_size, y))
        };

        rTexture.draw(top, 2, sf::Lines);
    }

    if (m_walls[RIGHT])
    {
        sf::Vertex right[] = {
            sf::Vertex(sf::Vector2f(x + m_size, y)),
            sf::Vertex(sf::Vector2f(x + m_size, y + m_size))
        };

        rTexture.draw(right, 2, sf::Lines);
    }

    if (m_walls[BOTTOM])
    {
        sf::Vertex bottom[] = {
            sf::Vertex(sf::Vector2f(x + m_size, y + m_size)),
            sf::Vertex(sf::Vector2f(x, y + m_size))
        };

        rTexture.draw(bottom, 2, sf::Lines);
    }

    if (m_walls[LEFT])
    {
        sf::Vertex left[] = {
            sf::Vertex(sf::Vector2f(x, y + m_size)),
            sf::Vertex(sf::Vector2f(x, y))
        };

        rTexture.draw(left, 2, sf::Lines);
    }
    
    
}

void Cell::highlight(sf::RenderTexture &rTexture)
{
    int x = m_i * m_size;
    int y = m_j * m_size;
    
    sf::RectangleShape highlighter(sf::Vector2f(m_size, m_size));
    highlighter.setPosition(x, y);

    highlighter.setFillColor(sf::Color(0, 0, 255, 100));

    rTexture.draw(highlighter);
}

int Cell::getIndex(int i, int j, int cols, int rows)
{
    if (i < 0 || j < 0 || i > cols - 1 || j > rows - 1)
        throw -1;
    
    return i + j * cols;
}

int Cell::getRandomNumber(int min, int max)
{
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  // static used for efficiency, so we only calculate this value once
    // evenly distribute the random number across our range
    return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

Cell& Cell::checkNeighbors(std::vector<Cell> &grid, int cols, int rows)
{
    std::vector<Cell*> neighbors;
    
    try
    {
        //Cell top = grid[getIndex(m_i, m_j - 1, cols, rows)];
        Cell &top = grid[getIndex(m_i, m_j - 1, cols, rows)];
        
        if (!top.hasBeenVisited())
        {
            neighbors.push_back(&top);
        }
        
    }
    
    catch(int err) {}
    
    try
    {
        Cell &right = grid[getIndex(m_i + 1, m_j, cols, rows)];
        
        if (!right.hasBeenVisited())
        {
            neighbors.push_back(&right);
        }
    }
    
    catch (int err) {}
    
    try
    {
        Cell &bottom = grid[getIndex(m_i, m_j + 1, cols, rows)];
        
        if (!bottom.hasBeenVisited())
        {
            neighbors.push_back(&bottom);
        }
    }
    catch (int err) {}
    
    try
    {
        Cell &left = grid[getIndex(m_i - 1, m_j, cols, rows)];
        
        if (!left.hasBeenVisited())
        {
            neighbors.push_back(&left);
        }
    }
    catch (int err) {}
    
    if (neighbors.size() > 0)
    {
        return *neighbors[getRandomNumber(0, neighbors.size() - 1)];
    }
    else
    {
        throw -1;
    }
        
        
}

