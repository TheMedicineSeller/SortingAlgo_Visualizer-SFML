#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>

#define WIN_DIM 1000
#define CANVAS_LENGTH 900
#define CANVAS_WIDTH 500
#define INDENT "\t"

void SwapRectangles(sf::RectangleShape &rect1, sf::RectangleShape &rect2)
{
    // float rectWidth = rect1.getSize().x;
    sf::Vector2f pos1 = rect1.getPosition();
    sf::Vector2f pos2 = rect2.getPosition();
    if (pos1.y < pos2.y)
    {
        // rect1.move(rectWidth, 0);
        // rect2.move(-rectWidth, 0);
        rect1.setPosition(pos2.x, pos1.y);
        rect2.setPosition(pos1.x, pos2.y);
    }
}

void HandleWindowEvents (sf::RenderWindow &window) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void debugRects(const std::vector<sf::RectangleShape> &rectangles)
{
    for (int i = 0; i < rectangles.size(); i++)
        std::cout << "Rectangle " << (i + 1) << ", dims : " << rectangles[i].getSize().x << " & " << rectangles[i].getSize().y << " ::Position : " << rectangles[i].getPosition().x << " & " << rectangles[i].getPosition().y <<" ::Color: " <<rectangles[i].getFillColor().toInteger() <<"\n";
}

void DrawRectangles (const std::vector<sf::RectangleShape> &Rectangles, sf::RenderWindow &window) {
    window.clear();
    for (int drawable = 0; drawable < Rectangles.size(); drawable++)
        window.draw(Rectangles[drawable]);
}

void generateRectangles(std::vector<sf::RectangleShape> &Rects, int n)
{
    Rects.reserve(n);
    int width = CANVAS_LENGTH / n;
    int y_unit = CANVAS_WIDTH / n;
    float start = (WIN_DIM - CANVAS_LENGTH) / 2;

    for (int i = 0; i < n; i++)
    {
        sf::RectangleShape bar;
        float height = (i + 1) * y_unit;
        bar.setSize(sf::Vector2f(width, height));
        bar.setPosition(start + i * width, (WIN_DIM >> 1) + (CANVAS_WIDTH >> 1) - height);

        bar.setFillColor(sf::Color::White);
        bar.setOutlineThickness(-1);
        bar.setOutlineColor(sf::Color::Black);
        Rects.emplace_back(bar);
    }
}

void shuffleRectangles(std::vector<sf::RectangleShape> &Rects)
{
    int width = Rects[0].getSize().x;
    sf::RectangleShape temp;
    for (int itr = 0; itr < Rects.size(); itr++)
    {
        int randidx = rand() % Rects.size();
        sf::Vector2f pos1 = Rects[itr].getPosition();
        sf::Vector2f pos2 = Rects[randidx].getPosition();
        if (pos1.x != pos2.x) {
            Rects[itr].setPosition(pos2.x, pos1.y);
            Rects[randidx].setPosition(pos1.x, pos2.y);

            temp = Rects[itr];
            Rects[itr] = Rects[randidx];
            Rects[randidx] = temp;
        }
    }
}

void BubbleSort (std::vector<sf::RectangleShape> &Rects, sf::RenderWindow &window) {
    for (int i = 0; i < Rects.size()-1; i ++) {
        for (int j = i+1; j < Rects.size(); j ++) {
            
            HandleWindowEvents(window);
            Rects[i].setFillColor(sf::Color::Red);
            Rects[j].setFillColor(sf::Color::Red);
            sf::RectangleShape temp;

            sf::Vector2f pos_i = Rects[i].getPosition();
            sf::Vector2f pos_j = Rects[j].getPosition();
            if (pos_i.y < pos_j.y) {
                Rects[i].move(pos_j.x - pos_i.x, 0);
                Rects[j].move(pos_i.x - pos_j.x, 0);

                DrawRectangles(Rects, window);
                window.display();
                Rects[i].setFillColor(sf::Color::White);
                Rects[j].setFillColor(sf::Color::White);

                temp = Rects[i];
                Rects[i] = Rects[j];
                Rects[j] = temp;
            } 
            else {
                DrawRectangles(Rects, window);
                window.display();
                Rects[i].setFillColor(sf::Color::White);
                Rects[j].setFillColor(sf::Color::White);
            }
        }
        Rects[i].setFillColor(sf::Color::Green);
        window.draw(Rects[i]);
    }
    Rects.back().setFillColor(sf::Color::Green);
    DrawRectangles(Rects, window);
    window.display();
}

void SelectionSort (std::vector<sf::RectangleShape> &Rects, sf::RenderWindow &window) {
    for (int i = 0; i < Rects.size(); i ++) {
        int min_idx = i;
        for (int j = i+1; j < Rects.size(); j ++) {
            HandleWindowEvents(window);

            Rects[j].setFillColor(sf::Color::Red);
            if (Rects[j].getPosition().y > Rects[min_idx].getPosition().y) {
                min_idx = j;
                Rects[min_idx].setFillColor(sf::Color::Yellow);
            }
            DrawRectangles(Rects, window);
            window.display();
            Rects[j].setFillColor(sf::Color::White);
        }
        if (min_idx != i) {
            Rects[min_idx].setFillColor(sf::Color::White);
            
            sf::Vector2f pos_i = Rects[i].getPosition();
            sf::Vector2f pos_min = Rects[min_idx].getPosition();
            Rects[i].move(pos_min.x - pos_i.x, 0);
            Rects[min_idx].move(pos_i.x - pos_min.x, 0);

            sf::RectangleShape temp = Rects[i];
            Rects[i] = Rects[min_idx];
            Rects[min_idx] = temp;
        }
        Rects[i].setFillColor(sf::Color::Green);
        window.draw(Rects[i]);
    }
    DrawRectangles(Rects, window);
    window.display();
}

void InsertionSort (std::vector<sf::RectangleShape> &Rects, sf::RenderWindow &window) {
    // Implement Inserion sort
}

int main()
{
    srand(time(0));
    int n;
    char inpKey, key;
    std::cout<< "\n" INDENT"-------------------------------------------------\n";
    std::cout<< INDENT"|\t\t!!SORT VISUALIZER!!\t\t|\n";
    std::cout<< INDENT"-------------------------------------------------\n\n";

    std::cout << INDENT"Enter the no of rectangles to generate: ";
    std::cin >> n;

    std::vector<sf::RectangleShape> rectangles;
    generateRectangles(rectangles, n);
    sf::RenderWindow window(sf::VideoMode(WIN_DIM, WIN_DIM), "Visualize sorts");
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        HandleWindowEvents(window);

        window.clear();
        for (int i = 0; i < rectangles.size(); i ++) {
            rectangles[i].setFillColor(sf::Color::White);
            window.draw(rectangles[i]);
        }
        window.display();
        std::cout << "\n" INDENT"Press s to shuffle, q to quit, none to continue without shuffle: ";
        std::cin>> key;
        if (key == 's') {
            shuffleRectangles(rectangles);
            DrawRectangles(rectangles, window);
            window.display();
        }
        else if (key == 'q')
            break;
        std::cout<< INDENT"Enter sorting algorithm to visualize (b->bubble, s->selection, i->insertion):";
        
        std::cin>> inpKey;
        if (inpKey == 'b') {
            BubbleSort(rectangles, window);
        } else if (inpKey == 's') {
            SelectionSort(rectangles, window);
        } else if (inpKey == 'i') {
            InsertionSort(rectangles, window);
        } else {
            std::cout << INDENT"Entered Invalid valid option :: Try again...";
            continue;
        }

        std::cout<<"\n" INDENT"Sort Done, ENTER to continue...";
        std::cin.sync();
        std::cin.get();
    }
    return 0;
}