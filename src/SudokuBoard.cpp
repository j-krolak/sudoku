#include "SudokuBoard.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

sf::Vector2f operator*(const sf::Vector2f& a, const sf::Vector2f& b ){
    return sf::Vector2f(a.x * b.x, a.y * b.y);
}

sf::Vector2f operator*(const sf::Vector2f& a, const int b ){
    return sf::Vector2f(a.x * b, a.y * b);
}

sf::Vector2f operator-(const sf::Vector2f& a, const float b ){
    return sf::Vector2f(a.x - b, a.y - b);
}


sf::Vector2f operator+(const sf::Vector2f& a, const float b ){
    return sf::Vector2f(a.x + b, a.y + b);
}

bool operator==(const sf::Vector2i& a, const sf::Vector2i& b){
    return a.x == b.x && a.y == b.y;
}

void operator<<(std::ostream& out, const sf::Vector2i& v){
    out << "X: " << v.x << " Y: " << v.y << '\n';
}

sf::Vector2i operator-=(sf::Vector2i& a, const sf::Vector2f& b){
    a.x -= b.x;
    a.y -= b.y;
    return a;
}


SudokuBoard::SudokuBoard():
size{9,9}, cellSize{50, 50}, outlineColor{120, 120, 120, 255}, outlineThickness{3},margin{180, 180}, outlineColor2{sf::Color(255, 255, 255, 255)},
selectedColor{sf::Color{100, 200, 100, 255}}, selectedCell{-1, -1}, unselectedColor{sf::Color(0,0,0,255)}
{
    std::srand(std::time(NULL));
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            sudoku[y][x] = -1;
            activeCell[y][x] = false;
            sf::RectangleShape cell = createCell(sf::Vector2f(x, y), cellSize, outlineColor);

            cells.push_back(cell);
        }

    }

}

void SudokuBoard::selectCell(sf::Vector2i mousePos){
    selectedCell = {-1, -1};

    mousePos -= margin;
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            if( (mousePos.x > cellSize.x * x) && mousePos.x < (cellSize.x * (x+1)) &&
                (mousePos.y > (cellSize.y * y)) && (mousePos.y < cellSize.y * (y+1))){
                if(activeCell[y][x]){                
                    selectedCell = {x, y}; 
                    cells[y*size.y  + x].setFillColor(selectedColor);
                }

            }
            else if(activeCell[y][x]){
                cells[y * size.y + x].setFillColor(sf::Color(30, 30, 30, 255));
            }
            else{
                cells[y * size.y + x].setFillColor(unselectedColor);
            }
        }
    }
}

void SudokuBoard::setNumIncell(unsigned int n){
    if(selectedCell.x  < 0)
        return;

    sudoku[selectedCell.y][selectedCell.x] = n;
}

void SudokuBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    // Draw cells
    
    for(const auto & cell : cells){
        target.draw(cell);
    }

    for(int y = 0; y < size.y/3; y++){
        for(int x = 0; x < size.x/3; x++){
            sf::RectangleShape cell = createCell(sf::Vector2f(x, y), cellSize*3, outlineColor2);
            target.draw(cell);
        }

    }

    // Draw values
    sf::Font font;
    font.loadFromFile("../src/PTSerif-Regular.ttf");
    
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            if(sudoku[y][x] == -1)
                continue;

            sf::Text tValue(std::to_string(sudoku[y][x]), font);

            tValue.setCharacterSize(35);
            tValue.setFillColor(sf::Color::White);
            sf::Vector2f tValPos = cells[y*size.y + x].getPosition();
            tValPos.x += cellSize.x / 3;
            tValue.setPosition(tValPos);
            target.draw(tValue);
        }
    }
    sf::RectangleShape border(cellSize*size);
    border.setPosition(margin );
    border.setFillColor(sf::Color(0,0,0,0));
    border.setOutlineColor(outlineColor2);
    border.setOutlineThickness(outlineThickness*2);
    target.draw(border);


}

sf::RectangleShape SudokuBoard::createCell(const sf::Vector2f pos, const sf::Vector2f cSize,  const sf::Color oColor ) const{
    sf::RectangleShape cell(cSize);
    cell.setPosition(pos*cSize+margin);
    cell.setFillColor(sf::Color(0,0,0,0));
    cell.setOutlineColor(oColor);
    cell.setOutlineThickness(outlineThickness);
    return cell;
}

void SudokuBoard::generateRandomSudoku(const int empty){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            sudoku[y][x] = -1;
            activeCell[y][x] = false;
        }

    }
    generateFullBoard();
    for(int i = 0; i < empty; i++){
        int x , y;
        int tmp;
        do{

            if(countSolutions() > 1){
                sudoku[y][x] = tmp;
                activeCell[y][x] = false;
            }

            do{
                x = (std::rand() % 9) ;
                y = (std::rand() % 9) ;
            }
            while(sudoku[y][x] == -1);
            tmp = sudoku[y][x];
            sudoku[y][x] = -1;
            activeCell[y][x] = true;
        }
        while(countSolutions() > 1);
        
    }
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            if(activeCell[y][x]){
                cells[y * size.y + x].setFillColor(sf::Color(30, 30, 30, 255));
            }
            else{
                cells[y * size.y + x].setFillColor(unselectedColor);
            }
        }
    }
       
}

int SudokuBoard::countSolutions(){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            if(sudoku[y][x] != -1)
                continue;
            int ans = 0;

            for(int v=1; v <= 9; v++){
                sudoku[y][x] = v;
                if(isCorrect(x, y)){
                    ans += countSolutions();
                }
                sudoku[y][x] = -1;
            }

            return ans;
        }
    }

    return 1;
}

bool SudokuBoard::generateFullBoard(int x, int y){
    if(x >= 9){
        x = 0;
        y++;
    }

    if(y >= 9){
        return true;
    }

    if(y < 1){
        do{
            sudoku[y][x] = (std::rand() % 9) + 1;
        }
        while(!isCorrect(x, y));
        return generateFullBoard(x+1, y);
    }
    else{

        for(int i = 1; i <= 9; i++){
            sudoku[y][x] = i;
            if(!isCorrect(x, y)){
                sudoku[y][x] = -1;
                continue;
            }
            if(generateFullBoard(x+1, y)){
                return true;
            }
            sudoku[y][x] = -1;
        }
    }
    return false;

}

bool SudokuBoard::isCorrect(int x, int y){

    for(int i = 0; i < 9; i++){
        if(x==i)
            continue;
        if(sudoku[y][i] == sudoku[y][x])
            return false;
    }
                    
    for(int i = 0; i < 9; i++){
        if(y==i)
            continue;
        if(sudoku[i][x] == sudoku[y][x])
            return false;
    }

    for(int i = 3*(x/3) ; i < 3*(x/3) + 3; i++){
        for(int j = 3*(y/3) ; j < 3*(y/3) + 3; j++){
            if(y==j && x==i)
                continue;

            if(sudoku[y][x] == sudoku[j][i])
                return false;
        }
    }

    return true;
}

bool SudokuBoard::isSolved(){
    for(int y = 0; y < 9; y++){
        for(int x = 0; x < 9; x++){
            if(sudoku[y][x] == -1 || !isCorrect(x, y)){
                return false;
            }

        }
    }

    return true;
}