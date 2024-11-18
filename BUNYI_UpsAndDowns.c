/*
    DESCRIPTION:
        This program is titled "Ups and Downs". It is a two-player game where two players begin at
        a starting point and race to reach the end of a 10 x 10 board. The two players alternate in
        turns; each move is pseudo-randomized through a die roll simulation, with the face value
        determining how many spaces forward the player moves for that turn. Some special rules are
        also applied, such as up and down tiles transporting a player to another connected tile and
        a special move privilege when a player rolls a '1' for two consecutive turns. Some bonus
        features have also been implemented, such as the ability to start a new game upon finishing
        and place a down tile and its link anywhere valid on the board affecting only the opponent.

    AUTHOR:
        Christian Joseph C. Bunyi - S17

    ACKNOWLEDGMENTS:
        1. Die ASCII Art by @author: valkyrie
        2. Text to ASCII Art Generator by @author: patorjk
        3. ASCII codes from https://theasciicode.com.ar/
*/


// preprocessor directives
#include <stdio.h>
#include <time.h>
#include <windows.h>


/*
    @brief: prints the game title ASCII art
*/
void printTitle() {
    printf(
        "  _   _                             _   ____                          \n"
        " | | | |_ __  ___    __ _ _ __   __| | |  _ \\  _____      ___ __  ___ \n"
        " | | | | '_ \\/ __|  / _` | '_ \\ / _` | | | | |/ _ \\ \\ /\\ / / '_ \\/ __|\n"
        " | |_| | |_) \\__ \\ | (_| | | | | (_| | | |_| | (_) \\ V  V /| | | \\__ \\\n"
        "  \\___/| .__/|___/  \\__,_|_| |_|\\__,_| |____/ \\___/ \\_/\\_/ |_| |_|___/\n"
        "       |_|                                                            \n"
    );

    return;
}


/*
    @brief: prints the game title with die ASCII art
*/
void printTitleWithDie() {
    printf(
        "\n                                                                                        _______\n"
        "      ______      _   _                             _   ____                           | .   . |\\\n"
        "     /     /\\    | | | |_ __  ___    __ _ _ __   __| | |  _ \\  _____      ___ __  ___  |   .   |.\\\n"
        "    /  '  /  \\   | | | | '_ \\/ __|  / _` | '_ \\ / _` | | | | |/ _ \\ \\ /\\ / / '_ \\/ __| | .   . |.'|\n"
        "   /_____/. . \\  | |_| | |_) \\__ \\ | (_| | | | | (_| | | |_| | (_) \\ V  V /| | | \\__ \\ |_______|.'|\n"
        "   \\ . . \\    /   \\___/| .__/|___/  \\__,_|_| |_|\\__,_| |____/ \\___/ \\_/\\_/ |_| |_|___/  \\ ' .   \\'|\n"
        "    \\ . . \\  /         |_|                                                               \\____'__\\|\n"
        "     \\_____\\/\n\n"
    );
    printf("                           A CCPROG1 project by Christian Joseph C. Bunyi.\n");
    printf("                                        Press enter to play.\n\n");

    return;
}


/*
    @brief: prints the die ASCII art
*/
void printDie() {
    printf(
        "                 _______\n"
        "      ______    | .   . |\\\n"
        "     /     /\\   |   .   |.\\\n"
        "    /  '  /  \\  | .   . |.'|\n"
        "   /_____/. . \\ |_______|.'|\n"
        "   \\ . . \\    /  \\ ' .   \\'|\n"
        "    \\ . . \\  /    \\____'__\\|\n"
        "     \\_____\\/\n\n"
    );

    return;
}


/*
    @brief: prints the die with rolling motion ASCII art
*/
void printDieRoll() {
    printf(
        "              (( _______\n"
        "      ______    | .   . |\\\n"
        "     /     /\\   |   .   |.\\  ))\n"
        "    /  '  /  \\  | .   . |.'|\n"
        "(( /_____/. . \\ |_______|.'|\n"
        "   \\ . . \\    /  \\ ' .   \\'|\n"
        "    \\ . . \\  /    \\____'__\\|\n"
        "     \\_____\\/ ))             ))\n"
        "   ((\n\n"
    );

    return;
}


/*
    @brief: prints the upper border ASCII of the board representation
*/
void printUpperBorder() {
    int i;

    printf("%c%c%c%c", 218, 196, 196, 196);
    for (i = 0; i < 9; i++) {
        printf("%c%c%c%c", 194, 196, 196, 196);
    }
    printf("%c\n", 191);

    return;
}


/*
    @brief: prints the middle border ASCII of the board representation
*/
void printMiddleBorder() {
    int i;

    printf("%c%c%c%c", 195, 196, 196, 196);
    for (i = 0; i < 9; i++) {
        printf("%c%c%c%c", 197, 196, 196, 196);
    }
    printf("%c\n", 180);

    return;
}


/*
    @brief: prints the lower border ASCII of the board representation
*/
void printLowerBorder() {
    int i;

    printf("%c%c%c%c", 192, 196, 196, 196);
    for (i = 0; i < 9; i++) {
        printf("%c%c%c%c", 193, 196, 196, 196);
    }
    printf("%c\n", 217);

    return;
}


/*
    @brief: checks if any player has won the game given their locations
   
    @pre: assumes parameters are between 1 and 100

    @param: nP1Loc - location of player 1
    @param: nP2Loc - location of player 2

    @return: 1 if any player has reached 100; otherwise, 0
*/
int nisWinnerFound(int nP1Loc, int nP2Loc) {
    return nP1Loc >= 100 || nP2Loc >= 100;
}


/*
    @brief: generates a pseudorandom integer between a range of numbers

    @pre: assumes parameters are nonnegative and nMin is less than or equal to nMax

    @param: nMin - minimum number in the range
    @param: nMax - maximum number in the range

    @return: pseudorandom-generated integer
*/
int ngetRandInt(int nMin, int nMax) {
    return nMin + rand() % (nMax - nMin + 1); // randomly generates an integer in the interval [nMin, nMax]
}


/*
    @brief: determines the row number of a particular location in the board

    @pre: assumes parameter is between 1 and 100

    @param: nLoc - some location on the board

    @return: integer row number of the location
*/
int ngetRow(int nLoc) {
    return (nLoc - 1) / 10 + 1; // we subtract 1 to prevent locations ending in 0s to be off by a row
}


/*
    @brief: swaps the values of two integers

    @pre: assumes both integers are between 1 and 100

    @param: *nNum1 - pointer to the first integer
    @param: *nNum2 - pointer to the second integer
*/
void swapInts(int *nNum1, int *nNum2) {
    int temp = *nNum1;
    *nNum1 = *nNum2;
    *nNum2 = temp;
    return;
}


/*
    @brief: clears the input buffer after a user response
*/
void clearInputBuffer() {
    while (getchar() != '\n'); // gets user input from the input stream char by char until a newline is encountered
    return;
}


/*
    @brief: prints the game initialization sequence and enables both players to set their personal
        down tile locations

    @pre: assumes all parameters are set to 0

    @param: *nP1DownStart - pointer to the location of player 1's custom down tile origin
    @param: *nP1DownEnd - pointer to the location of player 1's custom down tile destination
    @param: *nP2DownStart - pointer to the location of player 2's custom down tile origin
    @param: *nP2DownEnd - pointer to the location of player 2's custom down tile destination
*/
void initializeGame(int *nP1DownStart, int *nP1DownEnd, int *nP2DownStart, int *nP2DownEnd) {
    char cTemp;

    printTitleWithDie();
    scanf("%c", &cTemp);
    Sleep(1000);

    printf("To make the game more interesting, both players will be allowed to place a pair of ");
    printf("connected down tiles that only affect the other player.\n\n");
    Sleep(2000);

    printf("There are three (3) rules to keep in mind:\n");
    printf("1. No down tile can be placed on the first or last rows (i.e., only inputs between ");
    printf("11 and 90, inclusive, are allowed).\n");
    printf("2. The down tile origin's location must be greater than that of its corresponding ");
    printf("destination.\n");
    printf("3. By extension, you cannot place a down tile origin on the lowest unoccupied ");
    printf("location, as it would leave no valid destination.\n\n\n");
    Sleep(2500);

    printf("Let the drafting commence!\n");
    Sleep(1000);

    while (*nP1DownStart < 12 || *nP1DownStart > 90)
    { // loops until player selects a valid location that allows for a valid destination
        printf("\n\nInput Player 1's down tile origin: ");
        if (!scanf("%d", nP1DownStart) || *nP1DownStart < 11 || *nP1DownStart > 90) {
            printf("Please enter an integer between 11 and 90.");
            clearInputBuffer();
        } else if (*nP1DownStart < 12 || *nP1DownStart > 90) {
            printf("Choosing %d leaves no valid location for its destination. ", *nP1DownStart);
            printf("Please choose another integer between 11 and 90.");
            clearInputBuffer();
        } else {
            printf("Player 1 has successfully placed their down tile origin on location ");
            printf("%d.", *nP1DownStart);
        }
        Sleep(1000);
    }

    while (*nP1DownEnd < 11 || *nP1DownEnd > 90 || *nP1DownEnd >= *nP1DownStart)
    { // loops until player selects a valid location that is less than the origin
        printf("\n\nInput Player 1's down tile destination: ");
        if (!scanf("%d", nP1DownEnd) || *nP1DownEnd < 11 || *nP1DownEnd > 90) {
            printf("Please enter an integer between 11 and 90.");
            clearInputBuffer();
        } else if (*nP1DownEnd == *nP1DownStart) {
            printf("Location %d has already been taken. Please choose another ", *nP1DownEnd);
            printf("integer between 11 and 90.");
            clearInputBuffer();
        } else if (*nP1DownEnd > *nP1DownStart) {
            printf("Choosing location %d would create an invalid down tile pair. ", *nP1DownEnd);
            printf("Please choose another integer between 11 and 90 that is less than the origin.");
            clearInputBuffer();
        } else {
            printf("Player 1 has successfully placed their down tile destination on location ");
            printf("%d.", *nP1DownEnd);
        }
        Sleep(1000);
    }

    if (*nP1DownEnd == 11) {
        int nMinimum = 13 + ((*nP1DownStart) == 12 || (*nP1DownStart) == 13);
        while (*nP2DownStart < nMinimum || *nP2DownStart > 90 || *nP2DownStart == *nP1DownStart ||
               *nP2DownStart == *nP1DownEnd)
        { // loops until player selects a valid location that has not yet been chosen and allows for a valid destination
            printf("\n\nInput Player 2's down tile origin: ");
            if (!scanf("%d", nP2DownStart) || *nP2DownStart < 11 || *nP2DownStart > 90) {
                printf("Please enter an integer between 11 and 90.");
                clearInputBuffer();
            } else if (*nP2DownStart == *nP1DownStart || *nP2DownStart == *nP1DownEnd) {
                printf("Location %d has already been taken. Please choose another ", *nP2DownStart);
                printf("integer between 11 and 90.");
                clearInputBuffer();
            } else if (*nP2DownStart < nMinimum) {
                printf("Choosing %d leaves no valid location for its destination. ", *nP2DownStart);
                printf("Please choose another integer between 11 and 90.");
                clearInputBuffer();
            } else {
                printf("Player 2 has successfully placed their down tile origin on location ");
                printf("%d.", *nP2DownStart);
            }
            Sleep(1000);
        }
    }

    else {
        while (*nP2DownStart < 11 || *nP2DownStart > 90 || *nP2DownStart == 11 ||
               *nP2DownStart == *nP1DownStart || *nP2DownStart == *nP1DownEnd)
        { // loops until player selects a valid location that has not yet been chosen and allows for a valid destination
            printf("\n\nInput Player 2's down tile origin: ");
            if (!scanf("%d", nP2DownStart) || *nP2DownStart < 11 || *nP2DownStart > 90) {
                printf("Please enter an integer between 11 and 90.");
                clearInputBuffer();
            } else if (*nP2DownStart == *nP1DownStart || *nP2DownStart == *nP1DownEnd) {
                printf("Location %d has already been taken. Please choose another ", *nP2DownStart);
                printf("integer between 11 and 90.");
                clearInputBuffer();
            } else if (*nP2DownStart == 11) {
                printf("Choosing %d leaves no valid location for its destination. ", *nP2DownStart);
                printf("Please choose another integer between 11 and 90.");
                clearInputBuffer();
            } else {
                printf("Player 2 has successfully placed their down tile origin on location ");
                printf("%d.", *nP2DownStart);
            }
            Sleep(1000);
        }
    }

    while (*nP2DownEnd < 11 || *nP2DownEnd > 90 || *nP2DownEnd >= *nP2DownStart ||
           *nP2DownEnd == *nP1DownStart || *nP2DownEnd == *nP1DownEnd ||
           *nP2DownEnd == *nP2DownStart)
    { // loops until player selects a valid location that has not yet been chosen and is less than the origin
        printf("\n\nInput Player 2's down tile destination: ");
        if (!scanf("%d", nP2DownEnd) || *nP2DownEnd < 11 || *nP2DownEnd > 90) {
            printf("Please enter an integer between 11 and 90.");
            clearInputBuffer();
        } else if (*nP2DownEnd > *nP2DownStart) {
            printf("Choosing location %d would create an invalid down tile pair. ", *nP2DownEnd);
            printf("Please choose another integer between 11 and 90 that is less than the origin.");
            clearInputBuffer();
        } else if (*nP2DownEnd == *nP1DownStart || *nP2DownEnd == *nP1DownEnd ||
                   *nP2DownEnd == *nP2DownStart) {
            printf("Location %d has already been taken. Please choose another ", *nP2DownEnd);
                printf("integer between 11 and 90.");
            clearInputBuffer();
        } else {
            printf("Player 2 has successfully placed their down tile origin on location ");
            printf("%d.", *nP2DownEnd);
        }
        Sleep(1000);
    }

    printf("\n\nLoading the game...");
    Sleep(2000);
    system("cls");

    return;
}


/*
    @brief: checks if a pseudorandom generated integer is a valid location for a special tile
        given its intended type (up or down) and information about other special tile locations

    @pre: assumes nIsUpTile is 1 or 0
    @pre: assumes uninitialized special tiles are set to 0
    @pre: assumes both player's custom down tiles are set to valid locations

    @param: nIsUpTile - determines if the tile being generated is an up or down tile
    @param: nRandInt - random integer denoting the location of the special tile
    @param: nUpStart1 - location of the first up tile's origin
    @param: nUpStart2 - location of the second up tile's origin
    @param: nUpStart3 - location of the third up tile's origin
    @param: nUpEnd1 - location of the first up tile's destination
    @param: nUpEnd2 - location of the second up tile's destination
    @param: nUpEnd3 - location of the third up tile's destination
    @param: nDownStart1 - location of the first down tile's origin
    @param: nDownStart2 - location of the second down tile's origin
    @param: nDownStart3 - location of the third down tile's origin
    @param: nDownEnd1 - location of the first down tile's destination
    @param: nDownEnd2 - location of the second down tile's destination
    @param: nDownEnd3 - location of the third down tile's destination
    @param: nP1DownStart - location of player 1's custom down tile origin
    @param: nP1DownEnd - location of player 1's custom down tile destination
    @param: nP2DownStart - location of player 2's custom down tile origin
    @param: nP2DownEnd - location of player 2's custom down tile destination

    @return: 1 if the tile is unique in its row and is a regular tile given the random location;
        otherwise, 0
*/
int nisValidTile(int nIsUpTile, int nRandInt, int nUpStart1, int nUpStart2, int nUpStart3,
    int nUpEnd1, int nUpEnd2, int nUpEnd3, int nDownStart1, int nDownStart2, int nDownStart3,
    int nDownEnd1, int nDownEnd2, int nDownEnd3, int nP1DownStart, int nP1DownEnd, int nP2DownStart,
    int nP2DownEnd)
{
    int nRow = ngetRow(nRandInt);
    int nIsUniqueInRow, nIsRegularTile;

    // a tile is considered unique in its row if its row number is not equal to any other similar tile type
    if (nIsUpTile) {
        nIsUniqueInRow = nRow != ngetRow(nUpStart1) && nRow != ngetRow(nUpStart2);
        nIsUniqueInRow = nIsUniqueInRow && nRow != ngetRow(nUpStart3) && nRow != ngetRow(nUpEnd1);
        nIsUniqueInRow = nIsUniqueInRow && nRow != ngetRow(nUpEnd2) && nRow != ngetRow(nUpEnd3);
    } else {
        nIsUniqueInRow = nRow != ngetRow(nDownStart1) && nRow != ngetRow(nDownStart2);
        nIsUniqueInRow = nIsUniqueInRow && nRow != ngetRow(nDownStart3) && nRow != ngetRow(nDownEnd1);
        nIsUniqueInRow = nIsUniqueInRow && nRow != ngetRow(nDownEnd2) && nRow != ngetRow(nDownEnd3);
    }

    // a tile is considered regular if its location is not equal to any special tile, i.e., it is not a special tile
    nIsRegularTile = nRandInt != nUpStart1 && nRandInt != nUpStart2;
    nIsRegularTile = nIsRegularTile && nRandInt != nUpStart3 && nRandInt != nUpEnd1;
    nIsRegularTile = nIsRegularTile && nRandInt != nUpEnd2 && nRandInt != nUpEnd3;
    nIsRegularTile = nIsRegularTile && nRandInt != nDownStart1 && nRandInt != nDownStart2;
    nIsRegularTile = nIsRegularTile && nRandInt != nDownStart3 && nRandInt != nDownEnd1;
    nIsRegularTile = nIsRegularTile && nRandInt != nDownEnd2 && nRandInt != nDownEnd3;
    nIsRegularTile = nIsRegularTile && nRandInt != nP1DownStart && nRandInt != nP1DownEnd;
    nIsRegularTile = nIsRegularTile && nRandInt != nP2DownStart && nRandInt != nP2DownEnd;
   
    // a tile is considered valid if it is both unique in its row and regular
    return nIsUniqueInRow && nIsRegularTile;
}


/*
    @brief: generates a valid up/down tile pair and stores the integer locations in an origin and a
        destination variable

    @pre: assumes nGenerateUpTilePair is 1 or 0
    @pre: assumes *nOrigin and *nDestination are pointers to a special tile pair and their values
        are set to 0
    @pre: assumes uninitialized special tiles are set to 0
    @pre: assumes both player's custom down tiles are set to valid locations

    @param: nGenerateUpTilePair - determines whether an up or down tile pair is being generated
    @param: *nOrigin - pointer to the location of the special tile pair's origin
    @param: *nDestination - pointer to the location of the special tile pair's destination
    @param: *nUpStart1 - pointer to the location of the first up tile's origin
    @param: *nUpStart2 - pointer to the location of the second up tile's origin
    @param: *nUpStart3 - pointer to the location of the third up tile's origin
    @param: *nUpEnd1 - pointer to the location of the first up tile's destination
    @param: *nUpEnd2 - pointer to the location of the second up tile's destination
    @param: *nUpEnd3 - pointer to the location of the third up tile's destination
    @param: *nDownStart1 - pointer to the location of the first down tile's origin
    @param: *nDownStart2 - pointer to the location of the second down tile's origin
    @param: *nDownStart3 - pointer to the location of the third down tile's origin
    @param: *nDownEnd1 - pointer to the location of the first down tile's destination
    @param: *nDownEnd2 - pointer to the location of the second down tile's destination
    @param: *nDownEnd3 - pointer to the location of the third down tile's destination
    @param: *nP1DownStart - pointer to the location of player 1's custom down tile origin
    @param: *nP1DownEnd - pointer to the location of player 1's custom down tile destination
    @param: *nP2DownStart - pointer to the location of player 2's custom down tile origin
    @param: *nP2DownEnd - pointer to the location of player 2's custom down tile destination

    @note: the random integer generation excludes the interval [91, 100] (i.e., the 10th row) to
        reserve it for a down tile placement
    @note: moreover, the interval [1, 6] is also deliberately excluded for better special tile
        location generation
*/
void generateTilePair(int nGenerateUpTilePair, int *nOrigin, int *nDestination, int *nUpStart1,
    int *nUpStart2, int *nUpStart3, int *nUpEnd1, int *nUpEnd2, int *nUpEnd3, int *nDownStart1,
    int *nDownStart2, int *nDownStart3, int *nDownEnd1, int *nDownEnd2, int *nDownEnd3,
    int *nP1DownStart, int *nP1DownEnd, int *nP2DownStart, int *nP2DownEnd)
{
    int nIsValidGeneration = 0;
    int nRandInt;

    while (!nIsValidGeneration) {
        nRandInt = ngetRandInt(7, 90); // generates a random location from tile 7 until the end of the 9th row
        if (nisValidTile(nGenerateUpTilePair, nRandInt, *nUpStart1, *nUpStart2, *nUpStart3,
            *nUpEnd1, *nUpEnd2, *nUpEnd3, *nDownStart1, *nDownStart2, *nDownStart3, *nDownEnd1,
            *nDownEnd2, *nDownEnd3, *nP1DownStart, *nP1DownEnd, *nP2DownStart, *nP2DownEnd))
        {
            nIsValidGeneration = 1;
        }
    }
    *nOrigin = nRandInt;
    nIsValidGeneration = 0; // resets the random generation conditional variable
   
    while (!nIsValidGeneration) {
        nRandInt = ngetRandInt(7, 90); // generates a random location from tile 7 until the end of the 9th row
        if (nisValidTile(nGenerateUpTilePair, nRandInt, *nUpStart1, *nUpStart2, *nUpStart3,
            *nUpEnd1, *nUpEnd2, *nUpEnd3, *nDownStart1, *nDownStart2, *nDownStart3, *nDownEnd1,
            *nDownEnd2, *nDownEnd3, *nP1DownStart, *nP1DownEnd, *nP2DownStart, *nP2DownEnd))
        {
            nIsValidGeneration = 1;
        }
    }
    *nDestination = nRandInt;

    // ensures that the locations of the special tiles are logically correct based on their type
    if (nGenerateUpTilePair && *nOrigin > *nDestination) {
        swapInts(nOrigin, nDestination);
    } else if (!nGenerateUpTilePair && *nOrigin < *nDestination) {
        swapInts(nOrigin, nDestination);
    }

    return;
}


/*
    @brief: generates a complete, valid set of special tile pairs, that is, 3 up and 3 down tile
        pairs and stores their integer locations into their corresponding variables

    @pre: assumes all parameters except for both player's custom down tiles are set to 0
    @pre: assumes both player's custom down tiles are set to valid locations

    @param: *nUpStart1 - pointer to the location of the first up tile's origin
    @param: *nUpStart2 - pointer to the location of the second up tile's origin
    @param: *nUpStart3 - pointer to the location of the third up tile's origin
    @param: *nUpEnd1 - pointer to the location of the first up tile's destination
    @param: *nUpEnd2 - pointer to the location of the second up tile's destination
    @param: *nUpEnd3 - pointer to the location of the third up tile's destination
    @param: *nDownStart1 - pointer to the location of the first down tile's origin
    @param: *nDownStart2 - pointer to the location of the second down tile's origin
    @param: *nDownStart3 - pointer to the location of the third down tile's origin
    @param: *nDownEnd1 - pointer to the location of the first down tile's destination
    @param: *nDownEnd2 - pointer to the location of the second down tile's destination
    @param: *nDownEnd3 - pointer to the location of the third down tile's destination
    @param: *nP1DownStart - pointer to the location of player 1's custom down tile origin
    @param: *nP1DownEnd - pointer to the location of player 1's custom down tile destination
    @param: *nP2DownStart - pointer to the location of player 2's custom down tile origin
    @param: *nP2DownEnd - pointer to the location of player 2's custom down tile destination
*/
void randomizeTilePairs(int *nUpStart1, int *nUpStart2, int *nUpStart3, int *nUpEnd1, int *nUpEnd2,
    int *nUpEnd3, int *nDownStart1, int *nDownStart2, int *nDownStart3, int *nDownEnd1,
    int *nDownEnd2, int *nDownEnd3, int *nP1DownStart, int *nP1DownEnd, int *nP2DownStart,
    int *nP2DownEnd)
{
    generateTilePair(1, nUpStart1, nUpEnd1, nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2,
        nUpEnd3, nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3,
        nP1DownStart, nP1DownEnd, nP2DownStart, nP2DownEnd); // generates the first up tile pair
    generateTilePair(0, nDownStart1, nDownEnd1, nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2,
        nUpEnd3, nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3,
        nP1DownStart, nP1DownEnd, nP2DownStart, nP2DownEnd); // generates the first down tile pair
    generateTilePair(1, nUpStart2, nUpEnd2, nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2,
        nUpEnd3, nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3,
        nP1DownStart, nP1DownEnd, nP2DownStart, nP2DownEnd); // generates the second up tile pair
    generateTilePair(0, nDownStart2, nDownEnd2, nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2,
        nUpEnd3, nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3,
        nP1DownStart, nP1DownEnd, nP2DownStart, nP2DownEnd); // generates the second down tile pair
    generateTilePair(1, nUpStart3, nUpEnd3, nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2,
        nUpEnd3, nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3,
        nP1DownStart, nP1DownEnd, nP2DownStart, nP2DownEnd); // generates the third up tile pair
    generateTilePair(0, nDownStart3, nDownEnd3, nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2,
        nUpEnd3, nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3,
        nP1DownStart, nP1DownEnd, nP2DownStart, nP2DownEnd); // generates the third down tile pair
    *nDownStart3 = ngetRandInt(91, 99); // ensures that the third down tile origin is located at the last row

    return;
}


/*
    @brief: prints the entire board's representation along with its special tile states, given
        information about the locations of both players and special tile pairs

    @pre: assumes both player locations are between 1 and 100
    @pre: assumes all special tile locations are initialized and have distinct values

    @param: nP1Loc - location of player 1
    @param: nP2Loc - location of player 2
    @param: nUpStart1 - location of the first up tile's origin
    @param: nUpStart2 - location of the second up tile's origin
    @param: nUpStart3 - location of the third up tile's origin
    @param: nUpEnd1 - location of the first up tile's destination
    @param: nUpEnd2 - location of the second up tile's destination
    @param: nUpEnd3 - location of the third up tile's destination
    @param: nDownStart1 - location of the first down tile's origin
    @param: nDownStart2 - location of the second down tile's origin
    @param: nDownStart3 - location of the third down tile's origin
    @param: nDownEnd1 - location of the first down tile's destination
    @param: nDownEnd2 - location of the second down tile's destination
    @param: nDownEnd3 - location of the third down tile's destination
    @param: nP1DownStart - location of player 1's custom down tile origin
    @param: nP1DownEnd - location of player 1's custom down tile destination
    @param: nP2DownStart - location of player 2's custom down tile origin
    @param: nP2DownEnd - location of player 2's custom down tile destination
*/
void createBoard(int nP1Loc, int nP2Loc, int nUpStart1, int nUpStart2, int nUpStart3, int nUpEnd1,
    int nUpEnd2, int nUpEnd3, int nDownStart1, int nDownStart2, int nDownStart3, int nDownEnd1,
    int nDownEnd2, int nDownEnd3, int nP1DownStart, int nP1DownEnd, int nP2DownStart, int nP2DownEnd)
{
    int nRow = 1, nColumn, nLocation;

    printUpperBorder();
   
    while (nRow <= 10) { // rows are counted from top to bottom from 1 to 10
        nColumn = 1;
        while (nColumn <= 10) { // columns are counted from left to right from 1 to 10
            // computes for the location count given a row and a column in the board
            nLocation = (10 - nRow) * 10;
            if (nRow % 2 == 1) {
                nLocation += 11 - nColumn; // odd rows progress from right to left in the board
            } else {
                nLocation += nColumn; // even rows progress from left to right in the board
            }

            printf("%c ", 179);

            if (nLocation == nP1Loc && nLocation == nP2Loc) { // players 1 and 2
                printf("@");
            } else if (nLocation == nP1Loc) { // player 1
                printf("1");
            } else if (nLocation == nP2Loc) { // player 2
                printf("2");
            } else if (nLocation == nUpStart1 || nLocation == nUpEnd1) { // up tile pair 1
                printf("A");
            } else if (nLocation == nUpStart2 || nLocation == nUpEnd2) { // up tile pair 2
                printf("B");
            } else if (nLocation == nUpStart3 || nLocation == nUpEnd3) { // up tile pair 3
                printf("C");
            } else if (nLocation == nDownStart1 || nLocation == nDownEnd1) { // down tile pair 1
                printf("a");
            } else if (nLocation == nDownStart2 || nLocation == nDownEnd2) { // down tile pair 2
                printf("b");
            } else if (nLocation == nDownStart3 || nLocation == nDownEnd3) { // down tile pair 3
                printf("c");
            } else if (nLocation == nP1DownStart || nLocation == nP1DownEnd) { // player 1's down tile pair
                printf("\'");
            } else if (nLocation == nP2DownStart || nLocation == nP2DownEnd) { // player 2's down tile pair
                printf("\"");
            } else if (nLocation == 100) { // goal tile
                printf("%c", 206);
            } else { // plain tile
                printf("%c", 219);
            }

            printf(" ");
            nColumn++;
        }
        printf("%c\n", 179);
        if (nRow < 10) {
            printMiddleBorder();
        }
        nRow++;
    }

    printLowerBorder();

    return;
}


/*
    @brief: checks if the player is currently on a special tile that affects them and transports
        them to the corresponding destination if so

    @pre: assumes nIsP1Turn is 1 or 0
    @pre: assumes player location is between 1 and 100
    @pre: assumes all special tile locations are initialized and have distinct, valid values

    @param: nIsP1Turn - determines whether it is player 1 or 2's turn
    @param: *nPlayerLoc - pointer to the location of the player
    @param: *nUpStart1 - pointer to the location of the first up tile's origin
    @param: *nUpStart2 - pointer to the location of the second up tile's origin
    @param: *nUpStart3 - pointer to the location of the third up tile's origin
    @param: *nUpEnd1 - pointer to the location of the first up tile's destination
    @param: *nUpEnd2 - pointer to the location of the second up tile's destination
    @param: *nUpEnd3 - pointer to the location of the third up tile's destination
    @param: *nDownStart1 - pointer to the location of the first down tile's origin
    @param: *nDownStart2 - pointer to the location of the second down tile's origin
    @param: *nDownStart3 - pointer to the location of the third down tile's origin
    @param: *nDownEnd1 - pointer to the location of the first down tile's destination
    @param: *nDownEnd2 - pointer to the location of the second down tile's destination
    @param: *nDownEnd3 - pointer to the location of the third down tile's destination
    @param: *nP1DownStart - pointer to the location of player 1's custom down tile origin
    @param: *nP1DownEnd - pointer to the location of player 1's custom down tile destination
    @param: *nP2DownStart - pointer to the location of player 2's custom down tile origin
    @param: *nP2DownEnd - pointer to the location of player 2's custom down tile destination
*/
void checkForSpecialTile(int nIsP1Turn, int *nPlayerLoc, int *nUpStart1, int *nUpStart2,
    int *nUpStart3, int *nUpEnd1, int *nUpEnd2, int *nUpEnd3, int *nDownStart1, int *nDownStart2,
    int *nDownStart3, int *nDownEnd1, int *nDownEnd2, int *nDownEnd3, int *nP1DownStart,
    int *nP1DownEnd, int *nP2DownStart, int *nP2DownEnd)
{
    if (*nPlayerLoc == *nUpStart1) { // either player ended up on up tile pair 1's origin
        *nPlayerLoc = *nUpEnd1;
    } else if (*nPlayerLoc == *nUpStart2) { // either player ended up on up tile pair 2's origin
        *nPlayerLoc = *nUpEnd2;
    } else if (*nPlayerLoc == *nUpStart3) { // either player ended up on up tile pair 3's origin
        *nPlayerLoc = *nUpEnd3;
    } else if (*nPlayerLoc == *nDownStart1) { // either player ended up on down tile pair 1's origin
        *nPlayerLoc = *nDownEnd1;
    } else if (*nPlayerLoc == *nDownStart2) { // either player ended up on down tile pair 2's origin
        *nPlayerLoc = *nDownEnd2;
    } else if (*nPlayerLoc == *nDownStart3) { // either player ended up on down tile pair 3's origin
        *nPlayerLoc = *nDownEnd3;
    } else if (nIsP1Turn && *nPlayerLoc == *nP2DownStart) { // player 1 ended up on player 2's down tile origin
        *nPlayerLoc = *nP2DownEnd;
    } else if (!nIsP1Turn && *nPlayerLoc == *nP1DownStart) { // player 2 ended up on player 1's down tile origin
        *nPlayerLoc = *nP1DownEnd;
    }
}


/*
    @brief: simulates a player's turn by simulating a die roll and updating the board based on their roll

    @pre: assumes nIsP1Turn is 1 or 0
    @pre: assumes player location is between 1 and 100
    @pre: assumes all special tile locations are initialized and have distinct values

    @param: nIsP1Turn - determines whether it is player 1 or 2's turn
    @param: *nPlayerLoc - pointer to the location of the player
    @param: *nPlayerStreak - pointer to the player's streak of consecutive 1s
    @param: *nUpStart1 - pointer to the location of the first up tile's origin
    @param: *nUpStart2 - pointer to the location of the second up tile's origin
    @param: *nUpStart3 - pointer to the location of the third up tile's origin
    @param: *nUpEnd1 - pointer to the location of the first up tile's destination
    @param: *nUpEnd2 - pointer to the location of the second up tile's destination
    @param: *nUpEnd3 - pointer to the location of the third up tile's destination
    @param: *nDownStart1 - pointer to the location of the first down tile's origin
    @param: *nDownStart2 - pointer to the location of the second down tile's origin
    @param: *nDownStart3 - pointer to the location of the third down tile's origin
    @param: *nDownEnd1 - pointer to the location of the first down tile's destination
    @param: *nDownEnd2 - pointer to the location of the second down tile's destination
    @param: *nDownEnd3 - pointer to the location of the third down tile's destination
    @param: *nP1DownStart - pointer to the location of player 1's custom down tile origin
    @param: *nP1DownEnd - pointer to the location of player 1's custom down tile destination
    @param: *nP2DownStart - pointer to the location of player 2's custom down tile origin
    @param: *nP2DownEnd - pointer to the location of player 2's custom down tile destination
*/
void simulateTurn(int nIsP1Turn, int *nPlayerLoc, int *nPlayerStreak, int *nUpStart1,
    int *nUpStart2, int *nUpStart3, int *nUpEnd1, int *nUpEnd2, int *nUpEnd3, int *nDownStart1,
    int *nDownStart2, int *nDownStart3, int *nDownEnd1, int *nDownEnd2, int *nDownEnd3,
    int *nP1DownStart, int *nP1DownEnd, int *nP2DownStart, int *nP2DownEnd)
{
    int nPlayer = 2 - nIsP1Turn; // 2 if it is not player 1's turn; otherwise, 1
    int nRandom;

    if (*nPlayerStreak >= 2) { // special rule gets triggered when the streak is at least 2
        printf("\n(%d) Special rule! :3", *nPlayerStreak - 1);
    }
    printf("\nPlayer %d is rolling the dice...\n\n", nPlayer);
    printDieRoll();
    Sleep(1000);

    nRandom = ngetRandInt(0, 6); // mimics a six-sided die plus a 0 value
    if (nRandom == 1) {
        (*nPlayerStreak)++;
    } else {
        *nPlayerStreak = 0;
    }

    printf("Player %d rolled a %d!\n", nPlayer, nRandom);
    Sleep(1000);

    printf("Updating the board...\n");
    *nPlayerLoc += nRandom;
    checkForSpecialTile(nIsP1Turn, nPlayerLoc, nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2,
        nUpEnd3, nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3,
        nP1DownStart, nP1DownEnd, nP2DownStart, nP2DownEnd);
    Sleep(1000);

    return;
}


/*
    @brief: prints the game termination sequence
*/
void terminateGame() {
    Sleep(1000);
    printf("\nBefore you leave, here is a token from the creator of the program:\n");
    Sleep(2000);

    printDie();
    Sleep(1000);

    printf("(it is the pair of virtual dice you and your partner used to play :3)\n");
    Sleep(2000);
   
    printf("\n\nThank you for playing Ups and Downs! - CJ Bunyi\n\n");

    return;
}


/*
    @brief: This is the main function of the program. It initializes the program's main variables,
        executes the different program logic (e.g., game initialization, tile randomization, board
        creation, turn simulation), prints the corresponding outputs, then terminates the program
        upon completion/termination.

    @return: 0 for successful execution; otherwise, a non-zero value corresponding to the error.
*/
int main() {
    int nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2, nUpEnd3;
    int nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3;
    int nP1DownStart, nP1DownEnd, nP2DownStart, nP2DownEnd;

    int nIsP1Turn;
    int nP1Loc, nP2Loc;
    int nP1Streak, nP2Streak;
    int nIsPlayerPlaying = 1;

    srand(time(NULL)); // initializes rand() using system time

    while (nIsPlayerPlaying) {
        nUpStart1 = nUpStart2 = nUpStart3 = nUpEnd1 = nUpEnd2 = nUpEnd3 = 0;
        nDownStart1 = nDownStart2 = nDownStart3 = nDownEnd1 = nDownEnd2 = nDownEnd3 = 0;
        nP1DownStart = nP1DownEnd = nP2DownStart = nP2DownEnd = 0;

        nIsP1Turn = 1;
        nP1Loc = 1, nP2Loc = 1;
        nP1Streak = 0, nP2Streak = 0;

        initializeGame(&nP1DownStart, &nP1DownEnd, &nP2DownStart, &nP2DownEnd);        

        randomizeTilePairs(&nUpStart1, &nUpStart2, &nUpStart3, &nUpEnd1, &nUpEnd2, &nUpEnd3,
            &nDownStart1, &nDownStart2, &nDownStart3, &nDownEnd1, &nDownEnd2, &nDownEnd3,
            &nP1DownStart, &nP1DownEnd, &nP2DownStart, &nP2DownEnd);

        while (!nisWinnerFound(nP1Loc, nP2Loc)) { // loops the game proper until a winner is found
            system("cls");
            printTitle();
            printf("\nPlayer 1's location: %d\nPlayer 2's location: %d\n\n", nP1Loc, nP2Loc);

            createBoard(nP1Loc, nP2Loc, nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2, nUpEnd3,
                nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3,
                nP1DownStart, nP1DownEnd, nP2DownStart, nP2DownEnd);

            if (nIsP1Turn) { // simulates a turn for player 1
                simulateTurn(nIsP1Turn, &nP1Loc, &nP1Streak, &nUpStart1, &nUpStart2, &nUpStart3,
                &nUpEnd1, &nUpEnd2, &nUpEnd3, &nDownStart1, &nDownStart2, &nDownStart3, &nDownEnd1,
                &nDownEnd2, &nDownEnd3, &nP1DownStart, &nP1DownEnd, &nP2DownStart, &nP2DownEnd);
            } else { // simulates a turn for player 2
                simulateTurn(nIsP1Turn, &nP2Loc, &nP2Streak, &nUpStart1, &nUpStart2, &nUpStart3,
                &nUpEnd1, &nUpEnd2, &nUpEnd3, &nDownStart1, &nDownStart2, &nDownStart3, &nDownEnd1,
                &nDownEnd2, &nDownEnd3, &nP1DownStart, &nP1DownEnd, &nP2DownStart, &nP2DownEnd);
            }

            if ((nIsP1Turn && nP1Streak >= 2) || (!nIsP1Turn && nP2Streak >= 2)) {
                nIsP1Turn = !nIsP1Turn; // ensures that the special rule is being followed
            }
            nIsP1Turn = !nIsP1Turn; // switches to the other player's turn
        }
       
        // ensures that the winner is seen in the final board representation
        if (nP1Loc >= 100) {
            nP1Loc = 100;
        } else {
            nP2Loc = 100;
        }

        system("cls");
        printTitle();
        printf("\nPlayer 1's location: %d\nPlayer 2's location: %d\n\n", nP1Loc, nP2Loc);
        createBoard(nP1Loc, nP2Loc, nUpStart1, nUpStart2, nUpStart3, nUpEnd1, nUpEnd2, nUpEnd3,
            nDownStart1, nDownStart2, nDownStart3, nDownEnd1, nDownEnd2, nDownEnd3, nP1DownStart,
            nP1DownEnd, nP2DownStart, nP2DownEnd);
        Sleep(1000);

        printf("\nPlayer %d wins the game!\n", 1 + (nP2Loc == 100)); // 1 if player 1 reaches 100; otherwise, 2
        Sleep(2000);

        printf("\nInput any character to play again or '0' to terminate the program. ");
        scanf("%d", &nIsPlayerPlaying);
        system("cls");
    }

    terminateGame();

    return 0;
}