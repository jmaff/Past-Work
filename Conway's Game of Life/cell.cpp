//
//  cell.cpp
//  Conway's Game of Life
//
//  Created by 21maffetone on 12/10/17.
//  Copyright © 2017 21maffetone. All rights reserved.
//

#include "cell.hpp"

void Cell::draw(sf::RenderWindow &window)
{
    int x = m_x * CONFIG.cellSize;
    int y = m_y * CONFIG.cellSize;
    
    sf::RectangleShape cell(sf::Vector2f(CONFIG.cellSize, CONFIG.cellSize));
    cell.setPosition(x, y);
    
    
    switch(m_state)
    {
        case DEAD:
            cell.setFillColor(sf::Color::White);
            break;
        case ALIVE:
            cell.setFillColor(sf::Color::Black);
            break;
    }
    
//    cell.setOutlineThickness(1);
//    cell.setOutlineColor(sf::Color(211, 211, 211));
    
    window.draw(cell);
}

int Cell::getIndex(int i, int j)
{
    if (i < 0 || j < 0 || i > CONFIG.cols - 1 || j > CONFIG.rows - 1)
        throw -1;
    
    return i + j * CONFIG.cols;
}

int Cell::getAliveNeighbors(std::vector<Cell> &grid)
{
    int aliveNeighbors = 0;
    
    // check the state of nine neighbors
    try
    {
        Cell &tl = grid[getIndex(m_x - 1, m_y - 1)];
        if (tl.isAlive())
        {
            ++aliveNeighbors;
        }
    }
    catch(int err) {}

    try
    {
        Cell &tm = grid[getIndex(m_x, m_y - 1)];
        if (tm.isAlive())
        {
            ++aliveNeighbors;
        }
    }
    catch(int err) {}
    
    try
    {
        Cell &tr = grid[getIndex(m_x + 1, m_y - 1)];
        if (tr.isAlive())
        {
            ++aliveNeighbors;
        }
    }
    catch(int err) {}
    
    try
    {
        Cell &ml = grid[getIndex(m_x - 1, m_y)];
        if (ml.isAlive())
        {
            ++aliveNeighbors;
        }
    }
    catch(int err) {}
    
    try
    {
        Cell &mr = grid[getIndex(m_x + 1, m_y)];
        if (mr.isAlive())
        {
            ++aliveNeighbors;
        }
    }
    catch(int err) {}
    
    try
    {
        Cell &bl = grid[getIndex(m_x - 1, m_y + 1)];
        if (bl.isAlive())
        {
            ++aliveNeighbors;
        }
    }
    catch(int err) {}
    
    try
    {
        Cell &bm = grid[getIndex(m_x, m_y + 1)];
        if (bm.isAlive())
        {
            ++aliveNeighbors;
        }
    }
    catch(int err) {}
    
    try
    {
        Cell &br = grid[getIndex(m_x + 1, m_y + 1)];
        if (br.isAlive())
        {
            ++aliveNeighbors;
        }
    }
    catch(int err) {}
    
    return aliveNeighbors;
    
}

void Cell::updateState(int aliveNeighbors)
{
    if (m_state == ALIVE && aliveNeighbors < 2)
        m_state = DEAD;
    
    else if (m_state == ALIVE && aliveNeighbors > 3)
        m_state = DEAD;
    
    else if (m_state == DEAD && aliveNeighbors == 3)
        m_state = ALIVE;
}
