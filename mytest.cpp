/***************************
 ** File:    mytest.cpp
 ** Project: CMSC 341, proj0, Spring 2023
 ** Author:  William Whatley
 ** Date:    2/11/2023
 ** Section: Marron
 ** Email:   w59@umbc.edu
 **
 ** This file is written as a test for Checkers.cpp. Numerous cases are tested to ensure
 ** that the code works properly. Normal cases, edge cases, and error cases are tested, alongside
 ** other tests such as testing the play function, setGameState, and initGame.
 **
*****************************/
#include "checkers.h"

class Tester{
    public:
        void testCondition(bool var){
            if (var){
                cout << "\nThe test has passed" << endl << endl;
            }
            else{
                cout << "\nThis test has failed" << endl << endl;
            }
        }
        //boardCreation
        //This test checks to ensure that a board is being created
        bool boardCreation(const int size, Checkers& check){
            cout << "boardCreation called" << endl;
            cout << "This test is to ensure that the board was properly created" << endl;
            
            bool result = true;

            //this test checks to ensure that the default values are not constructed
            result = result && (check.m_game != nullptr);
            result = result && (check.m_numRows == sqrt(size));
            result = result && (check.m_numColumns == sqrt(size));

            return result;
        }

        //errorBoardCreation
        //This test checks to ensure that the board is not being created for error cases
        bool errorBoardCreation(Checkers& check){
            cout << "errorBoardCreation called" << endl;
            cout << "This test for error cases" << endl;
            
            bool result = true;

            //result checks to see if the default variables are in place
            result = result && (check.m_game == nullptr);
            result = result && (check.m_whiteDisks == 0);
            result = result && (check.m_blackDisks == 0);

            return result;
        }


        //initBoardTest
        //this checks to ensure that the initBoard test worked
        bool testinitBoard(Checkers& check){
            cout << "testinitBoard called" << endl;
            cout << "This test will check and ensure that initBoard works" << endl;
            bool result = true;

            check.initBoard();

            //result checks to ensure that the pieces are set by edges of the board and that the numbers and currPlayers are set
            result = result && (check.m_game != nullptr);

            //The first and last CELLS in m_game are checked to ensure that they correspond to the correct value
            result = result && (check.m_game[0][0] == WCELL);
            result = result && (check.m_game[check.m_numRows - 1][check.m_numColumns - 2] == BCELL);
            
            return result; 
        }

        //errorinitBoard Test
        //This test ensures that an error board does not allow the board to be set
        bool errorinitBoard(Checkers& check){
            cout << "errorinitBoard called" << endl;
            cout << "This test will check and ensure that initBoard does not work for error cases" << endl;
            bool result = true;

            //result checks to ensure that the object is still empty
            result = result && (check.m_game == nullptr);
            result = result && (check.m_whiteDisks == 0);
            result = result && (check.m_blackDisks == 0);
            
            return result; 
        }

        //testinitGame
        //This tests to ensure that initGame works properly
        bool testinitGame(const int size, Checkers& check){
            cout << "testinitGame called" << endl;
            cout << "This function checks to ensure that initGame works properly" << endl;
            bool result = true;
            //int numOfPieces declared and initialized and is used for checking num of white and black disks
            
            check.initGame();

            //result checks to ensure that the member variables are changed accordingly
            result = result && (check.m_whiteDisks == (sqrt(size)* 3/2));
            result = result && (check.m_blackDisks == (sqrt(size)* 3/2));
            result = result && (check.m_currPlayer == BPLAYER);
            result = result && (check.m_game[0][1] == WDISK);
            result = result && (check.m_game[check.m_numRows - 1][check.m_numColumns - 2] == BDISK); //last BCELL on an even board
           
            return result;
        }

        //errorinitGame
        //This functions checks to make sure that errant objects did not go through
        bool errorinitGame(Checkers& check){
            cout << "errorinitGame called" << endl;
            cout << "This function checks to ensure that an errant object's initGame keeps the object empty" << endl;
            
            bool result = true;

            check.initGame();

            //result checks to ensure that everything is still at it's default value
            result = result && (check.m_whiteDisks == 0);
            result = result && (check.m_blackDisks == 0);
            result = result && (check.m_currPlayer == NONE);

            return result;
        }

        //testsetGameState
        //Used to determine if setGameState works properly
        bool testsetGameState(Checkers& check, CELL game[], int n, PLAYER player){
            cout << "testsetGameState called" << endl;
            cout << "This function tests to ensure that setGameState is working properly" << endl;

            bool result = true;

            //checks setGameState to ensure it works
            check.setGameState(game, n, player);

            int currRow;
            int currColumn;

            //result checks to ensure that player is also changed
            result = result && (check.m_currPlayer == player);

            //for loop goes through both arrays and makes sure not everything equals each other
            //if not, result is set to false;
            for (int i = 0; i < n; i++){
                //currRow is set to i/sqrt(n) to indicate which index it is on, and since ints automatically floor, it will go to the lowest index
                currRow = i / sqrt(n);
                //currColumn is i minus currRow times sqrt(n), as it corresponds to the index provided
                currColumn = i - (currRow * sqrt(n));
                if (check.m_game[currRow][currColumn] != game[i]){
                    result = true;
                }
            }

            return result;
        }

        //errorsetGameState
        //This function checks to ensure that setGameState does not work if the object sent is invalid
        bool errorsetGameState(Checkers& check, CELL game[], int n, PLAYER player){
            cout << "errorSetGameState called" << endl;
            cout << "This function tests to make sure an errant setGameState does not go through" << endl;
            
            bool result = true;

            //checks setGameState to ensure it works
            check.setGameState(game, n, player);

            //int currRow and currColumn are declared for the for loop
            int currRow;
            int currColumn;

            //for loop goes through both arrays and makes sure everything equals each other
            //if not, result is set to false;
            for (int i = 0; i < n; i++){
                //currRow is set to i/sqrt(n) to indicate which index it is on, and since ints automatically floor, it will go to the lowest index
                currRow = i / sqrt(n);
                //currColumn is i minus currRow times sqrt(n), as it corresponds to the index provided
                currColumn = i - (currRow * sqrt(n));
                if (check.m_game[currRow][currColumn] != game[i]){
                    result = true;
                }
            }

            return result;

        }

        //errorPlay
        //This tests to ensure that invalid moves do not work properly
        bool errorPlay(Checkers& check){
            cout << "errorPlay called" << endl;
            cout << "A lot of invalid movements will appear, to be expected" << endl << endl;
            bool result = true;

            //result checks to see if there's a white disk and king on the board
            //the spaces do not matter, the numbers chosen were arbitrary and for easy access
            result = result && (check.m_game[2][1] == WDISK);
            result = result && (check.m_game[2][check.m_numColumns - 1] == WKING);

            //result checks to see if there's a black disk AD KINGon the board
            //the spaces do not matter, the numbers chosen were arbitrary and for easy access
            result = result && (check.m_game[check.m_numRows - 3][check.m_numColumns - 2] == BDISK);
            result = result && (check.m_game[check.m_numRows - 3][0] == BKING);

            check.m_currPlayer = BPLAYER;

            //black disk starts first
            //it is moved legitimately first
            //then it is tested to make sure it doesn't move backwards, then it is tested to ensure that it cannot 'teleport', and move on white spaces
            //finally, it is tested to ensure a BPLAYER cannot move a white disk
            result = result && check.play(pair<int,int>(check.m_numRows - 3, check.m_numColumns - 2), pair <int,int>(check.m_numRows - 4, check.m_numColumns - 1));
            
            //player is reset due to the valid move changing it
            check.m_currPlayer = BPLAYER;

            result = result && !(check.play(pair<int,int>(check.m_numRows - 4, check.m_numColumns - 1), pair <int,int>(check.m_numRows - 3, check.m_numColumns - 2)));
            result = result && !(check.play(pair<int,int>(check.m_numRows - 4, check.m_numColumns - 1), pair <int,int>(check.m_numRows - 4, check.m_numColumns - 3)));
            result = result && !(check.play(pair<int,int>(check.m_numRows - 4, check.m_numColumns - 1), pair <int,int>(check.m_numRows - 6, check.m_numColumns - 4)));
            result = result && !(check.play(pair<int,int>(check.m_numRows - 4, check.m_numColumns - 1), pair <int,int>(0,0)));
            result = result && !(check.play(pair<int,int>(check.m_numRows - 4, check.m_numColumns - 1), pair <int,int>(0,1)));
            result = result && !(check.play(pair<int,int>(2,1),pair <int,int>(3,2)));

            check.m_currPlayer = WPLAYER;
            //The same is then done for white disk
            //it is moved legitimately first
            //then it is tested to make sure it doesn't move backwards, then it is tested to ensure that it cannot 'teleport', and move on white spaces
            //finally, it is tested to ensure a WPLAYER cannot move a black disk
            result = result && check.play(pair<int,int>(2,1),pair <int,int>(3,2));
            
            //player is reset due to the valid move changing it
            check.m_currPlayer = WPLAYER;

            result = result && !(check.play(pair<int,int>(3,2),pair <int,int>(2,1)));
            result = result && !(check.play(pair<int,int>(3,2),pair <int,int>(3,4)));
            result = result && !(check.play(pair<int,int>(3,2),pair <int,int>(4,5)));
            result = result && !(check.play(pair<int,int>(3,2),pair <int,int>(0,1)));
            result = result && !(check.play(pair<int,int>(3,2),pair <int,int>(0,0)));
            result = result && !(check.play(pair<int,int>(check.m_numRows - 4, check.m_numColumns - 1),pair <int,int>(check.m_numRows - 5, check.m_numColumns - 2)));

            //Kings are tested to ensure they cannot teleport or move to a white space
            //white king tested first
            result = result && !(check.play(pair<int,int>(2, check.m_numColumns - 1),pair <int,int>(2, check.m_numColumns - 3)));
            result = result && !(check.play(pair<int,int>(2, check.m_numColumns - 1),pair <int,int>(5, check.m_numColumns - 4)));
            result = result && !(check.play(pair<int,int>(2, check.m_numColumns - 1),pair <int,int>(0,1)));
            result = result && !(check.play(pair<int,int>(2, check.m_numColumns - 1),pair <int,int>(0,0)));

            check.m_currPlayer = BPLAYER;
            //black king tested second
            result = result && !(check.play(pair<int,int>(check.m_numRows - 3, 0),pair <int,int>(check.m_numRows - 3, 2)));
            result = result && !(check.play(pair<int,int>(check.m_numRows - 3, 0),pair <int,int>(check.m_numRows - 6, 3)));
            result = result && !(check.play(pair<int,int>(check.m_numRows - 3, 0),pair <int,int>(0,1)));
            result = result && !(check.play(pair<int,int>(check.m_numRows - 3, 0),pair <int,int>(0,0)));

            return result;
        }

        //testMovement
        //The purpose of this file is to test the single movement of both black and white disks
        bool testDiskMovement (Checkers& check){
            cout << "testMovement called" << endl;
            cout << "This function tests disk movement for both black and white to ensure it properly works" << endl;
            bool result = true;

            //result checks to see if there's a white disk on the board
            //the spaces do not matter, the numbers chosen were arbitrary and for easy access
            result = result && (check.m_game[2][1] == WDISK);

            //result checks to see if there's a black disk on the board
            //the spaces do not matter, the numbers chosen were arbitrary and for easy access
            result = result && (check.m_game[check.m_numRows - 3][check.m_numColumns - 2] == BDISK);

            check.m_currPlayer = BPLAYER;

            //black player starts then white player move, which is what this result simulates
            //each piece moves once to the left and once to the right to ensure that movement is properly working in both directions
            result = result && check.play(pair<int,int>(check.m_numRows - 3, check.m_numColumns - 2), pair <int,int>(check.m_numRows - 4, check.m_numColumns - 1));
            result = result && check.play(pair<int,int>(2,1),pair <int,int>(3,2));
            result = result && check.play(pair<int,int>(check.m_numRows - 4, check.m_numRows - 1), pair <int,int>(check.m_numRows - 5, check.m_numColumns - 2)); 
            result = result && check.play(pair<int,int>(3,2),pair <int,int>(4,1));

            return result;    
        }

        //testKingMovement
        //This tests to ensure that the kings are moving properly
        bool testKingMovement(Checkers &check){
            cout << "testKingMovement called" << endl;
            cout << "This function tests movement for both black and white kings" << endl;
            bool result = true;

            //result checks to make sure there's a king at each corner
            //corners are used because each of the king's four directions are tesed
            result = result && (check.m_game[check.m_numRows - 1][0] == WKING); //check.m_numRows - 1 is used due to indexing
            result = result && (check.m_game[0][1] == WKING); //0,1 is used since 0,0 is a white cell
            result = result && (check.m_game[check.m_numRows - 1][check.m_numColumns -2] == WKING); //numColumns - 2 is used since that corner of the board is a WCELL
            result = result && (check.m_game[0][check.m_numColumns - 1] == WKING);

            //four more corners are used for black kings to see if their 4 directional movement works as well
            //they are placed one away and since BPLAYER moves first, they are moved first to ensure they aren't jumped
            result = result && (check.m_game[check.m_numRows - 2][1] == BKING);
            result = result && (check.m_game[1][2] == BKING);
            result = result && (check.m_game[check.m_numRows - 2][check.m_numColumns -3] == BKING);
            result = result && (check.m_game[1][check.m_numColumns - 2] == BKING);
            
            //the game is then played
            //the black kings are moved first, then the white kings afterwards so no black kings get jumped
            //this is done because of edge cases where an 8x8 has limited room
            check.m_currPlayer = BPLAYER;

            //bottom left corner tested
            result = result && check.play(pair<int,int>((check.m_numRows - 2), 1), pair <int,int>((check.m_numRows - 3), 2));
            result = result && check.play(pair<int,int>((check.m_numRows - 1), 0), pair <int,int>((check.m_numRows - 2), 1));

            //top left corner tested
            result = result && check.play(pair<int,int>(1, 2), pair <int,int>(2, 3));
            result = result && check.play(pair<int,int>(0, 1), pair <int,int>(1, 2));

            //bottom right corner tested
            result = result && check.play(pair<int,int>((check.m_numRows - 2), (check.m_numColumns - 3)), pair <int,int>((check.m_numRows - 3), (check.m_numColumns - 4)));
            result = result && check.play(pair<int,int>((check.m_numRows - 1), (check.m_numColumns - 2)), pair <int,int>((check.m_numRows - 2), (check.m_numColumns - 3)));

            //top left corner tested
            result = result && check.play(pair<int,int>(1, (check.m_numColumns - 2)), pair <int,int>(2, (check.m_numColumns - 3)));
            result = check.play(pair<int,int>(0, (check.m_numColumns - 1)), pair <int,int>(1, (check.m_numColumns - 2)));
            
            return result;
        }   

        //testKingUpgrade
        //This test ensures that the king upgrade works propery for both white and black pieces
        bool testKingUpgrade(Checkers& check){
            cout << "testKingUpgrade called" << endl;
            cout << "This function ensures that king upgrade works for both white and black disks" << endl;
            bool result = true;

            //checks to ensure that there are disks in position to be moved to kings
            result = result && (check.m_game[check.m_numRows - 2][1] == WDISK);
            result = result && (check.m_game[1][0] == BDISK);

            //checks to ensure that there are no disks blocking movement
            result = result && (check.m_game[check.m_numRows - 1][0] == BCELL);
            result = result && (check.m_game[0][1] == BCELL);
    
            check.m_currPlayer = BPLAYER; //player changed to BPLAYER

            //disks moved to the edges of boards
            result = result && check.play(pair<int,int>(1,0), pair <int,int>(0,1));
            result = result && check.play(pair<int,int>((check.m_numRows -2), 1), pair<int, int>((check.m_numRows - 1), 0));

            //checks to see if the pieces upgraded to kings
            result = result && (check.m_game[0][1] == BKING);
            
            result = result && (check.m_game[check.m_numRows - 1][0] == WKING);
            
            return result;
        }

        //testCaptureToKing
        //This function tests to ensure that an upgrade from disk to king still works when capturing another disk
        bool testCaptureToKing(Checkers& check){
            cout << "testCapturetoKing called" << endl;
            cout << "This function ensures that king upgrade works for both white and black disks" << endl;
            bool result = true;

            //checks to ensure that BDISK and WDISK are two away and are able to capture a piece
            result = result && (check.m_game[check.m_numRows - 3][2] == WDISK);
            result = result && (check.m_game[2][3] == BDISK);
            
            //checks to ensure that there are disks in position to be captured
            result = result && (check.m_game[check.m_numRows - 2][1] == BDISK);
            result = result && (check.m_game[1][2] == WDISK);

            //checks to ensure that there are no disks blocking movement
            result = result && (check.m_game[check.m_numRows - 1][0] == BCELL);
            result = result && (check.m_game[0][1] == BCELL);
    
            check.m_currPlayer = BPLAYER; //player changed to BPLAYER

            //disks moved to the edges of boards
            result = result && check.play(pair<int,int>(2,3), pair <int,int>(0,1));
            result = result && check.play(pair<int,int>((check.m_numRows -3), 2), pair<int, int>((check.m_numRows - 1), 0));

            //checks to see if the pieces upgraded to kings
            result = result && (check.m_game[0][1] == BKING);
            check.reportLostDisks();

            result = result && (check.m_game[check.m_numRows - 1][0] == WKING);
            
            return result;
        }

        //testEndOfGame
        //This tests the end of game for both a white victory and a black victory
        bool testEndOfGame(Checkers& check){
            cout << "testEndOfGame called" << endl;
            cout << "This function tests to ensure that white and black can both properly win" << endl;
            bool result = true;

            //result checks to make sure both sides only have one piece
            result = result && (check.m_blackDisks == 1);
            result = result && (check.m_whiteDisks == 1);

            //checks to ensure that pieces are set up in the proper places for the game to end
            //those arbitrary spots are tested because it's easy for a white disk and black disk to both overtake each other
            result = result && (check.m_game[2][3] == WDISK);
            result = result && (check.m_game[3][4] == BDISK);

            check.m_currPlayer = WPLAYER;
            result = result && check.play(pair<int,int>(2,3), pair <int,int>(4,5));

            result = result && !(check.play(pair<int,int>(4,5), pair <int,int>(5,6)));

            ++check.m_blackDisks;
            check.m_game[3][4] = BDISK;
            check.m_game[2][3] = WDISK;
            check.m_game[4][5] = BCELL;

            check.m_currPlayer = BPLAYER;

            result = result && check.play(pair<int,int>(3,4), pair <int,int>(1,2));
            
            result = result && !(check.play(pair<int,int>(1,2), pair <int,int>(0,1)));
            
            return result;
        } 


        //testWhiteKingCapture
        //This tests to ensure that the white king captures properly
        bool testWhiteKingCapture(Checkers& check){
            cout << "testWhiteKingCapture called" << endl;
            cout << "This function tests to make sure that white king can capture from all four directions" << endl;
            bool result = true;

            //disks is saved as a temporary int
            int disks = check.m_blackDisks;

            //result checks to make sure there's a king at each corner
            //corners are used because each of the king's four jumping movement is tested
            result = result && (check.m_game[check.m_numRows - 1][0] == WKING); //check.m_numRows - 1 is used due to indexing
            result = result && (check.m_game[0][1] == WKING); //0,1 is used since 0,0 is a white cell
            result = result && (check.m_game[check.m_numRows - 1][check.m_numColumns -2] == WKING); //numColumns - 2 is used since that corner of the board is a WCELL
            result = result && (check.m_game[0][check.m_numColumns - 1] == WKING);

            //result checks to ensure that there is a black disk able to be captured in each place
            result = result && (check.m_game[check.m_numRows - 2][1] == BDISK || check.m_game[check.m_numRows - 2][1] == BKING);
            result = result && (check.m_game[1][2] == BDISK || check.m_game[1][2] == BKING);
            result = result && (check.m_game[check.m_numRows - 2][check.m_numColumns - 3] == BDISK || check.m_game[check.m_numRows - 2][check.m_numColumns - 3] == BKING);
            result = result && (check.m_game[1][check.m_numColumns -2] == BDISK || check.m_game[1][check.m_numColumns -2] == BKING);

            //WPLAYER set and then the capture plays are tested
            check.m_currPlayer = WPLAYER;
            result = result && check.play(pair<int,int>((check.m_numRows - 1), 0), pair <int,int>((check.m_numRows - 3), 2));
            check.m_currPlayer = WPLAYER;
            result = result && check.play(pair<int,int>(0, 1), pair <int,int>(2, 3));
            check.m_currPlayer = WPLAYER;
            result = result && check.play(pair<int,int>((check.m_numRows - 1), (check.m_numColumns - 2)), pair <int,int>((check.m_numRows - 3), (check.m_numColumns - 4)));
            check.m_currPlayer = WPLAYER;
            result = result && check.play(pair<int,int>(0, (check.m_numColumns - 1)), pair <int,int>(2, (check.m_numColumns - 3)));

            //result finally checks to ensure that 4 black disks were taken
            result = result && (disks == (check.m_blackDisks + 4));
            
            check.reportLostDisks();

            return result;
        }

        //blackKingCapture
        //This tests to ensure that the black king is capturing properly
        bool testBlackKingCapture(Checkers& check){
            cout << "testBlackKingCapture called" << endl;
            cout << "This function tests to make sure that black king can capture from all four directions" << endl;
            bool result = true;

            //disks is saved as a temporary int
            int disks = check.m_whiteDisks;

            //result checks to make sure there's a king at each corner
            //corners are used because each of the king's four jumping movement is tested
            result = result && (check.m_game[check.m_numRows - 1][0] == BKING); //check.m_numRows - 1 is used due to indexing
            result = result && (check.m_game[0][1] == BKING); //0,1 is used since 0,0 is a white cell
            result = result && (check.m_game[check.m_numRows - 1][check.m_numColumns -2] == BKING); //numColumns - 2 is used since that corner of the board is a WCELL
            result = result && (check.m_game[0][check.m_numColumns - 1] == BKING);

            //result checks to ensure that there is a black disk able to be captured in each place
            result = result && (check.m_game[check.m_numRows - 2][1] == WDISK || check.m_game[check.m_numRows - 2][1] == WKING);
            result = result && (check.m_game[1][2] == WDISK || check.m_game[1][2] == WKING);
            result = result && (check.m_game[check.m_numRows - 2][check.m_numColumns -3] == WDISK || check.m_game[check.m_numRows - 2][check.m_numColumns - 3] == WKING);
            result = result && (check.m_game[1][check.m_numColumns -2] == WDISK || check.m_game[1][check.m_numColumns -2] == WKING);

            //each turn is BPLAYER, and then the play move is tested to ensure the piece is being captured
            check.m_currPlayer = BPLAYER;
            result = result && check.play(pair<int,int>((check.m_numRows - 1), 0), pair <int,int>((check.m_numRows - 3), 2));
            check.m_currPlayer = BPLAYER;
            result = result && check.play(pair<int,int>(0, 1), pair <int,int>(2, 3));
            check.m_currPlayer = BPLAYER;
            result = result && check.play(pair<int,int>((check.m_numRows - 1), (check.m_numColumns - 2)), pair <int,int>((check.m_numRows - 3), (check.m_numColumns - 4)));
            check.m_currPlayer = BPLAYER;
            result = result && check.play(pair<int,int>(0, (check.m_numColumns - 1)), pair <int,int>(2, (check.m_numColumns - 3)));

            //result checks to ensure that 4 white disks were taken from the board
            result = result && (disks == (check.m_whiteDisks + 4));

            check.reportLostDisks();
            
            return result;
        }

        //testWhiteBlackCapture
        //This test ensures that whiteDiskCapture works properly
        bool testWhiteDiskCapture(Checkers& check){
            cout << "testWhiteDiskCapture called" << endl;
            cout << "This function tests to make sure white disks can capture from two directions" << endl;
            bool result = true;

            //disks is a temportary int
            int disks = check.m_blackDisks;

            //result checks to ensure that a WDISK and BDISK are in place to set up a capture
            //disks are placed in a way so that the white capture is tested both to the left and the right
            result = result && (check.m_game[0][3] == WDISK); //result checks to ensure that a WDISK is in a corner
            result = result && ((check.m_game[1][2] == BDISK) || (check.m_game[1][2] == BKING));
            result = result && ((check.m_game[3][2] == BDISK) || (check.m_game[3][2] == BKING));
            result = result && (check.m_game[2][1] == BCELL);
            result = result && (check.m_game[4][3] == BCELL);

            //m_currPlayer is set to WPLAYER, and then the capture is tested
            check.m_currPlayer = WPLAYER;
            result = result && check.play(pair<int,int>(0,3), pair <int,int>(2, 1));

            check.m_currPlayer = WPLAYER;
            result = result && check.play(pair<int,int>(2,1), pair <int,int>(4,3));
            //result checks to ensure that one black disk was taken
            result = result && (disks == (check.m_blackDisks + 2));

            check.reportLostDisks();

            return result;
        }

        //testBlackDiskCapture
        //This test ensures that blackDiskCapture works properly
        bool testBlackDiskCapture(Checkers& check){
            cout << "testBlackDiskCapture called" << endl;
            cout << "This function tests to make sure black disks can capture from two directions" << endl;

            bool result = true;
            //disks is a temportary int
            int disks = check.m_whiteDisks;

            //result checks to ensure that a WDISK and BDISK are in place to set up a capture
            //disks are placed in a way so that the black capture is tested both to the left and the right
            result = result && (check.m_game[check.m_numRows - 1][2] == BDISK); //result checks to ensure that a WDISK is in a corner
            result = result && (check.m_game[check.m_numRows - 2][1] == WDISK || check.m_game[check.m_numRows - 2][1] == WKING);
            result = result && (check.m_game[check.m_numRows - 4][1] == WDISK || check.m_game[check.m_numRows - 4][1] == WKING);
            result = result && (check.m_game[check.m_numRows - 3][0] == BCELL);
            result = result && (check.m_game[check.m_numRows - 5][2] == BCELL);
            
            //m_currPlayer is set to BPLAYER, and then the capture is tested
            check.m_currPlayer = BPLAYER;
            result = result && check.play(pair<int,int>((check.m_numRows - 1), 2), pair <int,int>((check.m_numRows -3), 0));

            check.m_currPlayer = BPLAYER;

            result = result && check.play(pair<int,int>((check.m_numRows - 3), 0), pair <int,int>((check.m_numRows -5), 2));

            //result checks to ensure that one piece is captured
            result = result && (disks == (check.m_whiteDisks + 2));

            check.reportLostDisks();

            return result;
        }

};

int main(){
    Tester tester;
    
    cout << "**********************" << endl;
    cout << "***** BEGIN TEST *****" << endl;
    cout << "**********************" << endl << endl;
    {   
        cout << "***TEST BLOCK ONE ***" << endl << endl;
        cout << "First test block is regarding an edge case" << endl;
        cout << "We will attempt to create a board of 8 by 8 size" << endl << endl;

        //a new checkers object is created
        Checkers* newChecker = new Checkers(8,8);
        
        int sizeOfBoard = 8 * 8;

        //bool testResult is declared and initialized
        bool testResult = tester.boardCreation(sizeOfBoard, *newChecker);
        tester.testCondition(testResult);
        
        //testResult is then initalized to testinitBoard to ensure that it goes through
        testResult = tester.testinitBoard(*newChecker);
        tester.testCondition(testResult);

        
        

        //testResult is then initialized to testinitGame to ensure that the board is set up
        testResult = tester.testinitGame(sizeOfBoard, *newChecker);
        tester.testCondition(testResult);

        
        

        //CELL testarray is created and then sent to setGameState to ensure that it works properly
        CELL testArray[] = 
        {"", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",
        "", BCELL, "", BDISK, "", BCELL, "", BCELL,
        WDISK, "", "", "", WDISK, "", WDISK, "",
        "", "", "", BDISK, "", BDISK, "", "",
        "", "", BCELL, "", BCELL, "", BCELL, "",
        "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "",};

        //setGameState is then tested to ensure it works properly
        testResult = tester.testsetGameState(*newChecker, testArray, sizeOfBoard, WPLAYER);
        tester.testCondition(testResult);
        
        //newChecker is deleted
        delete newChecker;
        cout << "\n***END TEST BLOCK ONE***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK TWO***" << endl << endl;
        cout << "This test block will test the creation, initBoard, initGame, and setGameState of a normal board" << endl;
        cout << "We will test a 10 by 10 board" << endl << endl;

        //a new checkers object is created
        Checkers* newChecker = new Checkers(10, 10);
        
        int sizeOfBoard = 10 * 10;

        //bool testResult is declared and initialized
        bool testResult = tester.boardCreation(sizeOfBoard, *newChecker);
        tester.testCondition(testResult);
        
        //testResult is then initalized to testinitBoard to ensure that it goes through
        testResult = tester.testinitBoard(*newChecker);
        tester.testCondition(testResult);

        
        

        //testResult is then initialized to testinitGame to ensure that the board is set up
        testResult = tester.testinitGame(sizeOfBoard, *newChecker);
        tester.testCondition(testResult);

        
        

        //CELL testarray is created and then sent to setGameState to ensure that it works properly
        CELL testArray[] = 
        {"", WKING, "", "", "", "", "", "", "", WKING,
        "", "", BKING, "", "", "", "", "", BKING, "",
        "", "", "",BCELL, "", "", "", BCELL, "", "",
        "", "", "", "", BDISK, "", BDISK, "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", WDISK, "", WDISK, "", "", "", "",
        "", "", BCELL, "", "", "", BCELL, "", "", "",
        "", BKING, "", "", "", "", "", BKING, "", "",
        WKING, "", "", "", "", "", "", "", WKING, "",};

        //setGameState is then tested to ensure it works properly
        testResult = tester.testsetGameState(*newChecker, testArray, sizeOfBoard, WPLAYER);
        tester.testCondition(testResult);
        
        
        //newChecker is deleted
        delete newChecker;
        cout << "\n***END TEST BLOCK TWO***" << endl;

    }
    {
        cout << "\n*** TEST BLOCK THREE ***" << endl << endl;
        cout << "This test block will test the creation, initBoard, and initGame of an error board" << endl;
        cout << "We will test a 7 by 7 board" << endl << endl;

         //a new checkers object is created
        Checkers* newChecker = new Checkers(7, 7);
        

        //bool testResult is declared and initialized to errorBoardCreation to ensure that it isn't created
        bool testResult = tester.errorBoardCreation(*newChecker);
        tester.testCondition(testResult);
        
        //testResult is then initalized to errorinitBoard to ensure that the object stays empty
        testResult = tester.errorinitBoard(*newChecker);
        tester.testCondition(testResult);

        //testResult is then initialized to errorinitGame to ensure that the board is not created
        testResult = tester.errorinitGame(*newChecker);
        tester.testCondition(testResult);

        delete newChecker;

        cout << "\n*** END TEST BLOCK THREE ***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK FOUR ***" << endl << endl;
        cout << "This test block will test the creation, initBoard, and initGame of an error board" << endl;
        cout << "We will test a -10 by -10 board" << endl << endl;

         //a new checkers object is created
        Checkers* newChecker = new Checkers(-10, -10);
    
        //bool testResult is declared and initialized to errorBoardCreation to ensure that it isn't created
        bool testResult = tester.errorBoardCreation(*newChecker);
        tester.testCondition(testResult);
        
        //testResult is then initalized to errorinitBoard to ensure that the object stays empty
        testResult = tester.errorinitBoard(*newChecker);
        tester.testCondition(testResult);

        //testResult is then initialized to errorinitGame to ensure that the board is not created
        testResult = tester.errorinitGame(*newChecker);
        tester.testCondition(testResult);

        delete newChecker;

        cout << "\n*** END TEST BLOCK FOUR ***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK FIVE ***" << endl << endl;
        cout << "This test block will test the creation, initBoard, and initGame of an error board" << endl;
        cout << "We will test a 9 by 9 board" << endl << endl;

         //a new checkers object is created
        Checkers* newChecker = new Checkers(9,9);
        
        //bool testResult is declared and initialized to errorBoardCreation to ensure that it isn't created
        bool testResult = tester.errorBoardCreation(*newChecker);
        tester.testCondition(testResult);
        
        //testResult is then initalized to errorinitBoard to ensure that the object stays empty
        testResult = tester.errorinitBoard(*newChecker);
        tester.testCondition(testResult);

        //testResult is then initialized to errorinitGame to ensure that the board is not created
        testResult = tester.errorinitGame(*newChecker);
        tester.testCondition(testResult);

        delete newChecker;

        cout << "\n*** END TEST BLOCK FIVE ***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK SIX ***" << endl;
        cout << "This test is dedicated to ensuring an error setGameState doesn't work" << endl;
        Checkers* newChecker = new Checkers(10, 10);
        
        int sizeOfBoard = 10 * 10;

        newChecker->initBoard();
        newChecker->initGame();

        //CELL testarray is created and then sent to setGameState to ensure that it works properly
        CELL testArray[] = 
        {BCELL, "", WKING, "", "", "", "", "", "", "",
        "", BKING, "", BDISK, "", WDISK, "", "", "", "",
        "", WCELL, "", WCELL, "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        WCELL, "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        WCELL, "", "", "", "", "", "", "", "", "",};

        //errorSetGameState is called to ensure that the errored game state doesn't work properly
        bool testResult = tester.errorsetGameState(*newChecker, testArray, sizeOfBoard, WPLAYER);
        tester.testCondition(testResult);

        //newChecker is deleted
        delete newChecker;

        cout << "\n*** END TEST BLOCK SIX ***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK SEVEN ***" << endl;
        cout << "This test block is dedicated to ensure invalid plays do not work properly" << endl;
        cout << "This test will take place on a normal 10 by 10 board" << endl;
        Checkers* newChecker = new Checkers(10, 10);
        
        int sizeOfBoard = 10 * 10;

        newChecker->initBoard();
        newChecker->initGame();

        //CELL testArray is created, WKING and BKING placed to ensure their plays do not work properly
        CELL testArray[] = 
        {"", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", WKING,
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        BKING, "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",};

        newChecker->setGameState(testArray, sizeOfBoard, BPLAYER);

        //errorPlay is called to ensure that the plays do not go through
        bool testResult = tester.errorPlay(*newChecker);
        tester.testCondition(testResult);    
        
        //newChecker is deleted
        delete newChecker;

        cout << "\n*** END TEST BLOCK SEVEN ***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK EIGHT***" << endl << endl;
        cout << "This test block is dedicated to testing single disk movement on a normal board" << endl;
        cout << "We will test a 10 by 10 board" << endl << endl;
        
        Checkers* newChecker = new Checkers(10,10);

        //the board and game pieces are set and created
        newChecker->initBoard();
        newChecker->initGame();

        //setGameState not used as it isn't needed
        //Movement tested on normal board
        bool testResult = tester.testDiskMovement(*newChecker);
        tester.testCondition(testResult);  

        //newChecker deleted
        delete newChecker;
        
        cout << "*** END TEST BLOCK EIGHT ***" << endl;
    }
    {
        cout << "\n***TEST BLOCK NINE ***" << endl << endl;
        cout << "This test block is dedicated to testing single movements of kings" << endl;
        Checkers* newChecker = new Checkers(10, 10);

        int sizeOfBoard = 10 * 10;

        //the board and game pieces are set and created
        newChecker->initBoard();
        newChecker->initGame();

        //testArrray set up so that the BKING can move first without being captured
        CELL testArray[] = 
        {"", WKING, "", "", "", "", "", "", "", WKING,
        "", "", BKING, "", "", "", "", "", BKING, "",
        "", "", "",BCELL, "", "", "", BCELL, "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", BCELL, "", "", "", BCELL, "", "", "",
        "", BKING, "", "", "", "", "", BKING, "", "",
        WKING, "", "", "", "", "", "", "", WKING, "",};

        //setGameState called so that the game board is set properly
        newChecker->setGameState(testArray, sizeOfBoard, WPLAYER);

        //the test is run and the result is printed
        bool testResult = tester.testKingMovement(*newChecker);
        tester.testCondition(testResult);

        //newChecker is deleted
        delete newChecker;

        cout << "\n***END TEST BLOCK NINE ***" << endl;
    }
    {
        cout << "\n***TEST BLOCK TEN***" << endl << endl;
        cout << "This test block is dedicated to testing the king upgrade" << endl;
        cout << "This test will test both the white disk and black disk upgrade" << endl << endl;
        
        Checkers* newChecker = new Checkers(10, 10);

        int sizeOfBoard = 10 * 10;

        //the board and game pieces are set and created
        newChecker->initBoard();
        newChecker->initGame();

        //testArray declared and initialized
        //two BCELLs are cleared as free locations to view if the king upgrade takes place
        CELL testArray[] = 
        {"", BCELL, "", "", "", "", "", "", "", "",
        BDISK, "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", WDISK, "", "", "", "", "", "", "", "",
        BCELL, "", "", "", "", "", "", "", "", "",};
        //setGameState called so that the game board is set properly
        newChecker->setGameState(testArray, sizeOfBoard, BPLAYER);

        //the test is run and the result is printed
        bool testResult = tester.testKingUpgrade(*newChecker);
        tester.testCondition(testResult);

        //newChecker is deleted
        delete newChecker;

        cout << "\n*** END TEST BLOCK TEN***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK ELEVEN***" << endl;
        cout << "This test block is dedicated to testing the king upgrade" << endl;
        cout << "This test will test both the white disk and black disk upgrade when capturing another piece" << endl << endl;
        
        Checkers* newChecker = new Checkers(10, 10);

        int sizeOfBoard = 10 * 10;

        //the board and game pieces are set and created
        newChecker->initBoard();
        newChecker->initGame();

        //testArray declared and initialized
        //two BCELLs are cleared as free locations to view if the king upgrade takes place
        //A BDISK and WDISK added to make reportLostDisks make more sense
        CELL testArray[] = 
        {"", BCELL, "", "", "", "", "", "", "", "",
        "", "", WDISK, "", "", "", "", "", "", "",
        "", "", "", BDISK, "", "", "", "", "", "",
        "", "", "", "", BDISK, "", WDISK, "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", WDISK, "", "", "", "", "", "", "",
        "", BDISK, "", "", "", "", "", "", "", "",
        BCELL, "", "", "", "", "", "", "", "", "",};

        //setGameState called so that the game board is set properly
        newChecker->setGameState(testArray, sizeOfBoard, BPLAYER);

        //the test is run and the result is printed
        bool testResult = tester.testCaptureToKing(*newChecker);
        tester.testCondition(testResult);

        //newChecker is deleted
        delete newChecker;

        cout << "\n*** END TEST BLOCK ELEVEN***" << endl;
    }
    {
        cout << "\n***TEST BLOCK TWELVE ***" << endl << endl;
        cout << "This test block is dedicated to WDISK capturing on a normal, 10 by 10 board" << endl << endl;
        cout << "We will first test capturing BDISKS, then capturing BKINGS" << endl << endl;
        Checkers* newChecker = new Checkers(10, 10);

        int sizeOfBoard = 10 * 10;

        //the board and game pieces are set and created
        newChecker->initBoard();
        newChecker->initGame();

        //testArray is changed so that the WKINGS are in the proper place to capture black disks
        //two black disks replaced with white disks to make reportLostDisks logical
        CELL testArray[] = 
        {"", "", "", WDISK, "", "", "", "", "", "",
        "", "", BDISK, "", "", "", "", "", "", "",
        "", BCELL, "", "", "", "", "", "", "", "",
        "", "", BDISK, "", "", "", "", "", "", "",
        "", "", "",BCELL, "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        WDISK, "", WDISK, "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",};
        //setGameState called so that the game board is set properly
        newChecker->setGameState(testArray, sizeOfBoard, BPLAYER);

        //the test is run and the result is printed
        bool testResult = tester.testWhiteDiskCapture(*newChecker);
        tester.testCondition(testResult);

        //the test is then run again with kings instead of disks this time
        CELL secondArray[] = 
        {"", "", "", WDISK, "", "", "", "", "", "",
        "", "", BKING, "", "", "", "", "", "", "",
        "", BCELL, "", "", "", "", "", "", "", "",
        "", "", BKING, "", "", "", "", "", "", "",
        "", "", "",BCELL, "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        WDISK, "", WDISK, "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",};

        //setGameState set again with the new array
        newChecker->setGameState(secondArray, sizeOfBoard, BPLAYER);

        //test is then run again
        testResult = tester.testWhiteDiskCapture(*newChecker);
        tester.testCondition(testResult);
        
        //newChecker is deleted
        delete newChecker;

        cout << "\n*** END TEST BLOCK TWELVE ***" << endl;
    }
    
    {
        cout << "\n***TEST BLOCK THIRTEEN ***" << endl << endl;
        cout << "This test block is dedicated to BDISK capturing on a normal, 10 by 10 board" << endl;
        cout << "We will first test capturing WDISKS, then capturing WKINGS" << endl << endl;
        Checkers* newChecker = new Checkers(10, 10);

        int sizeOfBoard = 10 * 10;

        //the board and game pieces are set and created
        newChecker->initBoard();
        newChecker->initGame();

        //testArray is changed so that the WKINGS are in the proper place to capture black disks
        //two black disks replaced with white disks to make reportLostDisks logical
        CELL testArray[] = 
        {"", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", BDISK, "", BDISK, "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", BCELL, "", "", "", "", "", "", "",
        "", WDISK, "", "", "", "", "", "", "", "",
        BCELL, "", "", "", "", "", "", "", "", "",
        "", WDISK, "", "", "", "", "", "", "", "",
        "", "", BDISK, "", "", "", "", "", "", "",};
        //setGameState called so that the game board is set properly
        newChecker->setGameState(testArray, sizeOfBoard, BPLAYER);

        //the test is run and the result is printed
        bool testResult = tester.testBlackDiskCapture(*newChecker);
        tester.testCondition(testResult);

        //the test is then run again with kings instead of disks this time
        CELL secondArray[] = 
        {"", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", BDISK, "", BDISK, "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", BCELL, "", "", "", "", "", "", "",
        "", WKING, "", "", "", "", "", "", "", "",
        BCELL, "", "", "", "", "", "", "", "", "",
        "", WKING, "", "", "", "", "", "", "", "",
        "", "", BDISK, "", "", "", "", "", "", "",};

        //setGameState set again with the new array
        newChecker->setGameState(secondArray, sizeOfBoard, BPLAYER);

        //test is then run again
        testResult = tester.testBlackDiskCapture(*newChecker);
        tester.testCondition(testResult); 

        //newChecker is deleted
        delete newChecker;

        cout << "\n*** END TEST BLOCK THIRTEEN***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK FOURTEEN***" << endl << endl;
        cout << "This test block is dedicated to testing WKING capturing" << endl;
        cout << "We will first test capturing BDISKS, then capturing BKINGS" << endl << endl;
        Checkers* newChecker = new Checkers(10, 10);

        int sizeOfBoard = 10 * 10;

        //the board and game pieces are set and created
        newChecker->initBoard();
        newChecker->initGame();

        //testArray is changed so that the WKINGS are in the proper place to capture black disks
        //two WDISKS and BDISKS are added to make up for ones replaced and make the reportLostDisk logical
        CELL testArray[] = 
        {"", WKING, "", "", "", "", "", "", "", WKING,
        "", "", BDISK, "", "", "", "", "", BDISK, "",
        "", "", "",BCELL, "", "", "", BCELL, "", "",
        WDISK, "", "", "", "", "", "", "", BDISK, "",
        "", "", "", "", "", "", "", "", "", "",
        WDISK, "", "", "", "", "", "", "", BDISK, "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", BCELL, "", "", "", BCELL, "", "", "",
        "", BDISK, "", "", "", "", "", BDISK, "", "",
        WKING, "", "", "", "", "", "", "", WKING, "",};

        //setGameState called so that the game board is set properly
        newChecker->setGameState(testArray, sizeOfBoard, WPLAYER);

        //the test is run and the result is printed
        bool testResult = tester.testWhiteKingCapture(*newChecker);
        tester.testCondition(testResult);

        //the test is then run again with kings instead of disks this time
        CELL secondArray[] = 
        {"", WKING, "", "", "", "", "", "", "", WKING,
        "", "", BKING, "", "", "", "", "", BKING, "",
        "", "", "",BCELL, "", "", "", BCELL, "", "",
        WDISK, "", "", "", "", "", "", "", BDISK, "",
        "", "", "", "", "", "", "", "", "", "",
        WDISK, "", "", "", "", "", "", "", BDISK, "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", BCELL, "", "", "", BCELL, "", "", "",
        "", BKING, "", "", "", "", "", BKING, "", "",
        WKING, "", "", "", "", "", "", "", WKING, "",};

        //setGameState called so that the game board is set properly
        newChecker->setGameState(secondArray, sizeOfBoard, WPLAYER);

        //test is then run again
        testResult = tester.testWhiteKingCapture(*newChecker);
        tester.testCondition(testResult);

        //newChecker is deleted
        delete newChecker;

        cout << "\n***END TEST BLOCK FOURTEEN ***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK FIFTEEN ***" << endl << endl;
        cout << "This test block is dedicated to testing BKING capturing" << endl;
        cout << "We will first test capturing WDISKS, then capturing WKINGS" << endl << endl;
        Checkers* newChecker = new Checkers(10, 10);

        int sizeOfBoard = 10 * 10;

        //the board and game pieces are set and created
        newChecker->initBoard();
        newChecker->initGame();

        //testArray is changed so that the BKINGS are in the proper place to capture white disks
        //two WDISKS and BDISKS are added to make up for ones replaced and make the reportLostDisk logical
        CELL testArray[] = 
        {"", BKING, "", "", "", "", "", "", "", BKING,
        "", "", WDISK, "", "", "", "", "", WDISK, "",
        "", "", "",BCELL, "", "", "", BCELL, "", "",
        WDISK, "", "", "", "", "", "", "", BDISK, "",
        "", "", "", "", "", "", "", "", "", "",
        WDISK, "", "", "", "", "", "", "", BDISK, "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", BCELL, "", "", "", BCELL, "", "", "",
        "", WDISK, "", "", "", "", "", WDISK, "", "",
        BKING, "", "", "", "", "", "", "", BKING, "",};
        //setGameState called so that the game board is set properly
        newChecker->setGameState(testArray, sizeOfBoard, BPLAYER);

        //the test is run and the result is printed
        bool testResult = tester.testBlackKingCapture(*newChecker);
        tester.testCondition(testResult);

        //the test is then run again with kings instead of disks this time
        CELL secondArray[] = 
        {"", BKING, "", "", "", "", "", "", "", BKING,
        "", "", WKING, "", "", "", "", "", WKING, "",
        "", "", "",BCELL, "", "", "", BCELL, "", "",
        WDISK, "", "", "", "", "", "", "", BDISK, "",
        "", "", "", "", "", "", "", "", "", "",
        WDISK, "", "", "", "", "", "", "", BDISK, "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", BCELL, "", "", "", BCELL, "", "", "",
        "", WKING, "", "", "", "", "", WKING, "", "",
        BKING, "", "", "", "", "", "", "", BKING, "",};

        //setGameState set again with the new array
        newChecker->setGameState(secondArray, sizeOfBoard, BPLAYER);

        //test is then run again
        testResult = tester.testBlackKingCapture(*newChecker);
        tester.testCondition(testResult);

        //newChecker is deleted
        delete newChecker;

        cout << "\n*** END TEST BLOCK FIFTEEN ***" << endl;
    }
    {
        cout << "\n*** TEST BLOCK SIXTEEN ***" << endl;
        cout << "This test block is dedicated to testing that the end of game works properly" << endl << endl;

        Checkers* newChecker = new Checkers(10, 10);

        int sizeOfBoard = 10 * 10;

        //the board and game pieces are set and created
        newChecker->initBoard();
        newChecker->initGame();

        //testArray created
        //It represents an empty board except for two pieces
        CELL testArray[] = 
        {"", BCELL, "", BCELL, "", BCELL, "", BCELL, "", BCELL,
        BCELL, "", BCELL, "", BCELL, "", BCELL, "", BCELL, "",
        "", BCELL, "",  WDISK, "", BCELL, "", BCELL, "", BCELL,
        "", "", "", "", BDISK, "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        "", "", "", "", "", "", "", "", "", "",
        BCELL, "", BCELL, "", BCELL, "", BCELL, "", BCELL, "",
        "", BCELL, "", BCELL, "", BCELL, "", BCELL, "", BCELL,
        BCELL, "", BCELL, "", BCELL, "", BCELL, "", BCELL, "",};
        //setGameState called so that the game board is set properly
        newChecker->setGameState(testArray, sizeOfBoard, BPLAYER);

        //the test is run and the result is printed
        bool testResult = tester.testEndOfGame(*newChecker);
        tester.testCondition(testResult);

        //newChecker is deleted
        delete newChecker;

        cout << "\n*** END TEST BLOCK SIXTEEN***" << endl;
        
    }

    cout << "\n**********************" << endl;
    cout << "***** END TEST *******" << endl;
    cout << "**********************" << endl;
}