#include<iostream>
#include "SFML/Graphics.hpp"
using namespace std;

enum DIRECTIONS { LEFT, RIGHT, UP, DOWN }; //left is 0, right is 1, up is 2, down is 3

int main() {
    //game set up (you'll need these lines in every game)
    sf::RenderWindow screen(sf::VideoMode(950, 950), "breakout"); //set up screen
    sf::Event event; //set up event queue
    sf::Clock clock; //set up the clock (needed for game timing)
    const float FPS = 60.0f; //FPS
    screen.setFramerateLimit(FPS); //set FPS

    //load in images
    sf::Texture brick;
    brick.loadFromFile("brick 100.png");
    sf::Sprite wall;
    wall.setTexture(brick);

    int map[12][12] = {
        1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,0,0,1,
        1,0,1,0,1,0,1,0,1,1,0,1,
        1,0,0,0,1,0,1,0,0,1,0,1,
        1,0,1,1,1,0,1,0,1,1,0,1,
        1,0,1,0,0,0,1,0,1,0,0,1,
        1,0,1,0,0,1,1,0,1,0,0,1,
        1,0,1,1,0,1,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,1,0,0,1,
        1,0,1,1,0,1,1,0,0,1,0,1,
        1,0,0,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1
    };

    //player setup
    int xpos = 95;
    int ypos = 95;
    int vx = 0;
    int vy = 0;
    int radius = 35;
    sf::CircleShape dot(8);
    sf::CircleShape player(radius);
    player.setFillColor(sf::Color(250, 250, 0)); //using RGB value for color here (hex also works)
    dot.setFillColor(sf::Color(0, 0, 250));
    player.setPosition(xpos, ypos); //top left "corner" of circle (not center!)
    bool keys[] = { false, false, false, false };


    //################### HOLD ONTO YOUR BUTTS, ITS THE GAME LOOP###############################################################
    while (screen.isOpen()) {//keep window open until user shuts it down

        while (screen.pollEvent(event)) { //look for events-----------------------

            //this checks if the user has clicked the little "x" button in the top right corner
            if (event.type == sf::Event::EventType::Closed)
                screen.close();
            //KEYBOARD INPUT
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                keys[LEFT] = true;
            }
            else keys[LEFT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                keys[RIGHT] = true;
            }
            else keys[RIGHT] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                keys[UP] = true;
            }
            else keys[UP] = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                keys[DOWN] = true;
            }
            else keys[DOWN] = false;


        }//end event loop---------------------------------------------------------------

         //movePac
        if (keys[LEFT] == true)
            vx = -5;

        else if (keys[RIGHT] == true)
            vx = 5;
        else vx = 0;

        if (keys[UP] == true)
            vy = -5;

        else if (keys[DOWN] == true)
            vy = 5;

        else vy = 0;


        //RIGHT COLLISION
        if (vx > 0 &&
            //check if TOP right corner has hit
            ((map[(ypos) / 80]
                [(xpos + (radius * 2) + 5) / 80] == 1) ||
                (map[(ypos + (radius * 2) - 5) / 80]
                    [(xpos + (radius * 2) + 5) / 80] == 1))) {
            vx = 0;
            cout << "colliding RIGHT";
        }
         
        //LEFT collision
        else if (vx < 0 &&
             ((map[(ypos + 5) / 80]
                [(xpos - 5) / 80] == 1) ||
                (map[(ypos + (radius * 2)-5) / 80]
                    [(xpos - 5) / 80] == 1))) {
            vx = 0;
            cout << "colliding LEFT ";
        }
        //DOWN collision
        if (vy > 0 &&
               ((map[(ypos + (radius * 2) + 5) / 80]
                    [(xpos) / 80] == 1) ||
                (map[(ypos + (radius * 2) + 5) / 80]
                    [(xpos + (radius * 2)) / 80] == 1))) {
            vy = 0;
            cout << "colliding DOWN";
        }
        //UP collision
        else if (vy < 0 &&
               ((map[(ypos - 5) / 80]
                    [(xpos+5 ) / 80] == 1) ||
                (map[(ypos - 5) / 80]
                    [(xpos + (radius * 2)) / 80] == 1))) {
            vy = 0;
            cout << "colliding UP";
        }

        //player update position
        xpos += vx;
        ypos += vy;
        player.setPosition(xpos, ypos);


        //dots
        if (map[ypos / 80][xpos / 80] == 0)
            map[ypos / 80][xpos / 80] = -1;
        cout << xpos << ", " << ypos << endl;




        //render section-----------------------------------------
        screen.clear(); //wipes screen, without this things smear

        //draw map
        for (int rows = 0; rows < 12; rows++)
            for (int cols = 0; cols < 12; cols++) {
                if (map[rows][cols] == 1) {
                    wall.setPosition(cols * 80, rows * 80);
                    screen.draw(wall);
                }
                if (map[rows][cols] == 0) {
                    dot.setPosition(cols * 80 + 40, rows * 80 + 40);
                    screen.draw(dot);
                }
            }
        screen.draw(player); //draw player
        screen.display(); //flips memory drawings onto screen

    }//######################## end game loop ###################################################################################

    cout << "goodbye!" << endl;
} //end of main
