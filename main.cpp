#include <iostream>
#include "math.h"
#include "SFML/Graphics.hpp"

using namespace sf;

void movePaddle1(Sprite* x);
void movePaddle2(Sprite* x);
void ballCollision(Sprite* ball,Sprite* p1,Sprite* p2,RenderWindow* window);
bool check(Sprite *x,RenderWindow *window);

float velocity=0.1f;
float movement=0.00f;
float dx=0.1f;
float sx=-0.1f;

int main() {

    sf::RenderWindow window(sf::VideoMode(700,600),"Pong",sf::Style::Close | sf::Style::Resize);
    sf::Texture textureball,texturepaddle1,texturepaddle2;
    textureball.loadFromFile("ball.png");
    texturepaddle1.loadFromFile("paddle1.png");
    texturepaddle2.loadFromFile("paddle2.png");
    Sprite ball(textureball);
    Sprite paddle1(texturepaddle1);
    Sprite paddle2(texturepaddle2);
    ball.setOrigin(ball.getGlobalBounds().width/2,ball.getGlobalBounds().height/2);
    paddle1.setOrigin(paddle1.getGlobalBounds().width/2,paddle1.getGlobalBounds().height/2);
    paddle2.setOrigin(paddle2.getGlobalBounds().width/2,paddle2.getGlobalBounds().height/2);

    paddle1.setPosition(0+paddle1.getOrigin().x,window.getSize().y/2);
    paddle2.setPosition(window.getSize().x-paddle2.getOrigin().x,window.getSize().y/2);
    ball.setPosition(window.getSize().x/2,paddle1.getPosition().y);
    
    while(window.isOpen()) {
        sf::Event evnt;
        while(window.pollEvent(evnt)) {
            if(evnt.type==evnt.Closed)
                window.close();
        }

    movePaddle1(&paddle2);
    movePaddle2(&paddle1);
    ball.move(velocity,movement);
    ballCollision(&ball,&paddle1,&paddle2,&window);
    if(check(&ball,&window)) {
        window.close();
        if(velocity==dx)
            std::cout << "Giocatore 1 ha vinto" << std::endl;
        else   
            std::cout << "Giocatore 2 ha vinto" << std::endl;
    }

    window.clear();
    window.draw(paddle1);
    window.draw(paddle2);
    window.draw(ball);
    window.display();
    }
    return 0;
}

bool check(Sprite *x,RenderWindow *window) {
    if(x->getPosition().x<0 || x->getPosition().x>window->getSize().x)
        return true;
    else 
        return false;
}

void movePaddle1(Sprite* x) {
    if(Keyboard::isKeyPressed(Keyboard::Up))
        x->move(0.0f,-0.1f);
    if(Keyboard::isKeyPressed(Keyboard::Down))
        x->move(0.0f,0.1f);
}

void movePaddle2(Sprite* x) {
    if(Keyboard::isKeyPressed(Keyboard::W))
        x->move(0.0f,-0.1f);
    if(Keyboard::isKeyPressed(Keyboard::S))
        x->move(0.0f,0.1f);
}

void ballCollision(Sprite* ball,Sprite* p1,Sprite* p2,RenderWindow* window) {

    if(ball->getPosition().y>window->getSize().y)
        movement=movement-(2*movement);
    else if(ball->getPosition().y<=0)
        movement=0-movement;

    if(ball->getGlobalBounds().intersects(p2->getGlobalBounds())) {
        float temp=fmod(((ball->getPosition().y)-(p2->getPosition().y)),(0.1));
        movement=temp;
        velocity=sx;
    }
    else if(ball->getGlobalBounds().intersects(p1->getGlobalBounds())) {
        float temp=fmod(((ball->getPosition().y)-(p1->getPosition().y)),(0.1));
        movement=temp;
        velocity=dx;
    }
        
}