
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>

double getGrayscaleValue(const sf::Color &color)
{
    return color.r * 0.2989 + color.g * 0.5870 + color.b * 0.1140;
}

int main(int argc, char const** argv)
{
    const int imgWidth { 387 };
    const int imgHeight { 387 };
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(imgWidth, imgHeight), "SFML window");

    std::ofstream outf("image.txt");
    
    if(!outf)
    {
        return EXIT_FAILURE;
    }
    
    // Load a sprite to display
    sf::Image image;
    if (!image.loadFromFile("Resources/sunflower.jpg")) {
        return EXIT_FAILURE;
    }
    
    for(int y = 0; y < imgHeight; ++y)
    {
        for(int x = 0; x < imgWidth; ++x)
        {
            double gVal = getGrayscaleValue(image.getPixel(x, y));
            if (gVal >= 230.0) {
                outf << " ";
            } else if (gVal >= 200.0) {
                outf << ".";
            } else if (gVal >= 180.0) {
                outf << "*";
            } else if (gVal >= 160.0) {
                outf << ":";
            } else if (gVal >= 130.0) {
                outf << "o";
            } else if (gVal >= 100.0) {
                outf << "&";
            } else if (gVal >= 70.0) {
                outf << "8";
            } else if (gVal >= 50.0) {
                outf << "#";
            } else {
                outf << "@";
            }
        }
        outf << "\n";
    }
    
    sf::Texture imgTexture;
    imgTexture.loadFromImage(image);
    
    sf::Sprite sprite(imgTexture);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
