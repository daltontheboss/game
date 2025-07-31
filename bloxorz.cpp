#include <iostream> // For input/output operations (cin, cout)
#include <vector>   // For using vector to create the game board
#include <string>   // For using string for input
#include <limits> // For numeric_limits (to clear input buffer)

using namespace std;

// Function to clear the console screen
// Note: This is OS-dependent and might not work on all systems.
// For Windows: system("cls"); For Unix/Linux/macOS: system("clear");
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Enum for movement directions
enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    INVALID
};

// Function to get a valid move from the player
Direction getMove() {
    string moveInput;
    while (true) {
        cout << "Enter move (w/a/s/d for up/left/down/right): ";
        cin >> moveInput;

        // Clear the input buffer to prevent issues with subsequent inputs
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (moveInput == "w") return UP;
        if (moveInput == "s") return DOWN;
        if (moveInput == "a") return LEFT;
        if (moveInput == "d") return RIGHT;
        
        cout << "Invalid move. Please use 'w', 'a', 's', or 'd'." << endl;
    }
}

// Class to represent the game board and game logic
class GameBoard {
public:
    // Constructor to initialize the board
    GameBoard(int rows, int cols, pair<int, int> startPos, pair<int, int> endPos)
        : rows_(rows), cols_(cols), startPos_(startPos), endPos_(endPos) {
        
        // Initialize the board with empty spaces
        board_.resize(rows_, vector<char>(cols_, '.'));

        // Place the block and the hole
        board_[startPos_.first][startPos_.second] = 'B'; // Block
        board_[endPos_.first][endPos_.second] = 'H';     // Hole

        currentPos_ = startPos_; // Set initial block position
    }

    // Print the current state of the board
    void printBoard() const {
        for (int i = 0; i < rows_; ++i) {
            for (int j = 0; j < cols_; ++j) {
                cout << board_[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Move the block based on the given direction
    bool moveBlock(Direction dir) {
        int newRow = currentPos_.first;
        int newCol = currentPos_.second;

        // Calculate new position based on direction
        switch (dir) {
            case UP:    newRow--; break;
            case DOWN:  newRow++; break;
            case LEFT:  newCol--; break;
            case RIGHT: newCol++; break;
            default: return false; // Should not happen with valid input
        }

        // Check if the new position is within board boundaries
        if (newRow >= 0 && newRow < rows_ && newCol >= 0 && newCol < cols_) {
            // Update board: clear old position, set new position
            board_[currentPos_.first][currentPos_.second] = '.';
            currentPos_ = {newRow, newCol};
            board_[currentPos_.first][currentPos_.second] = 'B';
            return true; // Move successful
        } else {
            return false; // Fell off the board
        }
    }

    // Check if the block has reached the hole
    bool hasWon() const {
        return currentPos_ == endPos_;
    }

private:
    int rows_;
    int cols_;
    vector<std::vector<char>> board_; // 2D vector for the board
    pair<int, int> startPos_;
    pair<int, int> endPos_;
    pair<int, int> currentPos_; // Current position of the block
};

int main() {
    int rows = 5;
    int cols = 5;
    pair<int, int> startPos = {0, 0};
    pair<int, int> endPos = {rows - 1, cols - 1};

    GameBoard game(rows, cols, startPos, endPos);

    cout << "Welcome to Block Fall!" << endl;
    cout << "Move the 'B' block to the 'H' hole." << endl;
    cout << "Don't fall off the board!" << endl;

    while (true) {
        clearScreen();
        game.printBoard();

        if (game.hasWon()) {
            cout << "Congratulations! You reached the hole!" << endl;
            break;
        }

        Direction move = getMove();
        if (!game.moveBlock(move)) {
            cout << "Oops! You fell off the board! Game Over." << endl;
            break;
        }
    }

    return 0;
}