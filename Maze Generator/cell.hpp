//
//  cell.hpp
//  Maze Generator
//
//  Created by 21maffetone on 12/10/17.
//  Copyright © 2017 21maffetone. All rights reserved.
//

#ifndef cell_hpp
#define cell_hpp

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <iostream>

class Cell
{
private:
    int m_i;
    int m_j;
    int m_size;
    bool m_visited = false;
    
    int getIndex(int i, int j, int cols, int rows);
    static int getRandomNumber(int min, int max);
    
    
public:
    bool m_walls[4] {true, true, true, true}; // sorry for violating data encapsulation
    
    enum Wall
    {
        TOP,
        RIGHT,
        BOTTOM,
        LEFT
    };
    
    Cell(int i, int j, int size) : m_i { i }, m_j { j }, m_size { size } {}
    
    void draw(sf::RenderTexture &rTexture);
    void highlight(sf::RenderTexture &rTexture);
    
    void setVisited() { m_visited = true; }
    bool hasBeenVisited() { return m_visited; }
    
    int getI() { return m_i; }
    int getJ() {return m_j; }
    
    Cell& checkNeighbors(std::vector<Cell> &grid, int cols, int rows);
};

#endif /* cell_hpp */
