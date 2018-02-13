//
//  cell.cpp
//  Langton's Ant
//
//  Created by 21maffetone on 12/11/17.
//  Copyright © 2017 21maffetone. All rights reserved.
//

#include "cell.hpp"

int Cell::getIndex(int i, int j)
{
    if (i < 0 || j < 0 || i > CONFIG.cols - 1 || j > CONFIG.rows - 1)
        throw -1;
    
    return i + j * CONFIG.cols;
}

void Cell::flip()
{
    if (m_state == ON)
        m_state = OFF;
    else
        m_state = ON;
}

void Cell::draw(sf::RenderTexture &window, sf::Color color)
{
    int x = m_x * CONFIG.cellSize;
    int y = m_y * CONFIG.cellSize;
    
    sf::RectangleShape cell(sf::Vector2f(CONFIG.cellSize, CONFIG.cellSize));
    cell.setPosition(x, y);
    
    if (m_state == ON)
        cell.setFillColor(sf::Color::White);
    else
        cell.setFillColor(color);
    
    
//    cell.setOutlineColor(sf::Color::Black);
//    cell.setOutlineThickness(1);
    
    window.draw(cell);
}


