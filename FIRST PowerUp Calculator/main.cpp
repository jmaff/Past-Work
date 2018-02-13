//
//  main.cpp
//  FRC PowerUp Calculator
//
//  Created by 21maffetone on 1/9/18.
//  Copyright © 2018 21maffetone. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "PowerCube.hpp"

// Yes, I am aware this is insanely insecure, but oh well
const std::string pass = "frc1555";

// Predicates for std::remove_if to take out a certain column
bool removeColOne(PowerCube x)
{
    return (x.getPosition() == 0 || x.getPosition() == 1 || x.getPosition() == 2);
}

bool removeColTwo(PowerCube x)
{
    return (x.getPosition() == 3 || x.getPosition() == 4 || x.getPosition() == 5);
}

bool removeColThree(PowerCube x)
{
    return (x.getPosition() == 6 || x.getPosition() == 7 || x.getPosition() == 8);
}

// Used to sort vault in order by position for access to a specific cube
struct sort_by_pos_key
{
    inline bool operator() (const PowerCube* a, const PowerCube* b)
    {
        return (a->getPosition() < b->getPosition());
    }

    inline bool operator() (const PowerCube& a, const PowerCube& b)
    {
        return (a.getPosition() < b.getPosition());
    }
};

enum class LevitateStatus
{
    NO_CLIMB = 0, // no robots can climb - levitate is just for the points
    POINTS   = 1, // 1 bot can climb - levitate is just for the points
    RP       = 2, // 2 bots can climb - levitate is the only way to get the 1 RP!
    NONE     = 3  // all 3 bots can climb - levitate is only worth its 15 pts. for cubes
};

int main() {
    std::cout << "************************************\n";
    std::cout << "FIRST PowerUp Calculator - Team 1555\n";
    std::cout << "************************************\n";
    
    std::cout << "Password? ";
    std::string userPass;
    std::cin >> userPass;
    
    if (userPass != pass)
    {
        std::cout << "Incorrect password. Terminating program...\n";
        return EXIT_SUCCESS;
    }
    
    bool programActive = true;
    
    while (programActive)
    {
        // Get user information to calculate optimal PowerCube placement
        std::cout << "Do you have ownership of the switch? (y/n) ";
        char switchInput;
        std::cin >> switchInput;
        
        bool switchOwned = switchInput == 'y';
        
        std::cout << "Do you have ownership of the scale? (y/n) ";
        char scaleInput;
        std::cin >> scaleInput;
        
        bool scaleOwned = scaleInput == 'y';
        
        std::cout << "How many Power Cubes do you have? ";
        int cubes;
        std::cin >> cubes;
        
        std::cout << "How many robots can climb? ";
        int climbInput;
        std::cin >> climbInput;
        
        LevitateStatus levS = static_cast<LevitateStatus>(climbInput);
        
        if (levS == LevitateStatus::RP)
        {
            std::cout << "\n*LEVITATE CRUCIAL FOR RP - WILL PRIORITIZE FULL LEVITATE*\n";
        }
        
        std::cout << "\n******VAULT SCORING BREAKDOWN******\n";
        // Represents a vault FULL of PowerCubes which we use to store cubes as we check if we can "afford" them
        std::vector<PowerCube> vault;
        
        // Fill the "vault" with one PowerCube for each position
        for (int i = 0; i < 9; ++i)
        {
            PowerCube cube(i, switchOwned, scaleOwned);
            if (i % 3 == 0) {
                switch (cube.getPowerUp())
                {
                    case PowerUp::FORCE:
                        std::cout << "[FORCE]    ";
                        break;
                    case PowerUp::BOOST:
                        std::cout << "[BOOST]    ";
                        break;
                    case PowerUp::LEVITATE:
                        std::cout << "[LEVITATE] ";
                        break;
                }
            }
            
            // Set the point value of 3rd levitate cube to 15 if 3 bots can climb
            if (levS == LevitateStatus::NONE && i == 8)
            {
                cube.setPoints(15);
            }

            std::cout << cube.getPoints() << " ";
            vault.push_back(cube);
            
            // Format output
            if (i == 2 || i == 5 || i == 8) std::cout << "\n";
        }

        std::vector<PowerCube> result;
        int fullVault = 8;
        switch (levS)
        {
            case LevitateStatus::RP:
                // Only if we can afford it, force "buy" full levitate as we need it for RP
                if (cubes >= 3)
                {
                    std::sort(vault.begin(), vault.end(), sort_by_pos_key());
                    result.push_back(vault[8]);
                    vault.erase(std::remove_if(vault.begin(), vault.end(), removeColThree), vault.end());
                    cubes -= 3;
                    fullVault = 5;
                }
                break;
                
            case LevitateStatus::NONE:
                std::sort(vault.begin(), vault.end(), sort_by_pos_key());
                vault[8].setPoints(15);
                break;
            default:
                break;
        }
       
        // Sort our vault by how many points each cube is worth
        std::sort(vault.begin(), vault.end());
        
        // Iterate through this sorted list to find the highest scoring path
        for (int i = fullVault; cubes > 0 || i > 0; --i)
        {
            int cost = static_cast<int>(vault[i].getLevel()) + 1;
            
            // If we can "afford" a cube, we "buy" it since we know the list is in order of points
            if (cost <= cubes)
            {
                // "Spend" the cost of this cube and add it to our result vector
                cubes -= cost;
                result.push_back(vault[i]);
                
                // Remove the rest of this PowerUp's cubes so we don't buy two from the same one!
                if (vault[i].getPosition() < 3)
                {
                    vault.erase(std::remove_if(vault.begin(), vault.end(), removeColOne), vault.end());
                }
                else if (vault[i].getPosition() < 6)
                {
                    vault.erase(std::remove_if(vault.begin(), vault.end(), removeColTwo), vault.end());
                }
                else
                {
                    vault.erase(std::remove_if(vault.begin(), vault.end(), removeColThree), vault.end());
                }
                
                i = static_cast<int>(vault.size());
            }
            
        }
        
        
        int totalScore = 0;
        
        // Array to hold the level of each PowerUp
        int levels[] = { 0, 0, 0 };
        
        // Iterate through our result vector, add the score to our total, and add the level to the levels array
        for (auto& cube : result)
        {
            totalScore+= cube.getPoints();
            int index = static_cast<int>(cube.getPowerUp());
            int level = static_cast<int>(cube.getLevel()) + 1;
            
            levels[index] = level;
        }
        
        // Output the results to the user
        std::cout << "\n******OPTIMAL PLACEMENT BREAKDOWN******\n\n";
        std::cout << "[FORCE] ......... " << levels[0] << "\n";
        std::cout << "[BOOST] ......... " << levels[1] << "\n";
        std::cout << "[LEVITATE] ...... " << levels[2] << "\n";
        std::cout << "TOTAL SCORE ..... " << totalScore << "\n";
        
        std::cout << "\nEnter another scenario? (y/n) ";
        char activeInput;
        std::cin >> activeInput;
        
        programActive = activeInput == 'y';
    }
    
    return EXIT_SUCCESS;
}
