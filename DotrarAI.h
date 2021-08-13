//
// Created by Dre on 6/6/2021.
//

#ifndef FLOODIT_AI_DOTRAR_H
#define FLOODIT_AI_DOTRAR_H


#include <vector>
#include "Player.h"
#include "BoardSimple.h"

typedef std::tuple<int,int> Coord;
typedef std::vector<Coord> ListOfCoords;


class DotrarAI : public Player
{
private:

    BoardSimple *gameboard;

    // List of neighbouring
    ListOfCoords neighbours;

    // get a vector of neighbouring colours, offColour true will return the neighbours not on target colour 
    ListOfCoords findNeighboursOfColour(Coord coord, int colour, bool offColour = false);
    
    // return colour
    int getColour(Coord coord);

    //private function to eplore connecting spaces (breadth first)
    // and build a list of off-coloured blocks. (_edges)
    void exploreSurroundings(uint32_t startx, uint32_t starty, int targetColour, std::vector<uint64_t>);

public:
    DotrarAI(std::string n = "Dotrar AI") : Player(n)
    { 
    
        displayBoard = false; 
    }

    // public interface that will be called by the system
    bool getMove(BoardSimple board, int &colour, int &row, int &col);

};


/* == DotrarAI::getMove ==
 * Chooses its moved based on the biggest attached segment of colour that is attached to the first colour.
 */
bool DotrarAI::getMove(BoardSimple board, int &colour, int &row, int &col)
{
    this->gameboard = &board;

    int colour = board.grid[0][0];

    Coord max_position = std::make_tuple(0,0); 
    int max_size = 0;
    int target_colour = colour;

    //explore our surroundings, get a list of edge nodes
    ListOfCoords neighbours = findNeighboursOfColour(max_position,colour, true);

    for (Coord& neighbour : neighbours ) {
        int col = getColour(neighbour);
        ListOfCoords thisSegment = findNeighboursOfColour(neighbour, col);
        //find the biggest.
        if (thisSegment.size() > max_size){
            max_size = thisSegment.size();
            target_colour = col;
        }
    }


    // return cases
    row = 0;
    col = 0;
    colour = target_colour;
    return true;
}

ListOfCoords DotrarAI::findNeighboursOfColour(Coord coord, int colour, bool offColour){
    /*
     * STarting from coord, work around and find other items that are of color
     *
     */

    ListOfCoords ret;


}

void DotrarAI::exploreSurroundings(BoardSimple *board, int startx, int starty, int targetColour)
{

    addOffColour(board,startx-1,starty-1);
    addOffColour(board,startx-1,starty);
    addOffColour(board,startx-1,starty+1);
    
    addOffColour(board,startx,starty-1);
    addOffColour(board,startx,starty);
    addOffColour(board,startx,starty+1);
    
    addOffColour(board,startx+1,starty-1);
    addOffColour(board,startx+1,starty);
    addOffColour(board,startx+1,starty+1);
    
}
void DotrarAI::addOffColour(BardSimple *board, uint32_t x, uint32_t y)
{
    if (x < 0 || y < 0)
        return;
   
    uint64_t coord =  (x<<32)|y;
   
    //check if we already have it, and return early
    if( std::find(this->_mapping.begin(), this->_mapping.end(), coord) != this->_mapping.end())
        return;

    if (board->grid[x][y] == this->_targetColour){
        this->_mapping.push_back(coord);
    }
}

int DotrarAI::getBiggestNeighbour()
{
    for(uint64_t& coord: this->_mapping){
        int x = (coord & 0xFFFF0000)>>32;
        int y = (coord & 0x0000FFFF);
        //this target:
        int target_colour = this->board.grid[x][y];
    
        std::vector
        
    }
}



#endif //FLOODIT_AI_BASICAI_H
