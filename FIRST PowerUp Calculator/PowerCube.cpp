//
//  PowerCube.cpp
//  FRC PowerUp Calculator
//
//  Created by 21maffetone on 1/9/18.
//  Copyright © 2018 21maffetone. All rights reserved.
//
#include "PowerCube.hpp"

PowerUp PowerCube::getPowerUp() const
{
    if (m_position < 3 && m_position >= 0)
    {
        return PowerUp::FORCE;
    }
    else if (m_position < 6 && m_position >= 0)
    {
        return PowerUp::BOOST;
    } else if (m_position < 9 && m_position >= 0){
        return PowerUp::LEVITATE;
    }
    else
    {
        if (m_position == -1) { return PowerUp::FORCE; }
        else if (m_position == -2) { return PowerUp::BOOST; }
        else { return PowerUp::LEVITATE; }
    }
    
}

Level PowerCube::getLevel() const
{
    if (m_position < 0)
    {
        return Level::NONE;
    }
    
    if ((m_position + 1) % 3 == 0)
    {
        return Level::THIRD;
    }
    else if (m_position == 1 || m_position == 4 || m_position == 7)
    {
        return Level::SECOND;
    }
    else
    {
        return Level::FIRST;
    }
}

int PowerCube::calcPoints() const
{
    switch (getPowerUp())
    {
        case PowerUp::FORCE:
            switch (getLevel())
        {
            case Level::FIRST:
                if (m_switch)
                {
                    return 10 + 5;
                }
                else
                {
                    return 11 + 5;
                }
                break;
            case Level::SECOND:
                if (m_scale)
                {
                    return 10 + 10;
                }
                else
                {
                    return 11 + 10;
                }
                break;
            case Level::THIRD:
                if (m_scale && m_switch)
                {
                    return 20;
                }
                else if (!m_scale && !m_switch)
                {
                    return 22 + 15;
                }
                else
                {
                    return 21 + 15;
                }
                break;
            default:
                return 0;
                break;
            }
            break;
        case PowerUp::BOOST:
            switch (getLevel())
            {
            case Level::FIRST:
                if (m_switch)
                {
                    return 20 + 5;
                }
                else
                {
                    return 0 + 5;
                }
                break;
            case Level::SECOND:
                if (m_scale)
                {
                    return 20 + 10;
                }
                else
                {
                    return 0 + 10;
                }
                break;
            case Level::THIRD:
                if (m_scale && m_switch)
                {
                    return 40 + 15;
                }
                else if (!m_scale && !m_switch)
                {
                    return 0 + 15;
                }
                else
                {
                    return 20 + 15;
                }
                break;
            default:
                return 0;
                break;
            }
            break;
        case PowerUp::LEVITATE:
            switch (getLevel())
            {
            case Level::FIRST:
                return 0 + 5;
                break;
            case Level::SECOND:
                return 0 + 10;
                break;
            case Level::THIRD:
                return 30 + 15;
                break;
            default:
                return 0;
                break;
            
            }
            break;
    }
}

