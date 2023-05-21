#include <SFML/Graphics.hpp>
#include "SudokuBoard.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv){
    int emptyCells = 9;

    if(argc > 1){
        emptyCells = std::stoi(argv[1]);
    }
    sf::RenderWindow win(sf::VideoMode(800, 800), "Sudoku", sf::Style::Close);

    sf::Color backgroundColor (0, 0, 0, 255);

    SudokuBoard sudokuBoard;
    sudokuBoard.generateRandomSudoku(emptyCells);
    bool solved = false;

    while(win.isOpen()){

        // Process events

        sf::Event event;

        while(win.pollEvent(event)){
            switch(event.type){
                case sf::Event::EventType::Closed:
                    win.close();
                    break;
            }
        }


        // Game logic


        if(!solved){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                sudokuBoard.selectCell(sf::Mouse::getPosition(win));
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)){
                sudokuBoard.setNumIncell(1);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)){
                sudokuBoard.setNumIncell(2);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)){
                sudokuBoard.setNumIncell(3);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)){
                sudokuBoard.setNumIncell(4);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)){
                sudokuBoard.setNumIncell(5);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num6)){
                sudokuBoard.setNumIncell(6);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num7)){
                sudokuBoard.setNumIncell(7);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num8)){
                sudokuBoard.setNumIncell(8);
            }        
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num9)){
                sudokuBoard.setNumIncell(9);
            } 
            solved = sudokuBoard.isSolved();
            if(solved){
                sudokuBoard.selectCell(sf::Vector2i(-1, -1));
            }
        }
        else{
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)){
                sudokuBoard.generateRandomSudoku(emptyCells);
                solved = false;
            }
        }

        // Rendering

        win.clear(backgroundColor);
        win.draw(sudokuBoard);

        if(solved){
            sf::Font font;
            font.loadFromFile("../src/PTSerif-Regular.ttf");

            sf::Text tWin ("You solved!\n   [R] Reset", font);
            tWin.setCharacterSize(30);
            tWin.setPosition(sf::Vector2f(330, 50));
            tWin.setFillColor(sf::Color::White);

            win.draw(tWin);
        }
        win.display();
    }

    return 0;
}

