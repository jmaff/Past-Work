//
//  PowerCube.hpp
//  FRC PowerUp Calculator
//
//  Created by 21maffetone on 1/9/18.
//  Copyright © 2018 21maffetone. All rights reserved.
//

#ifndef PowerCube_hpp
#define PowerCube_hpp

enum class PowerUp
{
    FORCE,
    BOOST,
    LEVITATE
};

enum class Level
{
    NONE = -1,
    FIRST,
    SECOND,
    THIRD
};

class PowerCube
{
private:
    int m_position;
    bool m_switch;
    bool m_scale;
    int m_points = 0;
    
    int calcPoints() const;
    
public:
    PowerCube(int position, bool switchOwn, bool scaleOwn) : m_position(position), m_switch(switchOwn), m_scale(scaleOwn)
    {
        m_points = calcPoints();
    }
    
    int getPoints() const { return m_points; }
    int setPoints(int points) { return m_points = points; }
    void updatePoints() { m_points = calcPoints(); }
    PowerUp getPowerUp() const;
    Level getLevel() const;
    void setPosition(int position) { m_position = position; }
    int getPosition() const { return m_position; }
    
    friend bool operator< (const PowerCube &a, const PowerCube &b)
    {
        return a.getPoints() < b.getPoints();
//        if (a.getPoints() != b.getPoints()) {
//            return a.getPoints() < b.getPoints();
//        } else {
//            return static_cast<int>(a.getLevel()) > static_cast<int>(b.getLevel());
//        }
    }
};

#endif /* PowerCube_hpp */
