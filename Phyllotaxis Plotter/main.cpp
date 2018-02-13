//
// Draws points following the pattern of phyllotaxis, the naturally occuring phenomeon found in the seeds,
// leaves, etc. of plants (inspired by video from The Coding Train on YouTube, where he creates this in
// p5.js)
// My first SFML "project"!
//

#include <SFML/Graphics.hpp>
#include <cmath> // for cos() and sin()
#include <cassert>
#include <iostream>

// hsv to sf::Color (RGBa) (i didn't write this was too lazy) for easily coloring the points
sf::Color hsv(int hue, float sat, float val)
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

// c++ is mean and calculates sin and cos in terms of radians
double toRadians(double degrees)
{
    return (degrees * M_PI) / 180;
}

int main()
{
    
    // define width and height for window
    const int height { 600 };
    const int width { 600 };
    
    int n { 0 }; // the nth dot drawn, counting from the center
    int c { 7 }; // scale factor
    
    // I will draw my points to a render texture since I clear the window each frame (as reccomended by SFML)
    sf::RenderTexture renderTexture;
    assert(renderTexture.create(width, height)); // error if creation fails
    
    // create and launch window object
    sf::RenderWindow window (sf::VideoMode(width, height), "Phyllotaxis");
    window.setFramerateLimit(50); // unlimited is a bit too fast
    
    while (window.isOpen())
    {
        // handle events (just close)
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        // formulas from alorithmicbotany.org paper (polar coordiantes)
        double a = toRadians(n * 137.5); // cos() and sin() take radians, not degrees
        double r = c * sqrt(n);
        
        // convert from polar to cartesian coordinates and account for origin being at top left
        double x = r * cos(a) + width / 2;
        double y = r * sin(a) + height / 2;
        
        sf::CircleShape point(4);
        // base color hue off of n-vale and loop back (modulus)
        point.setFillColor(hsv(n % 256, 255, 255));
        point.setPosition(x, y);
        
        renderTexture.draw(point);
        renderTexture.display();
        
        // create texture from renderTexture and construct a sprite from it
        const sf::Texture& texture = renderTexture.getTexture();
        sf::Sprite sprite(texture);
        
        window.clear(sf::Color::Black);
        // draw everything
        window.draw(sprite);
        
        ++n; // increment our n-value (ordering number)
        
        window.display();
    }
    
    return 0;
}
