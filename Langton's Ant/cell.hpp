//
//  cell.hpp
//  Langton's Ant
//
//  Created by 21maffetone on 12/11/17.
//  Copyright © 2017 21maffetone. All rights reserved.
//

#ifndef cell_hpp
#define cell_hpp

#include <SFML/Graphics.hpp>
#include "config.hpp"


class Cell
{
public:
    Cell(int x, int y, Config &c) : m_x { x }, m_y { y }, CONFIG { c } {}
    
    enum State
    {
        OFF,
        ON
    };
    
    void draw(sf::RenderTexture &window, sf::Color color);
    State getState() { return m_state; }
    int getIndex(int i, int j);
    void flip();
    
private:
    int m_x;
    int m_y;
    
    State m_state = ON;
    Config CONFIG;
};

#endif /* cell_hpp */
