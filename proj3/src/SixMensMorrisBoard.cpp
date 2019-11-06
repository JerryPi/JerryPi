#include "SixMensMorrisBoard.h" 	  			 	 
#include <cctype>
#include <iostream>
#include <sstream>

// Default constructor should initialize the board.
CSixMensMorrisBoard::CSixMensMorrisBoard(){
    DTurn = SIX_MENS_MORRIS_PLAYER_R;
    for(int Index = 0; Index < SIX_MENS_MORRIS_PLAYERS; Index++){
        DUnplacedPieces[Index] = SIX_MENS_MORRIS_PIECES;
    }
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        DPositions[Index] = SIX_MENS_MORRIS_EMPTY;
        DPreviousPositions[Index] = SIX_MENS_MORRIS_EMPTY;
    }
}

// Constructor to specify a board setup with the piece at each
// location, the player turn, the number of unplaced pieces,
// and the previous board setup.
CSixMensMorrisBoard::CSixMensMorrisBoard(char turn, const int unplaced[SIX_MENS_MORRIS_PLAYERS], const char positions[SIX_MENS_MORRIS_POSITIONS], const char previous[SIX_MENS_MORRIS_POSITIONS]){
    DTurn = turn;
    for(int Index = 0; Index < SIX_MENS_MORRIS_PLAYERS; Index++){
        DUnplacedPieces[Index] = unplaced[Index];
    }
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        DPositions[Index] = positions[Index];
        DPreviousPositions[Index] = previous[Index];
    }
}

// Return true If there is three pieces in a row (either horizontal or vertical), they have
// formed a mill, else Return false.
bool CSixMensMorrisBoard::MillCreated(char player){
    int PotentialMills[8][3] = {{0x0, 0x1, 0x2},
                                {0x3, 0x4, 0x5},
                                {0xA, 0xB, 0xC},
                                {0xD, 0xE, 0xF},
                                {0x0, 0x6, 0xD},
                                {0x3, 0x7, 0xA},
                                {0x5, 0x8, 0xC},
                                {0x2, 0x9, 0xF}};
    for(int Index = 0; Index < 8; Index++){
        bool CurrentMill = true;
        bool PastMill = true; // for old mill.
        char CurrentFirst = DPositions[PotentialMills[Index][0]];
        char PastFirst = DPreviousPositions[PotentialMills[Index][0]];
        if(CurrentFirst != player){
            continue;
        }
        for(int Inner = 1; Inner < 3; Inner++){
            if(CurrentFirst != DPositions[PotentialMills[Index][Inner]]){
                CurrentMill = false;
                break;
            }
            if(PastFirst != DPreviousPositions[PotentialMills[Index][Inner]]){
                PastMill = false;
            }
        }
        if(CurrentMill and not PastMill){
            // std::cout << "Index: " << Index << std::endl;
            return true;   
        }
    }
    return false;
}

// check from and to position is Adjacent.
bool CSixMensMorrisBoard::AdjacentPositions(int from, int to){
    int Adjacents[SIX_MENS_MORRIS_POSITIONS] = {0x0042, 0x0015, 0x0202,
                                                0x0090, 0x002A, 0x0110,
                                                0x2081, 0x0448, 0x1220,
                                                0x8104, 0x0880, 0x5400,
                                                0x0900, 0x4040, 0xA800,
                                                0x4200};
    // std::cout << to <<": " << (Adjacents[from] & (1 <<to)) << std::endl;
    
    return Adjacents[from] & (1<<to);
}

// Resets the board back to initial setup.
void CSixMensMorrisBoard::ResetBoard(){
    DTurn = SIX_MENS_MORRIS_PLAYER_R;
    for(int Index = 0; Index < SIX_MENS_MORRIS_PLAYERS; Index++){
        DUnplacedPieces[Index] = SIX_MENS_MORRIS_PIECES;
    }
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        DPositions[Index] = SIX_MENS_MORRIS_EMPTY;
        DPreviousPositions[Index] = SIX_MENS_MORRIS_EMPTY;
    }
}

// Returns which player's turn it is.
char CSixMensMorrisBoard::PlayerTurn() const{
    return toupper(DTurn);
}

// Returns the player at the particular position, '\0' should be
// returned on bad parameter.
char CSixMensMorrisBoard::PlayerAtPosition(int position) const{
    if((0 <= position) and (position <= SIX_MENS_MORRIS_POSITIONS)){
        return DPositions[position];   
    }
    return '\0';
}

// Returns the number of pieces left for the player to place,
// returns -1 on bad parameter.
int CSixMensMorrisBoard::UnplacedPieces(char player) const{
    if(SIX_MENS_MORRIS_PLAYER_R == player){
        return DUnplacedPieces[0];
    }
    if(SIX_MENS_MORRIS_PLAYER_W == player){
        return DUnplacedPieces[1];
    }
    return -1;
}

// Returns true if the game is over.
// A player wins if their opponent is reduced to two pieces, or if their opponent has no
// legal moves 
bool CSixMensMorrisBoard::GameOver() {
    char player = DTurn;
    int piece_cnt = UnplacedPieces(player);
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        if (DPositions[Index] == player) {
            piece_cnt += 1;
        }
    }
    if (piece_cnt <= 2) {
        DTurn = opponentPlayer();
        return true;
    }
    int cannot_move = 0;
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        if (DPositions[Index] == player && !CanMove(player, Index)) {
            cannot_move += 1;
        }
    }
    // std::cout << player << ":" << cannot_move << std::endl;
    if (cannot_move == piece_cnt) {
        DTurn = opponentPlayer();
        return true;
    }
    return false;
}

// format CSixMensMorrisBoard.
std::string CSixMensMorrisBoard::ToString() const{
    std::stringstream OutStream;
    int CapturedR, CapturedW;
    
    CapturedR = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[0];
    CapturedW = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[1];
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_R){
            CapturedR--;   
        }
        else if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_W){
            CapturedW--;   
        }
    }
    OutStream<<(DTurn == SIX_MENS_MORRIS_PLAYER_R ? ">RU:" : " RU:")<<DUnplacedPieces[0]<<" RC:"<<CapturedW<<(DTurn == SIX_MENS_MORRIS_PLAYER_W ? " >WU:" : "  WU:")<<DUnplacedPieces[1]<<" WC:"<<CapturedR<<std::endl;
    OutStream<<DPositions[0x0]<<"---------"<<DPositions[0x1]<<"---------"<<DPositions[0x2]<<"      0---1---2"<<std::endl;
    OutStream<<"|         |         |      | 3-4-5 |"<<std::endl;
    OutStream<<"|         |         |      6-7   8-9"<<std::endl;
    OutStream<<"|    "<<DPositions[0x3]<<"----"<<DPositions[0x4]<<"----"<<DPositions[0x5]<<"    |      | A-B-C |"<<std::endl;
    OutStream<<"|    |         |    |      D---E---F"<<std::endl;
    OutStream<<"|    |         |    |        LEGEND"<<std::endl;
    OutStream<<DPositions[0x6]<<"----"<<DPositions[0x7]<<"         "<<DPositions[0x8]<<"----"<<DPositions[0x9]<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    "<<DPositions[0xA]<<"----"<<DPositions[0xB]<<"----"<<DPositions[0xC]<<"    |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<DPositions[0xD]<<"---------"<<DPositions[0xE]<<"---------"<<DPositions[0xF]<<std::endl;
    
    return OutStream.str();
}

CSixMensMorrisBoard::operator std::string() const{
    std::stringstream OutStream;
    int CapturedR, CapturedW;
    
    CapturedR = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[0];
    CapturedW = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[1];
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_R){
            CapturedR--;   
        }
        else if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_W){
            CapturedW--;   
        }
    }
    OutStream<<(DTurn == SIX_MENS_MORRIS_PLAYER_R ? ">RU:" : " RU:")<<DUnplacedPieces[0]<<" RC:"<<CapturedW<<(DTurn == SIX_MENS_MORRIS_PLAYER_W ? " >WU:" : "  WU:")<<DUnplacedPieces[1]<<" WC:"<<CapturedR<<std::endl;
    OutStream<<DPositions[0x0]<<"---------"<<DPositions[0x1]<<"---------"<<DPositions[0x2]<<"      0---1---2"<<std::endl;
    OutStream<<"|         |         |      | 3-4-5 |"<<std::endl;
    OutStream<<"|         |         |      6-7   8-9"<<std::endl;
    OutStream<<"|    "<<DPositions[0x3]<<"----"<<DPositions[0x4]<<"----"<<DPositions[0x5]<<"    |      | A-B-C |"<<std::endl;
    OutStream<<"|    |         |    |      D---E---F"<<std::endl;
    OutStream<<"|    |         |    |        LEGEND"<<std::endl;
    OutStream<<DPositions[0x6]<<"----"<<DPositions[0x7]<<"         "<<DPositions[0x8]<<"----"<<DPositions[0x9]<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    "<<DPositions[0xA]<<"----"<<DPositions[0xB]<<"----"<<DPositions[0xC]<<"    |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<DPositions[0xD]<<"---------"<<DPositions[0xE]<<"---------"<<DPositions[0xF]<<std::endl;
    
    return OutStream.str();
}

// Places a piece at the location specified by where. If the
// placement failed, or it is not the player's turn Place should
// return false. If the placement succeeds true should be
// returned.
bool CSixMensMorrisBoard::Place(char player, int where){
    int UnplacedIndex = player == SIX_MENS_MORRIS_PLAYER_R ? 0 : 1;
    if((player == DTurn) and DUnplacedPieces[UnplacedIndex]){
        if((0 <= where) and (where < SIX_MENS_MORRIS_POSITIONS)){
            if(SIX_MENS_MORRIS_EMPTY == DPositions[where]){
                for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
                    DPreviousPositions[Index] = DPositions[Index];       
                }
                DPositions[where] = player;
                DUnplacedPieces[UnplacedIndex]--;
                DTurn = opponentPlayer();
                return true;
            }
        }
    }
    return false;
}

// opponent Player
char CSixMensMorrisBoard::opponentPlayer() const {
    return DTurn == SIX_MENS_MORRIS_PLAYER_R ? SIX_MENS_MORRIS_PLAYER_W : SIX_MENS_MORRIS_PLAYER_R;

}

// Returns true if the player can remove an opponents piece,
// otherwise returns false. Returns false on invalid parameter.
bool CSixMensMorrisBoard::CanRemove(char player){
    return ((opponentPlayer() == player) and MillCreated(player));
}

// Returns true if the player can move their piece located at
// position specified by where, otherwise returns false. Returns
// false on invalid parameter.
bool CSixMensMorrisBoard::CanMove(char player, int where) {
    if((SIX_MENS_MORRIS_PLAYER_R == player) or (SIX_MENS_MORRIS_PLAYER_W == player)){
        if((0 <= where) and (where < SIX_MENS_MORRIS_POSITIONS)){
            if(player == DPositions[where]){
                for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){     
                    if(SIX_MENS_MORRIS_EMPTY == (DPositions[Index]) and AdjacentPositions(where,Index)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// Does a move for the player, by taking the piece from the
// from specified position and moving it to the to specified
// position. If the move failed, or it is not the player's
// turn Move should return false. If the move succeeds true
// should be returned.
bool CSixMensMorrisBoard::Move(char player, int from, int to){
    int UnplacedIndex = player == SIX_MENS_MORRIS_PLAYER_R ? 0 : 1;
    if((player == DTurn) and (0 == DUnplacedPieces[UnplacedIndex])){
        if((0 <= from) and (from < SIX_MENS_MORRIS_POSITIONS)){
            if(player == DPositions[from]){
                if((0 <= to) and (to < SIX_MENS_MORRIS_POSITIONS) and (SIX_MENS_MORRIS_EMPTY ==  DPositions[to]) and AdjacentPositions(from, to)){
                    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
                        DPreviousPositions[Index] = DPositions[Index];       
                    }
                    DPositions[to] = player;
                    DPositions[from] = SIX_MENS_MORRIS_EMPTY;
                    DTurn = opponentPlayer();
                    return true;
                }
            }
        }
    }
    return false;
}

// Removes an opponent's piece from the position specified by
// from. Upon successful removal of the opponent's piece true is
// returned. If the player cannot remove the opponent's piece,
// or bad parameters are entered, false should be returned.
bool CSixMensMorrisBoard::Remove(char player, int from){
    if(CanRemove(player)and (0 <= from) and (from < SIX_MENS_MORRIS_POSITIONS)){
        char OtherPlayer = DTurn;
        if(DPositions[from] == OtherPlayer){
            DPositions[from] = SIX_MENS_MORRIS_EMPTY;
            // int UnplacedIndex = OtherPlayer == SIX_MENS_MORRIS_PLAYER_R ? 0 : 1;
            // int PlayerCount = DUnplacedPieces[UnplacedIndex];

            // for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
            //     if(DPositions[Index] == OtherPlayer){
            //         PlayerCount++;
            //     }
            // }
            // if(PlayerCount <= 2){
            //     DTurn = tolower(DTurn);
            //     return true;
            // }
            // bool HasMove = false;
            // for(int From = 0; From < SIX_MENS_MORRIS_POSITIONS; From++){
            //     if(DPositions[From] == OtherPlayer){
            //         for(int To = 0; To < SIX_MENS_MORRIS_POSITIONS; To++){
            //             if(From == To){
            //                 continue;    
            //             }
            //             if((SIX_MENS_MORRIS_EMPTY == DPositions[To]) and AdjacentPositions(From,To)){
            //                 HasMove = true;
            //                 break;
            //             }
            //         }
            //         if(HasMove){
            //             break;   
            //         }
            //     }       
            // }
            // if(HasMove){
            //     DTurn = OtherPlayer;
            // }
            // else{
            //     DTurn = tolower(DTurn);   
            // }
            return true;
        }
    }
    return false;
}
