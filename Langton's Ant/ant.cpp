//
//  ant.cpp
//  Langton's Ant
//
//  Created by 21maffetone on 12/11/17.
//  Copyright © 2017 21maffetone. All rights reserved.
//

#include "ant.hpp"

int Ant::getIndex()
{
    return m_x + m_y * CONFIG.cols;
}

void Ant::turnRight()
{
    switch(m_direction)
    {
        case FORWARDS:
            m_direction = RIGHT;
            break;
        case RIGHT:
            m_direction = BACKWARDS;
            break;
        case BACKWARDS:
            m_direction = LEFT;
            break;
        case LEFT:
            m_direction = FORWARDS;
            break;
    }
}

void Ant::turnLeft()
{
    switch(m_direction)
    {
        case FORWARDS:
            m_direction = LEFT;
            break;
        case RIGHT:
            m_direction = FORWARDS;
            break;
        case BACKWARDS:
            m_direction = RIGHT;
            break;
        case LEFT:
            m_direction = BACKWARDS;
            break;
    }
}

void Ant::move()
{
    if (m_y > 0 && m_y < CONFIG.rows && m_x < CONFIG.cols && m_x > 0)
    {
        switch (m_direction)
        {
            case FORWARDS:
                --m_y;
                break;
            case BACKWARDS:
                ++m_y;
                break;
            case RIGHT:
                ++m_x;
                break;
            case LEFT:
                --m_x;
                break;
        }
    }
}

sf::Color Ant::hsv(int hue, float sat, float val)
{
    hue %= 360;
    while(hue<0) hue += 360;
    
    if(sat<0.f) sat = 0.f;
    if(sat>1.f) sat = 1.f;
    
    if(val<0.f) val = 0.f;
    if(val>1.f) val = 1.f;
    
    int h = hue/60;
    float f = float(hue)/60-h;
    float p = val*(1.f-sat);
    float q = val*(1.f-sat*f);
    float t = val*(1.f-sat*(1-f));
    
    switch(h)
    {
        default:
        case 0:
        case 6: return sf::Color(val*255, t*255, p*255);
        case 1: return sf::Color(q*255, val*255, p*255);
        case 2: return sf::Color(p*255, val*255, t*255);
        case 3: return sf::Color(p*255, q*255, val*255);
        case 4: return sf::Color(t*255, p*255, val*255);
        case 5: return sf::Color(val*255, p*255, q*255);
    }
}
