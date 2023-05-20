#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics.hpp>
#include <vector>


class SudokuBoard : public sf::Drawable{
public:
    SudokuBoard();
    void selectCell(sf::Vector2i mousePos);
    void setNumIncell(unsigned int n);
    void generateRandomSudoku(const int empty = 5);
    bool isSolved();
private:
    sf::Vector2f size;
    sf::Color outlineColor;
    sf::Color outlineColor2;
    sf::Color selectedColor;
    sf::Color unselectedColor;

    float outlineThickness;
    sf::Vector2f cellSize;
    sf::Vector2f margin;
    std::vector<sf::RectangleShape> cells;
    sf::Vector2i selectedCell;
    int sudoku[9][9];
    bool activeCell[9][9];

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::RectangleShape createCell(const sf::Vector2f pos, const sf::Vector2f cSize, const sf::Color oColor) const;
    int countSolutions();
    bool generateFullBoard(int x = 0, int y = 0);
    bool isCorrect(int x, int y);


};