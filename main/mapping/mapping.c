#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to represent a cell in the maze
typedef struct {
    int cellNumber;
    int x;             // x-coordinate of the cell
    int y;             // y-coordinate of the cell
    bool northWall;    // Boolean value for the north wall existence
    bool southWall;    // Boolean value for the south wall existence
    bool eastWall;     // Boolean value for the east wall existence
    bool westWall;     // Boolean value for the west wall existence
    // Add any other relevant information for the cell here
} Cell;

typedef struct {
    bool northWall;
    bool southWall;
    bool eastWall;
    bool westWall;
} CellWall;

// Array to hold a list of CellWall instances
CellWall cellWallsList[3]; // Assuming to store walls for the next 3 cells

// Function to update the walls of a cell based on the next walls in the cellWallsList
void updateCellWalls(Cell* cell) {
    if (cell != NULL) {
        cell->northWall = cellWallsList[0].northWall;
        cell->southWall = cellWallsList[0].southWall;
        cell->eastWall = cellWallsList[0].eastWall;
        cell->westWall = cellWallsList[0].westWall;

        // Shift the remaining walls in the list forward
        for (int i = 0; i < 2; ++i) {
            cellWallsList[i] = cellWallsList[i + 1];
        }
    }
}

// Function to add a cell to the maze with updated walls
void addCellToListWithWalls(Cell* cell, Cell** maze, int mazeSize) {
    if (cell != NULL && maze != NULL) {
        updateCellWalls(cell); // Update walls for the new cell
        maze[mazeSize] = cell;
    }
}

char facing_direction[] = "North";
int current_coords[2];
// Static variable to keep track of the cell number
static int cellCounter = 0;

// Function to create a new cell
Cell* createCell(int x, int y) {
    Cell* newCell = (Cell*)malloc(sizeof(Cell));
    if (newCell != NULL) {
        newCell->cellNumber = cellCounter; 
        newCell->x = x;
        newCell->y = y;
        newCell->northWall = false;  // Initially, all walls are considered present
        newCell->southWall = false;
        newCell->eastWall = false;
        newCell->westWall = false;
        // Initialize any other cell-specific information here
    }
    cellCounter++;
    return newCell;
}

// Function to add a cell to the maze
void addCellToList(Cell* cell, Cell** maze, int mazeSize) {
    if (cell != NULL && maze != NULL) {
        maze[mazeSize] = cell;
    }
}

// Function to turn left by 90 degrees
void turnLeft90() {
    printf("Trigger Turning Left 90\n");

    // Update direction based on current facing_direction using switch statement
    switch (facing_direction[0]) {
        case 'N':
            strcpy(facing_direction, "West");
            break;
        case 'W':
            strcpy(facing_direction, "South");
            break;
        case 'S':
            strcpy(facing_direction, "East");
            break;
        case 'E':
            strcpy(facing_direction, "North");
            break;
        default:
            break;
    }
}

// Function to turn right by 90 degrees
void turnRight90() {
    printf("Trigger Turning Right 90\n");

    // Update direction based on current facing_direction using switch statement
    switch (facing_direction[0]) {
        case 'N':
            strcpy(facing_direction, "East");
            break;
        case 'E':
            strcpy(facing_direction, "South");
            break;
        case 'S':
            strcpy(facing_direction, "West");
            break;
        case 'W':
            strcpy(facing_direction, "North");
            break;
        default:
            break;
    }
}


bool checkFrontWall(Cell** maze, int maxCells){
    if (maze != NULL) {
        // Check every cell
        for (int i = 0; i < maxCells; ++i) {
            // Check for current cell
            if (maze[i] != NULL && maze[i]->x == current_coords[0] && maze[i]->y == current_coords[1]) {
                switch (facing_direction[0])
                {
                case 'N':
                    if (maze[i]->northWall) {
                        printf("Wall in front, turning left...\n");
                        turnLeft90();
                        return false; // Don't move forward, turn left instead
                    }
                    break;
                case 'S':
                if (maze[i]->southWall) {
                        printf("Wall in front, turning left...\n");
                        turnLeft90();
                        return false; // Don't move forward, turn left instead
                    }
                    break;

                case 'E':
                    if (maze[i]->eastWall) {
                        printf("Wall in front, turning left...\n");
                        turnLeft90();
                        return false; // Don't move forward, turn left instead
                    }
                    break;
                    
                case 'W':
                    if (maze[i]->westWall) {
                        printf("Wall in front, turning left...\n");
                        turnLeft90();
                        return false; // Don't move forward, turn left instead
                    }
                    break;
                
                default:
                    break;
                }
            }
        }
    }
    return true; // No wall detected, can move forward
}
// Function to check the wall in the current direction before moving forward
bool checkWall(Cell** maze, int maxCells) {

    switch (facing_direction[0]) {
        case 'N':
            // Check if facing North and the north wall of the current cell is true
            if (maze != NULL) {
                for (int i = 0; i < maxCells; ++i) {
                    if (maze[i] != NULL && maze[i]->x == current_coords[0] && maze[i]->y == current_coords[1]) {
                        if (maze[i]->northWall) {
                            printf("Wall in front, turning left...\n");
                            turnLeft90();
                            return false; // Don't move forward, turn left instead
                        }
                    }
                }
            }
            break;
        case 'S':
            // Check if facing South and the south wall of the current cell is true
            // ... Similar code to check South wall
            break;
        case 'E':
            // Check if facing East and the east wall of the current cell is true
            // ... Similar code to check East wall
            break;
        case 'W':
            // Check if facing West and the west wall of the current cell is true
            // ... Similar code to check West wall
            break;
        default:
            break;
    }

    return true; // No wall detected, can move forward
}

// Function to move forward
bool moveForward(Cell** maze, int maxCells) {

    int nextX = current_coords[0];
    int nextY = current_coords[1];
    printf("Trigger Move Forward\n");

    // Check for walls before moving forward
    if (!checkFrontWall(maze, maxCells)) {
        return false; // Don't update coordinates, turn left instead
    }

    // Update coordinates based on current facing_direction using switch statement
    switch (facing_direction[0]) {
        case 'N':
            current_coords[1]++;
            break;
        case 'S':
            current_coords[1]--;
            break;
        case 'E':
            current_coords[0]++;
            break;
        case 'W':
            current_coords[0]--;
            break;
        default:
            break;
    }
    printf("Current coordinates: (%d, %d)\n", current_coords[0], current_coords[1]);
    return true;
}

bool moveBackward(Cell** maze, int maxCells) {

    int nextX = current_coords[0];
    int nextY = current_coords[1];
    printf("Trigger Move Backward\n");

    // Check for walls before moving backward

    // Update coordinates based on current facing_direction using switch statement
    switch (facing_direction[0]) {
        case 'N':
            current_coords[1]--;
            break;
        case 'S':
            current_coords[1]++;
            break;
        case 'E':
            current_coords[0]--;
            break;
        case 'W':
            current_coords[0]++;
            break;
        default:
            break;
    }
    printf("Current coordinates: (%d, %d)\n", current_coords[0], current_coords[1]);
    return true;
}

// Function to print the coordinates of explored cells in the maze
void printExploredCells(Cell** maze, int maxCells) {
    printf("Explored Coordinates in the Maze:\n");
    for (int i = 0; i < maxCells; ++i) {
        if (maze[i] != NULL) {
            printf("Coordinates: (%d, %d)\n", maze[i]->x, maze[i]->y);
            printf("Walls - North: %s, South: %s, East: %s, West: %s\n",
                   maze[i]->northWall ? "True" : "False",
                   maze[i]->southWall ? "True" : "False",
                   maze[i]->eastWall ? "True" : "False",
                   maze[i]->westWall ? "True" : "False");
        }
    }
    printf("\n");
}
// Function to print details of current cell
void printCurrentCell(Cell** maze, int maxCells, int currentX, int currentY) {
    bool cellFound = false;

    // Search for the current cell in the maze
    for (int i = 0; i < maxCells; ++i) {
        if (maze[i] != NULL && maze[i]->x == currentX && maze[i]->y == currentY) {
            cellFound = true;
            
            printf("--------Cell %d--------\n", maze[i]->cellNumber);
            printf("Coordinates: (%d, %d)\n", maze[i]->x, maze[i]->y);
            printf("Walls - North: %s, South: %s, East: %s, West: %s\n",
                   maze[i]->northWall ? "True" : "False",
                   maze[i]->southWall ? "True" : "False",
                   maze[i]->eastWall ? "True" : "False",
                   maze[i]->westWall ? "True" : "False");
            break;
        }
    }

    if (!cellFound) {
        printf("No data available for current cell coordinates: (%d, %d)\n", currentX, currentY);
    }
}

// Function to get the current cell based on coordinates
Cell* getCurrentCell(Cell** maze, int maxCells, int currentX, int currentY) {
    for (int i = 0; i < maxCells; ++i) {
        if (maze[i] != NULL && maze[i]->x == currentX && maze[i]->y == currentY) {
            return maze[i];
        }
    }
    return NULL; // If the cell doesn't exist
}

// Function to set a wall (true or false) in the current cell based on direction
void setWallCurrentCell(Cell** maze, int maxCells, int currentX, int currentY, char direction, bool value) {
    Cell* currentCell = getCurrentCell(maze, maxCells, currentX, currentY);
    if (currentCell != NULL) {
        switch (direction) {
            case 'N':
                currentCell->northWall = value;
                break;
            case 'S':
                currentCell->southWall = value;
                break;
            case 'E':
                currentCell->eastWall = value;
                break;
            case 'W':
                currentCell->westWall = value;
                break;
            default:
                printf("Invalid direction provided!\n");
                break;
        }
    } else {
        printf("Current cell not found at coordinates: (%d, %d)\n", currentX, currentY);
    }
}

// Example usage
int main() {
    // Assuming the starting point of the maze is (0, 0)
    int currentX = 0;
    int currentY = -1;

    // Update cellWallsList with example walls (customize these based on your maze structure)
    cellWallsList[0] = (CellWall){.northWall = false, .southWall = true, .eastWall = true, .westWall = true};
    cellWallsList[1] = (CellWall){.northWall = true, .southWall = false, .eastWall = false, .westWall = true};
    cellWallsList[2] = (CellWall){.northWall = false, .southWall = true, .eastWall = true, .westWall = false};

    // Create an array to store the cells in the maze (adjust the size as needed)
    int maxCells = 100;  // For example, assuming a maximum of 100 cells
    Cell** maze = (Cell**)malloc(maxCells * sizeof(Cell*));

    // Create the initial cell at the starting point
    Cell* startingCell = createCell(currentX, currentY);
    if (startingCell != NULL) {
        // Set the initial walls of the starting cell based on your description
        startingCell->cellNumber = cellCounter;
        startingCell->northWall = false;  // Assuming the starting cell has no northern wall
        startingCell->southWall = false;
        startingCell->eastWall = true;
        startingCell->westWall = true;

        // Add the starting cell to the maze
        addCellToList(startingCell, maze, 0);  // Adding the starting cell at index 0
    }

    // Now, as the car moves through the maze and discovers new cells,
    // create new Cell structures and add them to the maze list with updated wall information.


    for (int i = 0; i < maxCells; ++i) {
        maze[i] = NULL;
    }
    char action;
    int move = 1;
    bool cellExists=false;
    while (1){
        // Cell* currentCell = getCurrentCell(maze, currentX, currentY, maxCells);
        printCurrentCell(maze, maxCells, current_coords[0], current_coords[1]);
        move++;
        printf("You are now facing: %s\n", facing_direction);
        printf("Enter your next action \n l, r, f, b, w\n");

        // Add a space before %c to consume leading whitespace including newline characters
        scanf(" %c", &action);
        switch (action)
        {
        case 'l':
            turnLeft90();
            break;
        case 'r':
            turnRight90();
            break;
        case 'f':
            moveForward(maze, maxCells);
            // Check if a cell with current coordinates exists in the maze
            cellExists = false;
            for (int i = 0; i < maxCells; ++i) {
                if (maze[i] != NULL && maze[i]->x == current_coords[0] && maze[i]->y == current_coords[1]) {
                    cellExists = true;
                    break;
                }
            }

            // If a cell with current coordinates doesn't exist, create a new cell and add it to the maze
            if (!cellExists) {
                printf("Creating new cell...\n\n");
                Cell* newCell = createCell(current_coords[0], current_coords[1]);
                if (newCell != NULL) {
                    addCellToListWithWalls(newCell, maze, maxCells);
                    maxCells++; // Increment the count of cells in the maze
                }
            }
            printExploredCells(maze, maxCells);
            break;
        case 'b':
            moveBackward(maze, maxCells);
            // Check if a cell with current coordinates exists in the maze
            cellExists = false;
            for (int i = 0; i < maxCells; ++i) {
                if (maze[i] != NULL && maze[i]->x == current_coords[0] && maze[i]->y == current_coords[1]) {
                    cellExists = true;
                    break;
                }
            }

            // If a cell with current coordinates doesn't exist, create a new cell and add it to the maze
            if (!cellExists) {
                printf("Creating new cell...\n\n");
                Cell* newCell = createCell(current_coords[0], current_coords[1]);
                if (newCell != NULL) {
                    addCellToListWithWalls(newCell, maze, maxCells);
                    maxCells++; // Increment the count of cells in the maze
                }
            }
            printExploredCells(maze, maxCells);
            break;
        case 'w':
            char wall;
            printf("Choose a wall to open\n N, S, E, W\n");
            scanf(" %c", &wall);
            setWallCurrentCell(maze, maxCells, current_coords[0], current_coords[1], wall, false);
            break;
        default:
            break;
        }
    }

    // After the car has traversed through the maze, you can access the maze data
    // stored in the 'maze' array, which contains the Cell structures with wall information.

    // Remember to free the allocated memory for the maze when done
    for (int i = 0; i < maxCells; ++i) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}
