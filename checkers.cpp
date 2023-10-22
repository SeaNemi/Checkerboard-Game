/***************************
 ** File:    checkers.cpp
 ** Project: CMSC 341, proj0, Spring 2023
 ** Author:  William Whatley
 ** Date:    2/11/2023
 ** Section: Marron
 ** Email:   w59@umbc.edu
 **
 ** This file is checkers.cpp and initializes the functions provided in checkers.h for the
 ** Checkers class.
 **
 ** All functions were created by William Whatley excluding dumpGame, whch was provided in the project
*****************************/

#include "checkers.h"

//Checkers default constructor
//Creates an empty object with everything initialized to 0, none, and null
Checkers::Checkers(){
    m_numRows = 0;
    m_numColumns = 0;
    m_whiteDisks = 0;
    m_blackDisks = 0;
    m_game = nullptr;
    m_currPlayer = NONE;
}

//Checkers overloaded constructor
//Checks to ensure that the rows and columns are valid, and if so a proper object is created
//If not, an empty object is created
Checkers::Checkers(int rows, int columns){
    //if statement ensures that the rows and columns are valid
    //The board must be square, column must be even, and the board size should at least be 8x8
    if ((rows >= DEFBOARDSIZE) && (columns >= DEFBOARDSIZE) && (columns % 2 == 0) && (rows == columns)){
        m_numRows = rows;
        m_numColumns = columns;
        m_whiteDisks = 0;
        m_blackDisks = 0;
        m_currPlayer = NONE;

        //m_game created. A new array of CELL pointers is created
        m_game = new CELL*[m_numRows];
        //for loop fills each m_game CELL array. Each array points to a cell array, which make up the columns
        for (int i = 0; i < m_numRows; i++){
            m_game[i] = new CELL[m_numColumns];
        }
    }
    //if all conditions are not met, an empty object is created
    else{
        m_numRows = 0;
        m_numColumns = 0;
        m_whiteDisks = 0;
        m_blackDisks = 0;
        m_game = nullptr;
        m_currPlayer = NONE;
    }
}

//Checkers destructor
//calls upon clear to destroy the game board
Checkers::~Checkers(){
    clear();
}

//clear
//Deletes the object and resets it to an empty object
void Checkers::clear(){
    if (m_game != nullptr){
        //for loop deletes each array that m_game[] was dynamically pointing to
        for (int i = 0; i < m_numRows; i++){
            delete[] m_game[i];
        }
        delete[] m_game; //m_game array itself is deleted and no memory is dynamically allocated
        m_game = nullptr; //m_game reset to nullptr
    }

    //all other members are reset and initialized to zero, as seen in an empty object
    m_numRows = 0;
    m_numColumns = 0;
    m_currPlayer = NONE;
    m_whiteDisks = 0;
    m_blackDisks = 0;
}

//initBoard
//This function creates the checkers game board itself
void Checkers::initBoard(){
    //if statement verifies that the object is not empty and legitimate by checking m_game[]
    if (m_game != nullptr){ 
        //for loop and nested for loop go through arrays and determine if the square is black or white   
        for (int i = 0; i < m_numColumns; i++){
            for (int j = 0; j < m_numColumns; j++){
                //if statement verifies which color the square is
                //the gaame board starts off at 0x0 with a white square, and that is consistent
                if ((i % 2 == 0) && (j % 2 == 0)){
                    m_game[i][j] = WCELL;
                }
                //the suare beneath a white is always black, which this if statement is for
                else if ((i % 2 != 0) && (j % 2 == 0)){
                    m_game[i][j] = BCELL;
                }
                //the square next to a white square is black, which is done in this statement
                else if ((i % 2 == 0) && (j % 2 != 0)){
                    m_game[i][j] = BCELL;
                }
                //a square diagonal from a white square is also white, which is in this else statement
                else{
                    m_game[i][j] = WCELL;
                }
            } 
        }
    }
}

//initGame
//This functions creates the gameboard and sets up the pieces of the chess board
void Checkers::initGame(){
    //if statement verifies that m_game was created and that the chess board was properly set
    if ((m_game != nullptr) && (m_game[0][0] == WCELL)){
        //numDisks and diskIterator declared and initialized
        int numDisks = m_numColumns * 3/2; //formula given for amount of pieces to be set on the board
        int diskIterator = numDisks;

        //both m_whiteDisks and m_blackDisks are updated to the amount of disks on the board
        m_whiteDisks = numDisks;
        m_blackDisks = numDisks;

        //for statement places the white pieces on the checker board
        for (int i = 0; i < m_numRows; i++){
            for (int j = 0; j < m_numColumns; j++){
                //if diskIterator is greater than 0, it means there's more pieces to be set on the board
                if (diskIterator > 0){
                    //if statement checks if i is odd or even, as that changes where the pieces are placed
                    if (i % 2 == 0){
                        //if statement verifies that j is odd, as that's where the piece is placed
                        //If even, it is skipped
                        if (j % 2 != 0){
                            m_game[i][j] = WDISK;
                            --diskIterator; //diskIterator decremented so it's known there's one less piece to place on board
                        }
                    }
                    else{
                        //if statement verifies that j is even. If it is odd, no pieces are set
                        if (j % 2 == 0){
                            m_game[i][j] = WDISK;
                            --diskIterator;
                        }
                    }
                }
            }
        }

        diskIterator = numDisks; //disk iterator reset for black pieces
        
        //for loop acts as a reverse iterator and adds black disks to the board
        //for loop i starts at m_numRows - 1 to properly match the indexing
        for (int i = (m_numRows - 1); i > 0; --i){
            for (int j = 0; j < m_numColumns; j++){
                //if statement verifies that there are still pieces to be placed on the board
                if (diskIterator > 0){
                       //if statement checks if i is odd or even, as that changes where the pieces are placed
                    if (i % 2 == 0){
                        //if statement verifies that j is odd, as that's where the piece is placed
                        //If even, it is skipped
                        if (j % 2 != 0){
                            m_game[i][j] = BDISK;
                            --diskIterator;
                        }
                    }
                    else{
                        //if statement verifies that j is even. If it is odd, no pieces are set
                        if (j % 2 == 0){
                            m_game[i][j] = BDISK;
                            --diskIterator;
                        }
                    }
                }
            }
        }
        //current player set to black, as the starting player
        m_currPlayer = BPLAYER;
    }
}

//play
//play checks and sees if the destination is valid, and if it is the piece is moved, and if not the movement is invalid
bool Checkers::play(pair<int,int> origin, pair<int,int> destination){
    bool pieceMoved = false;


    //if white disks or black disks equal zero, then the game is over
    if ((m_whiteDisks == 0) || (m_blackDisks == 0)){
        cout << "No play can be made, as there are no remaining pieces" << endl;
        return pieceMoved;
    }
    //else if checks to make sure that the object isn't empty
    else if (m_game == nullptr){
        cout << "Empty object, no play may be made" << endl;
        return pieceMoved;
    }
    //else then ensures play is correct
    else{
        //if statement verifies that the origin and destination are valid
        //less than m_numRows and m_numColumns used as index is one less than the number
        if ((origin.first >= 0) && (origin.second >= 0) && (origin.first < m_numRows) && (origin.second < m_numColumns) && (destination.first >= 0) && (destination.second >= 0) && (destination.first < m_numRows) && (destination.second < m_numColumns)){
            //if statement verifies that the player doing the movement is valid
            if (m_currPlayer == WPLAYER){
                //if statement verifies WPLAYER is moving a white piece, and not moving an incorrect one
                if (m_game[origin.first][origin.second] == WDISK){
                    pieceMoved = whiteMove(origin, destination, WDISK);
                }
                else if (m_game[origin.first][origin.second] == WKING){
                    pieceMoved = whiteMove(origin, destination, WKING);
                }
                //if WPLAYER is not moving a WDISK or WKING, then they aren't moving a valid piece
                else{
                    cout << "WPLAYER playing, incorrect disk choice" << endl;
                    pieceMoved = false;
                }
            }
            //else if statement checks to ensure BPLAYER is moving a black piece
            else if (m_currPlayer == BPLAYER){
                //if statements below ensure a BDISK or a BKING is being moved
                if (m_game[origin.first][origin.second] == BDISK){
                    pieceMoved = blackMove(origin, destination, BDISK);
                }
                else if (m_game[origin.first][origin.second] == BKING){
                    pieceMoved = blackMove(origin, destination, BKING);
                }
                else{
                    cout << "BPLAYER playing, incorrect disk choice" << endl;
                    pieceMoved = false;
                }
            }
            //if neither BPLAYER or WPLAYER is moving the piece, then NONE, meaning the move is invalid
            else{
                cout << "Nobody playing, no pieces may be moved" << endl;
                pieceMoved = false;
            }
        }
        else{
            pieceMoved = false;
        }
    }
    //if statement verifies if pieceMoved was turned to true, and if so it changes the board
    if (pieceMoved){
        //since all pieces are on BCELLs, if the piece was moved, then the original spot is turned back to BCELL
        m_game[origin.first][origin.second] = BCELL;
        
        //if statement checks to ensure the game is not over
        if ((m_whiteDisks != 0) && (m_blackDisks != 0)){
            //if statement changes which player is currently playing
            if(m_currPlayer == BPLAYER){
                m_currPlayer = WPLAYER;
            }
            else{
                m_currPlayer = BPLAYER;
            }

            //if statement checks if the DISK should be upgraded. This is for when it reaches the end
            if ((destination.first == (m_numRows - 1)) && (m_game[destination.first][destination.second] == WDISK)){
                m_game[destination.first][destination.second] = WKING;
                return true;
            }
            else if ((destination.first == 0) && (m_game[destination.first][destination.second] == BDISK)){
                m_game[destination.first][destination.second] = BKING;
                return true;
            }
            else{
                return true;
            }
        }
        else{
            //string winningPlayer created
            string winningPlayer;

            //string changes depending on which player won
            if (m_currPlayer == WPLAYER){
                winningPlayer = "WPLAYER";
            }
            else{
                winningPlayer = "BPLAYER";
            }
            cout << "Game is over, congrats " << winningPlayer << " on your victory!!" << endl;
            return true;
        }
    }
    else{
        cout << "Invalid movement" << endl;
        return false;
    }
}

//setGameState
//Changes the game board to how the array sent has it
void Checkers::setGameState(CELL game[], int n, PLAYER player){
    //inital if statement checks to ensure that the object is not empty
    if (m_game != nullptr){
        //ints currRow and currColumn declared and are used for tracking current index of m_game in the for loop
        int currRow;
        int currColumn;
        //if statement ensures that n is the same size as m_numRows
        //has to be square rooted as n is the size of the whole board
        if ((sqrt(n) != m_numRows) || (sqrt(n) != m_numColumns)){
            cout << "Invalid conversion, cannot change file" << endl;
        }
        else{
            //m_currPlayer is set to the current player sent
            m_currPlayer = player;
            
            //if m_currPlayer == NONE, it is assumed that BPLAYER is playing
            if (m_currPlayer == NONE){
                m_currPlayer = BPLAYER;
            }

            //for loop goes through and checks every value for game[i] to see if it is eligble to replace m_game
            for (int i = 0; i < n; i++){
                //currRow is set to i/sqrt(n) to indicate which index it is on, and since ints automatically floor, it will go to the lowest index
                currRow = i / sqrt(n);
                //currColumn is i minus currRow times sqrt(n), as it corresponds to the index provided
                currColumn = i - (currRow * sqrt(n));

                //if game[i] is empty or if it is a WCELL, it is ignored since nothing changes
                if (game[i] == "" || (game[i] == WCELL)){
                    //if so, it is just ignored
                }
                //if m_game is on a WCELL and game[i] is a piece, then it is overruled since a piece cannot be on a white cell
                else if ((m_game[currRow][currColumn] == WCELL) && ((game[i] == WKING) || (game[i] == BKING) || (game[i] == BDISK) || (game[i] == WDISK))){
                    cout << "Cannot place pieces on white spaces" << endl;
                }
                //cannot swap layout, so if m_game is WCELL and game is BCELL nothing will change
                else if (((game[i] == BCELL) && (m_game[currRow][currColumn] == WCELL))){
                    cout << "Cannot change layout of the board" << endl;
                }
                else{
                    //first if statement checks if the cell being replaced isn't a black cell, and if it is, the piece on it is removed
                    if (m_game[currRow][currColumn] != BCELL){
                        if (m_game[currRow][currColumn] == WKING){
                            --m_whiteDisks;
                        }
                        else if (m_game[currRow][currColumn] == WDISK){
                            --m_whiteDisks;
                        }
                        //if white piece isn't removed, then a black piece is
                        else{
                            --m_blackDisks;
                        }
                    }

                    //second if statement checks if game[i] equals a piece, then it is added on the board and a color's disk number is changed accordingly
                    if (game[i] == WKING){
                        m_game[currRow][currColumn] = WKING;
                        m_whiteDisks++;
                    }
                    else if (game[i] == BKING){
                        m_game[currRow][currColumn] = BKING;
                        m_blackDisks++;
                    }
                    else if (game[i] == WDISK){
                        m_game[currRow][currColumn] = WDISK;
                        m_whiteDisks++;
                    }
                    else if (game[i] == BDISK){
                        m_game[currRow][currColumn] = BDISK;
                        m_blackDisks++;
                    }
                    //if it is not a piece, then it is simply a BCELL, and left as is
                    else{
                        m_game[currRow][currColumn] = BCELL;
                    }
                }
            }
        }
    }
    else{
        cout << "Empty object, gameState is nonexistent" << endl;
    }
}

//reportLostDisks
//The amount of lost disks by both WPLAYER and BPLAYER are shown
void Checkers::reportLostDisks(){
    int numDisks = m_numColumns * 3/2; //formula given for amount of pieces to be set on the board
    cout << "White player lost disks: " << (numDisks - m_whiteDisks) << endl;
    cout << "Black player lost disks: " << (numDisks - m_blackDisks) << endl;
}

//dumpGame
//displays the game board in its current state
void Checkers::dumpGame(){
     if (m_numRows > 0 && m_numColumns > 0 && m_game != nullptr){
        cout << "  ";
        for (int k=0;k<m_numColumns;k++){
            cout << k << " ";
        }
        cout << endl;
        for (int i=1;i <= m_numRows;i++){
            cout << i-1 << " ";
            for (int j=1;j<=m_numColumns;j++){
                cout << m_game[i-1][j-1];
            }
            cout << endl;
        }
        cout << endl;
    }
}

//whiteMove
//private function dedicated to determining if a white move is valid. If it is, it returns true. If not, false
bool Checkers::whiteMove(pair<int,int> origin, pair<int,int> destination, CELL piece){
    //the first if statement verifies that the location trying to be moved to isn't blocked by another piece
    if ((m_game[destination.first][destination.second] != WDISK) && (m_game[destination.first][destination.second] != WKING) && (m_game[destination.first][destination.second] != BDISK) && (m_game[destination.first][destination.second] != BKING)){
        //the third if statements check if the piece is a WKING or a WDISK and determines valid moves based on that
        
        /*WKING MOVE*/

        if (piece == WKING){
            //the first set of if statements check solo moves with no pieces being jumped
            //the king can move both forwards and backwards, and the valid actions reflect that
            //the first if statement verifies moving up OR down one row, indicating no piece being jumped

            /*WKING SINGLE MOVE*/

            if ((destination.first == (origin.first + 1)) ||(destination.first == (origin.first - 1))){
                //if statements verify that the movement was valid
                //if statement verifies movement one column to the right
                if (destination.second == (origin.second + 1)){
                    m_game[destination.first][destination.second] = WKING;
                    return true;
                }
                //else if verifies movement one column to the left
                else if (destination.second == (origin.second - 1)){
                    m_game[destination.first][destination.second] = WKING;
                    return true;
                }
                //if the column is not one to the left or one to the right, then the move is invalid
                else{
                    cout << "Second destination variable incorrect ensure it is one to the right or left" << endl;
                    return false;
                }
            }

            /*WKING JUMP DOWN*/

            //the first statement checks to see if a piece was jumped two rows up
            else if ((destination.first == (origin.first + 2))){
                //if statements below check that a disk was jumped either two columns to the left or two the right
                if (destination.second == (origin.second + 2)){
                    //if statement checks if a piece was jumped two columns to the right and ensures a disk is jumped
                    if (m_game[origin.first + 1][origin.second + 1] == BDISK){
                        --m_blackDisks;
                        m_game[origin.first + 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = WKING;
                        return true;
                    }
                    //else if ensures a KING was jumped
                    else if (m_game[origin.first + 1][origin.second + 1] == BKING){
                        --m_blackDisks;
                        m_game[origin.first + 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = WKING;
                        return true;
                    }
                    //if nothing was jumped, then the move is invalid and false is returned
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else if checks if a piece was jumped two columns to the left
                else if (destination.second == (origin.second - 2)){
                    //if statement checks that a DISK was jumped
                    if (m_game[origin.first + 1][origin.second - 1] == BDISK){
                        --m_blackDisks;
                        m_game[origin.first + 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = WKING;
                        return true;
                    }
                    //else if checks that a KING was jumped
                    else if (m_game[origin.first + 1][origin.second - 1] == BKING){
                        --m_blackDisks;
                        m_game[origin.first + 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = WKING;
                        return true;
                    }
                    //if nothing is returned, then the move is invalid and false is returned
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else checks that the column is two away exactly, if not the move is invalid
                else{
                    cout << "Move is invalid. Ensure the second destination is valid" << endl;
                    return false;
                }
            }

            /*WKING JUMP DOWN*/

            //else statement verifies if a piece was jumped if the destination is two rows down
            //if no piece is jumped, it is returned as false
            else if (destination.first == (origin.first - 2)){
                //if statement checks to ensure the destination is two away from the original column
                if (destination.second == (origin.second + 2)){
                    //if statement checks to see if a BDISK or BKING was jumped, if so it is 
                    if (m_game[origin.first - 1][origin.second + 1] == BDISK){
                        --m_blackDisks;
                        m_game[origin.first - 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = WKING;
                        return true;
                    }
                    //else if is for eliminating the king
                    else if (m_game[origin.first - 1][origin.second + 1] == BKING){
                        --m_blackDisks;
                        m_game[origin.first - 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = WKING;
                        return true;
                    }
                    //if nothing is jumped, then the location is invalid and is returned false
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else statement checks and see if the column 2 blocks away had a piece jump
                else if (destination.second == (origin.second - 2)){
                    //if statement checks that a DISK was jumped and eliminates it
                    if (m_game[origin.first - 1][origin.second - 1] == BDISK){
                        --m_blackDisks;
                        m_game[origin.first - 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = WKING;
                        return true;
                    }
                    //else statement verifies that a BKING was jumped
                    else if (m_game[origin.first - 1][origin.second - 1] == BKING){
                        --m_blackDisks;
                        m_game[origin.first - 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = WKING;
                        return true;
                    }
                    //if neither is true, false is returned
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else, if the destination second is not two columns away exactly, then the move is invalid
                else{
                    cout << "Move invalid. The second destination is invalid" << endl;
                    return false;
                }
            }
            //if none of the conditions above are satisifed, then the move is entirely invalid and false is returned
            else{
                cout << "Destination or origin makes this move invalid" << endl;
                return false;
            }
        }


        /*WDISK START*/

        //the else statement checks for valid movements for the WDISK piece
        //WDISK has more limited movement as it cannot go backwards
        else{

            /*WDISK MOVE ONE DOWN*/

            //if statement checks movement one down
            if (destination.first == (origin.first + 1)){
                //if statement verifies movement to the right is valid
                if (destination.second == (origin.second + 1)){
                    m_game[destination.first][destination.second] = WDISK;
                    return true;
                }
                //else if verifies movement to the left
                else if (destination.second == (origin.second - 1)){
                    m_game[destination.first][destination.second] = WDISK;
                    return true;
                }
                //if the movement is not one column to the left or right, then the move is invalid
                else{
                    cout << "Movement invalid. Piece must move either one to the right or one to the left" << endl;
                    return false;
                }
            }

            /*WDISK JUMP DOWN*/

            //else statement verifies if a piece was jumped if the destination is two rows down
            //if no piece is jumped, it is returned as false
            else if (destination.first == (origin.first + 2)){
                //if statement checks to ensure the destination is two away from the original column
                if (destination.second == (origin.second + 2)){
                    //if statement checks to see if a BDISK or BKING was jumped, if so it is 
                    if (m_game[origin.first + 1][origin.second + 1] == BDISK){
                        --m_blackDisks;
                        m_game[origin.first + 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = WDISK;
                        return true;
                    }
                    //else if is for eliminating the king
                    else if (m_game[origin.first + 1][origin.second + 1] == BKING){
                        --m_blackDisks;
                        m_game[origin.first + 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = WDISK;
                        return true;
                    }
                    //if nothing is jumped, then the location is invalid and is returned false
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else statement checks and see if the column 2 blocks away had a piece jump
                else if (destination.second == (origin.second - 2)){
                    //if statement checks that a DISK was jumped and eliminates it
                    if (m_game[origin.first + 1][origin.second - 1] == BDISK){
                        --m_blackDisks;
                        m_game[origin.first + 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = WDISK;
                        return true;
                    }
                    //else statement verifies that a BKING was jumped
                    else if (m_game[origin.first + 1][origin.second - 1] == BKING){
                        --m_blackDisks;
                        m_game[origin.first + 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = WDISK;
                        return true;
                    }
                    //if neither is true, false is returned
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else, if the destination second is not two columns away exactly, then the move is invalid
                else{
                    cout << "Move invalid, ensure that your destination is two away" << endl;
                    return false;
                }
            }
            //if none of the conditions above are satisifed, then the move is entirely invalid and false is returned
            else{
                cout << "Destination or Origin is invalid" << endl;
                return false;
            }
        }
    }
    else{
        cout << "Invalid Piece Move" << endl;
        return false;
    }
}

//blackMove
//private function dedicated to determining if a black move is valid. If it is, it returns true. If not, false
bool Checkers::blackMove(pair<int,int> origin, pair<int,int> destination, CELL piece){ 
    //the first if statement verifies that the location trying to be moved to isn't blocked by another \piece
    if ((m_game[destination.first][destination.second] != BDISK) && (m_game[destination.first][destination.second] != BKING) && (m_game[destination.first][destination.second] != WDISK) && (m_game[destination.first][destination.second] != WKING)){
        //the second if statement verifies that a black piece is not on the location desired
        //the third if statements check if the piece is a BKING or a BDISK and determines valid moves based on that
        if (piece == BKING){
            //the first set of if statements check solo moves with no pieces being jumped
            //the king can move both forwards and backwards, and the valid actions reflect that

            /*BKING SINGLE MOVE*/

            //the first if statement verifies moving up one row
            if ((destination.first == (origin.first + 1)) || destination.first == (origin.first - 1)){
                //if statements verify that the movement was valid
                //if statement verifies movement one column to the right
                if (destination.second == (origin.second + 1)){
                    m_game[destination.first][destination.second] = BKING;
                    return true;
                }
                //else if verifies movement one column to the left
                else if (destination.second == (origin.second - 1)){
                    m_game[destination.first][destination.second] = BKING;
                    return true;
                }
                //if the column is not one to the left or one to the right, then the move is invalid
                else{
                    cout << "Second destination variable incorrect" << endl;
                    return false;
                }
            }

            
            /*BKING JUMP*/

            //the if statements below are verifiying if a piece got jumped

            //the first statement checks to see if a piece was jumped two rows up
            else if ((destination.first == (origin.first + 2))){
                //if statements below check that a disk was jumped either two columns to the left or two the right
                if (destination.second == (origin.second + 2)){
                    //if statement checks if a piece was jumped two columns to the right and ensures a disk is jumped
                    if (m_game[origin.first + 1][origin.second + 1] == WDISK){
                        --m_whiteDisks;
                        m_game[origin.first + 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = BKING;
                        return true;
                    }
                    //else if ensures a KING was jumped
                    else if (m_game[origin.first + 1][origin.second + 1] == WKING){
                        --m_whiteDisks;
                        m_game[origin.first + 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = BKING;
                        return true;
                    }
                    //if nothing was jumped, then the move is invalid and false is returned
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else if checks if a piece was jumped two columns to the left
                else if (destination.second == (origin.second - 2)){
                    //if statement checks that a DISK was jumped
                    if (m_game[origin.first + 1][origin.second - 1] == WDISK){
                        --m_whiteDisks;
                        m_game[origin.first + 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = BKING;
                        return true;
                    }
                    //else if checks that a KING was jumped
                    else if (m_game[origin.first + 1][origin.second - 1] == WKING){
                        --m_whiteDisks;
                        m_game[origin.first + 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = BKING;
                        return true;
                    }
                    //if nothing is returned, then the move is invalid and false is returned
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else checks that the column is two away exactly, if not the move is invalid
                else{
                    cout << "Second destination variable invalid. Ensure something is being jumped" << endl;
                    return false;
                }
            }
            //else statement verifies if a piece was jumped if the destination is two rows down
            //if no piece is jumped, it is returned as false
            else if (destination.first == (origin.first - 2)){
                //if statement checks to ensure the destination is two away from the original column
                if (destination.second == (origin.second + 2)){
                    //if statement checks to see if a WDISK or WKING was jumped, if so it is 
                    if (m_game[origin.first - 1][origin.second + 1] == WDISK){
                        --m_whiteDisks;
                        m_game[origin.first - 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = BKING;
                        return true;
                    }
                    //else if is for eliminating the king
                    else if (m_game[origin.first - 1][origin.second + 1] == WKING){
                        --m_whiteDisks;
                        m_game[origin.first - 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = BKING;
                        return true;
                    }
                    //if nothing is jumped, then the location is invalid and is returned false
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else statement checks and see if the column 2 blocks away had a piece jump
                else if (destination.second == (origin.second - 2)){
                    //if statement checks that a DISK was jumped and eliminates it
                    if (m_game[origin.first - 1][origin.second - 1] == WDISK){
                        --m_whiteDisks;
                        m_game[origin.first - 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = BKING;
                        return true;
                    }
                    //else statement verifies that a WKING was jumped
                    else if (m_game[origin.first - 1][origin.second - 1] == WKING){
                        --m_whiteDisks;
                        m_game[origin.first - 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = BKING;
                        return true;
                    }
                    //if neither is true, false is returned
                    else{
                        cout << "Destination incorrect as nothing is jumped" << endl;
                        return false;
                    }
                }
                //else, if the destination second is not two columns away exactly, then the move is invalid
                else{
                    cout << "Second destination variable invalid. Ensure something is being jumped" << endl;
                    return false;
                }
            }
            //if none of the conditions above are satisifed, then the move is entirely invalid and false is returned
            else{
                cout << "Destination invalid, please try again" << endl;
                return false;
            }
        }

        /*BDISK MOVE*/

        //the else statement checks for valid movements for the BDISK piece
        //BDISK has more limited movement as it cannot go backwards
        else{
            //the first set of if statements check solo moves with no pieces being jumped
            //the king can move both forwards and backwards, and the valid actions reflect that

            //the first if statement verifies moving up one row
            if (destination.first == (origin.first - 1)){
                //if statements verify that the movement was valid
                //if statement verifies movement one column to the right
                if (destination.second == (origin.second + 1)){
                    m_game[destination.first][destination.second] = BDISK;
                    return true;
                }
                //else if verifies movement one column to the left
                else if (destination.second == (origin.second - 1)){
                    m_game[destination.first][destination.second] = BDISK;
                    return true;
                }
                //if the column is not one to the left or one to the right, then the move is invalid
                else{
                    cout << "Destination invalid, can only move right or left" << endl;
                    return false;
                }
            }

            //the if statements below are verifiying if a piece got jumped

            //the first statement checks to see if a piece was jumped two rows up
            else if ((destination.first == (origin.first - 2))){
                //if statements below check that a disk was jumped either two columns to the left or two the right
                if (destination.second == (origin.second + 2)){
                    //if statement checks if a piece was jumped two columns to the right and ensures a disk is jumped
                    if (m_game[origin.first - 1][origin.second + 1] == WDISK){
                        --m_whiteDisks;
                        m_game[origin.first - 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = BDISK;
                        return true;
                    }
                    //else if ensures a KING was jumped
                    else if (m_game[origin.first - 1][origin.second + 1] == WKING){
                        --m_whiteDisks;
                        m_game[origin.first - 1][origin.second + 1] = BCELL;
                        m_game[destination.first][destination.second] = BDISK;
                        return true;
                    }
                    //if nothing was jumped, then the move is invalid and false is returned
                    else{
                        cout << "Destination invalid. Ensure that a piece is being jumped" << endl;
                        return false;
                    }
                }
                //else if checks if a piece was jumped two columns to the left
                else if (destination.second == (origin.second - 2)){
                    //if statement checks that a DISK was jumped
                    if (m_game[origin.first - 1][origin.second - 1] == WDISK){
                        --m_whiteDisks;
                        m_game[origin.first - 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = BDISK;
                        return true;
                    }
                    //else if checks that a KING was jumped
                    else if (m_game[origin.first - 1][origin.second - 1] == WKING){
                        --m_whiteDisks;
                        m_game[origin.first - 1][origin.second - 1] = BCELL;
                        m_game[destination.first][destination.second] = BDISK;
                        return true;
                    }
                    //if nothing is returned, then the move is invalid and false is returned
                    else{
                        cout << "Invalid move, ensure a piece is being jumped" << endl;
                        return false;
                    }
                }
                //else checks that the column is two away exactly, if not the move is invalid
                else{
                    cout << "Move invalid, ensure that your destination is two away" << endl;
                    return false;
                }
            }
            //if none of the conditions above are satisifed, then the move is entirely invalid and false is returned
            else{
                cout << "Destination invalid" << endl;
                return false;
            }
        }
    }
    else{
        cout << "Invalid Piece Move" << endl;
        return false;
    }
}