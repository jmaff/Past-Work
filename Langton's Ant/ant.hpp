//
//  ant.hpp
//  Langton's Ant
//
//  Created by 21maffetone on 12/11/17.
//  Copyright © 2017 21maffetone. All rights reserved.
//

#ifndef ant_hpp
#define ant_hpp

#include "config.hpp"
#include "randnum.hpp"
#include <SFML/Graphics.hpp>

class Ant
{
public:
    enum Direction
    {
        FORWARDS,
        RIGHT,
        BACKWARDS,
        LEFT
    };
    
    Ant(int x, int y, Config &c) : m_x { x }, m_y { y }, CONFIG { c } {}
    
    Ant(Config &c) : CONFIG { c }
    {
        m_x = getRandomNumber(0, CONFIG.cols);
        m_y = getRandomNumber(0, CONFIG.rows);
    }
    
    int getIndex();
    sf::Color getColor() { return m_color; }
    
    void turnRight();
    void turnLeft();
    void move();
    
private:
    int m_x;
    int m_y;
    
    sf::Color m_color = hsv(getRandomNumber(0, 255), 255, 255);
    Direction m_direction = static_cast<Direction>(getRandomNumber(0, 3));
    Config CONFIG;
    
    sf::Color hsv(int hue, float sat, float val);
};

#endif /* ant_hpp */
