//
//  cell.hpp
//  Conway's Game of Life
//
//  Created by 21maffetone on 12/10/17.
//  Copyright © 2017 21maffetone. All rights reserved.
//

#ifndef cell_hpp
#define cell_hpp

#include <SFML/Graphics.hpp>
#include "config.hpp"
#include "randnum.hpp"
#include <vector>

class Cell
{
public:
    Cell(int x, int y, Config &c) : m_x { x }, m_y { y }, CONFIG { c }
    {
        m_state = static_cast<State>(getRandomNumber(0, 1));
    }
    
    enum State
    {
        DEAD,
        ALIVE
    };
    
    bool isAlive() { return m_state == ALIVE; }
    
    void draw(sf::RenderWindow &window);
    int getIndex(int i, int j);
    int getAliveNeighbors(std::vector<Cell> &grid);
    void updateState(int aliveNeighbors);
    
private:
    int m_x;
    int m_y;
    State m_state;
    
    Config CONFIG;
    
};

#endif /* cell_hpp */
