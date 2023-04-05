/* ------------------------------------------------------------
    CREDENTIALS:

    Submitted By: Tyler Procko

    Assignment: CS223 Final Project

    Filename: PROCKOT_FINALPROJECT_CS223

    Credit to:

       - Professor Behi for everything.
       - Mohammad Alali for helping me with
         a lot of important parts, especially
         the bubblesort algorithm.

    Submitted On: 12/05/2016

    By submitting this program with my name,
    I affirm that the creation and modification
    of this program is primarily my own work.
 ------------------------------------------------------------ */

/* -------------------------------------------------------------
    PROGRAM DESCRIPTION:

    This program creates, in the console window, a
    text-based game where four or two cars (marked by asterisks)
    'race' across the screen. The user will be given the
    choice to run the race automatically (4-cars) or to race
    against another person (2-cars), using keyboard input.
    In addition, file read will be implemented for the car
    usage, as well as file write for saving the results of
    races.
 ------------------------------------------------------------ */

/* -------------------------------------------------------------
    NOTES:

    All non-constant names in this program follow a form of
    Hungarian notation, i.e.:

    int iNumber;

    char cCharacter;

    void fnvFunctionName;
    (where fnv stands for 'function-void')

    int arriArrayName[#];
    (where arri stands for 'array-integer'

    etc.
 ------------------------------------------------------------ */


/* - - INCLUDES - - */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// Next two are included for the Sleep function
#include <unistd.h>
#include <windows.h>


/* - - CONSTANTS - - */
// Constants of RNG for spaces moved
#define TRACK_LENGTH 90
#define MAX_MOVE_SPACES 10
#define MIN_MOVE_SPACES 1
// Filename constants
#define FILENAME_1 "car.txt"
#define FILENAME_2 "raceresult.txt"
// Number of cars for the array (auto and manual)
#define CARSPECS_ARRAY_SIZE_AUTO 4
#define CARSPECS_ARRAY_SIZE_MANUAL 2
// Constants for lower and upper index numbers of car array
#define INDEX_LOWER 0
#define INDEX_HIGHER 3


/* - - STRUCTURE - - */
struct CarSpecs
{
    char cDriverName[20];
    char cCarType[20];
    int iCarNumber;
    char cCarColor[20];
    int iPosition;

};


/* - - FUNCTIONS - - */
// RNG prototypes
int fniRandGenMove(int iLowerBound1, int iUpperBound1);
int fniRandGenCar(int iLowerBound1, int iUpperBound1);
// Auto race prototype
void fnvMoveSpacesAuto(struct CarSpecs stCarArray[], int iArraySize, int iTrackLength, int iLowerBound1, int iUpperBound1, int iLowerBound2, int iUpperBound2);
// Manual race prototype
void fnvMoveSpacesManual(struct CarSpecs stCarArray[], int iArraySize, int iChoiceIndex1, int iChoiceIndex2, int iTrackLength, int iLowerBound1, int iUpperBound1);
// Bubblesort prototype
void fnvBubbleSort(struct CarSpecs stCarArray[], int iArraySize);
// Swap prototype (used with bubblesort)
void fnvSwap(struct CarSpecs stCarArray[], int iIndex1, int iIndex2);
// Read file prototype
void fnvReadFile(struct CarSpecs stCarArray[], int iArraySize);
// Write to file (auto race) prototype
void fnvAppendAutoFile(struct CarSpecs stCarArray[], char arrcFileName[], int iArraySize);
// Write to file (manual race) prototype
void fnvAppendManualFile(struct CarSpecs stFirstCar, struct CarSpecs stSecondCar, char arrcFilename[]);
// Title screen prototype
void fnvTitleScreen();


// Main function does very little besides ask user for which type of race they want to play
// and whether they want to keep playing, all in one large do-while loop.
// In addition, nothing else is done in the main function besides declaring variables,
// calling for functions and passing values.
int main()
{
    printf("----Tyler Procko----\n\n\n");

    // Declare
    int iAutoManual;
    int iUserYesNo;
    int iChoice1, iChoice2;
    int iChoiceIndex1, iChoiceIndex2;
    int i;

    // Initialize random seed
    srand(time(NULL));

    // Title screen print
    fnvTitleScreen();

    // Declare structure variable to fit all cars' specs
    // This is used in almost every function- very important
    struct CarSpecs stCarArray[CARSPECS_ARRAY_SIZE_AUTO];

    // Call to function to read file
    fnvReadFile(stCarArray, CARSPECS_ARRAY_SIZE_AUTO);
    system("CLS");

    // Loop to ask user for auto/manual race
    // Also to ask user if they want to continue playing
    do
    {
        // Ask for auto/manual with simple check
        printf("Type 1 for auto (4-car) race or 2 for manual (2-car) race.\n");
        do
        {
        printf("1) Auto\n2) Manual\n>> ");
        scanf("%d", &iAutoManual);

        } while((iAutoManual != 1) && (iAutoManual != 2));

        // Clear for movement screens
        system("CLS");

        // If auto, call to auto race function
        if (iAutoManual == 1)
        {
            fnvMoveSpacesAuto(stCarArray, CARSPECS_ARRAY_SIZE_AUTO, TRACK_LENGTH, MIN_MOVE_SPACES, MAX_MOVE_SPACES, INDEX_LOWER, INDEX_HIGHER);

        }

        // Else, ask two users which cars they want and check
        else
        {
            // Print visual indicators
            printf("    RACER         CAR         NUMBER     COLOR\n");
            printf("   --------------------------------------------\n");
            // Call to function to print whole file
            fnvReadFile(stCarArray, CARSPECS_ARRAY_SIZE_AUTO);

            // Player 1 choice
            do
            {
            printf("\nType the number of the racer you choose, player 1.\n");
            scanf("%d", &iChoice1);

            } while((iChoice1 < 1) || (iChoice1 > 4));

            // Assign value based on array index
            iChoiceIndex1 = iChoice1 - 1;

            // Give warning
            printf("\nPlayer 2! Don't pick the same racer as player 1. It won't happen.");

            // Player 2 choice
            do
            {
            printf("\n\nType the number of the racer you choose, player 2.\n");
            scanf("%d", &iChoice2);

            } while((iChoice2 < 1) || (iChoice2 > 4) || (iChoice2 == iChoice1));

            // Assign value based on array index
            iChoiceIndex2 = iChoice2 - 1;

            // Call to manual race function
            fnvMoveSpacesManual(stCarArray, CARSPECS_ARRAY_SIZE_MANUAL, iChoiceIndex1, iChoiceIndex2, TRACK_LENGTH, MIN_MOVE_SPACES, MAX_MOVE_SPACES);

        }

        // Ask user to play again with simple check
        printf("\n\nWould you like to play again? Type 1 for yes or 2 for no.\n");
        do
        {
        printf("1) Yes\n2) No\n>> ");
        scanf("%d", &iUserYesNo);

        } while((iUserYesNo != 1) && (iUserYesNo != 2));

        // Clear screen and return to ask for auto/manual race
        system("CLS");

    // Keep looping as long as user continues to want to play
    } while(iUserYesNo == 1);

    // If user types 2, end program with confirmatory message and delay
    printf("\nThanks for playing!\n\n");
    Sleep(2250);

    return 0;

}


/* --------------------------------- */
/*                                   */
/*             FUNCTIONS             */
/*                                   */
/* --------------------------------- */


// Function to create random number for car movement
int fniRandGenMove(int iLowerBound1, int iUpperBound1)
{
    // Declare
    int randInt;

    // Formula for RNG (1-10) based on global-defined numbers
    randInt = (rand() % (iUpperBound1 - iLowerBound1 + 1)) + iLowerBound1;

    return (randInt);

}


// Function to create random number for car selection during auto race
int fniRandGenCar(int iLowerBound1, int iUpperBound1)
{
    //Declare
    int randInt;

    // Formula for RNG (0-3, the indexes of four cars)
    randInt = (rand() % (iUpperBound1 - iLowerBound1 + 1)) + iLowerBound1;

    return (randInt);

}


// Function to print asterisks in auto (4-car) mode and display the final results
void fnvMoveSpacesAuto(struct CarSpecs stCarArray[], int iArraySize, int iTrackLength, int iLowerBound1, int iUpperBound1, int iLowerBound2, int iUpperBound2)
{
    // Declare
    int i, j;
    int iRandomCarIndex;

    // Assign initial position of all cars to 0 spaces
    for(i = 0; i < iArraySize; i++)
    {
        stCarArray[i].iPosition = 0;

    }

    // Declare new variable of structure for 1st place car and set to zero on purpose (start of race)
    struct CarSpecs stFirstCar;
    stFirstCar.iPosition = 0;

    // Loop to print asterisks, representing car movement
    do
    {
        // Represent the track length
        printf("       |------------------------------------------------------------------------------------------|\n");

        // Grabs a random index in the car array (0 - 4) and moves that car only
        iRandomCarIndex = fniRandGenCar(iLowerBound2, iUpperBound2);
        stCarArray[iRandomCarIndex].iPosition += fniRandGenMove(iLowerBound1, iUpperBound1);

        // Loop to print the car number and RNG amount of asterisks for the randomly selected car
        for(i = 0; i < iArraySize; i++)
        {
            // Print the car number for each line
            printf("Car #%d\t", stCarArray[i].iCarNumber);

            // Print the number of asterisks for the random car, according to the 'running sum' of asterisks
            for(j = 0; j < stCarArray[i].iPosition; j++)
            {
                printf("*");

            }

            // Assign first place car
            if (stCarArray[i].iPosition > stFirstCar.iPosition)
            {
                stFirstCar.iPosition = stCarArray[i].iPosition;
                stFirstCar.iCarNumber = stCarArray[i].iCarNumber;

            }

            // Newline for each car
            printf("\n");

        }

        // Represent the track length
        printf("       |------------------------------------------------------------------------------------------|\n");

        // Auto mode- sleep function to pause for a bit, and cls to clear screen for next move
        Sleep(300);
        system("CLS");

    // All while under the length of the track (90)
    } while(stFirstCar.iPosition < iTrackLength);

    // Reprint the final race for visual
    // Represent the track length
    printf("       |------------------------------------------------------------------------------------------|\n");
    // Loop to print the car number and RNG amount of asterisks for each car
    for(i = 0; i < iArraySize; i++)
    {
        // Print the car number for each line
        printf("Car #%d\t", stCarArray[i].iCarNumber);

        // Print the number of asterisks for each car,
        // according to the 'running sum' of asterisks
        for(j = 0; j < stCarArray[i].iPosition; j++)
        {
            printf("*");

        }

        // Newline for each car
        printf("\n");

    }
    // Represent the track length
    printf("       |------------------------------------------------------------------------------------------|\n");

    // Call to function to sort the car's positions- to find their places
    fnvBubbleSort(stCarArray, iArraySize);

    // Print the car's places on screen
    printf("\nThe car in first place is #%d.\n", stCarArray[0].iCarNumber);
    printf("The car in second place is #%d.\n", stCarArray[1].iCarNumber);
    printf("The car in third place is #%d.\n", stCarArray[2].iCarNumber);
    printf("The car in fourth place is #%d.\n", stCarArray[3].iCarNumber);

    // Function call to print race results to file
    fnvAppendAutoFile(stCarArray, FILENAME_2, iArraySize);

}


// Function to record auto race results to file
void fnvAppendAutoFile(struct CarSpecs stCarArray[], char arrcFileName[], int iArraySize)
{
    // Declare file pointer
    FILE *Fappend;
    // Declare
    int i;

    // Open file for appending
    Fappend = fopen(arrcFileName, "a");

    // If returned NULL, file isn't there
    if (Fappend == NULL)
    {
        printf("%s does not exist.", arrcFileName);

    }

    // Otherwise, append race results to file
    else
    {
        // Print results to file
        fprintf(Fappend, "------- AUTO RACE -------\n");
        for(i = 0; i < iArraySize; i++)
        {
            fprintf(Fappend, "Place %d - %s in car #%d\n", (i + 1), stCarArray[i].cDriverName, stCarArray[i].iCarNumber);

        }
        fprintf(Fappend, "\n");

    }

    // Close file
    fclose(Fappend);

}


// Function to print asterisks in manual (2-car) mode and display the final results
void fnvMoveSpacesManual(struct CarSpecs stCarArray[], int iArraySize, int iPlayer1Choice, int iPlayer2Choice, int iTrackLength, int iLowerBound1, int iUpperBound1)
{
    // Declare
    int i, j;

    // Assign car-place variables to player chosen cars
    struct CarSpecs stFirstCar = stCarArray[iPlayer1Choice];
    stFirstCar.iPosition = 0;

    struct CarSpecs stSecondCar = stCarArray[iPlayer2Choice];
    stSecondCar.iPosition = 0;

    // Clear screen for more visibility of manual race
    system("CLS");

    // Simple reminder to players and their choices
    printf("Player 1 chose %s in car #%d.\n", stFirstCar.cDriverName, stFirstCar.iCarNumber);
    printf("Player 2 chose %s in car #%d.\n", stSecondCar.cDriverName, stSecondCar.iCarNumber);

    // Pause before we show the race
    system("PAUSE");
    system("CLS");

    // Display starting positions of both cars and the track
    // This block of code comes before the main do-while loop and acts as a
    // 'baseline' for the starting race visual

    // Represent the track length
    printf("       |------------------------------------------------------------------------------------------|\n");

    // Print the car number for 1st car
    printf("Car #%d\t", stFirstCar.iCarNumber);

    // Print the car number for 2nd car
    printf("\nCar #%d\t", stSecondCar.iCarNumber);

    // Represent the track length
    printf("\n       |------------------------------------------------------------------------------------------|\n");

    // Get player one's INITIAL input (no starting asterisks)
    getchar();

    // Loop to print asterisks, representing car movement
    // Somewhat redundant logic in the loop here, but it is simply to make the visual aspect of the race more appealing
    do
    {
        // PLAYER ONE'S TURN
        // Wait for user input then clear screen
         printf("Player 1 press enter.");
        getchar();
        system("CLS");

        // Represent the track length
        printf("       |------------------------------------------------------------------------------------------|\n");

        // RNG function call for movement increment
        if(stFirstCar.iPosition < iTrackLength)
        {
            stFirstCar.iPosition += fniRandGenMove(iLowerBound1, iUpperBound1);

        }

        // Print the car number for 1st car
        printf("Car #%d\t", stFirstCar.iCarNumber);
        // Print the number of asterisks for 1st car
        for(i = 0; i < stFirstCar.iPosition; i++)
        {
            printf("*");

        }

        // Print the car number for 2nd car
        printf("\nCar #%d\t", stSecondCar.iCarNumber);
        // Print the number of asterisks for 2nd car
        for(j = 0; j < stSecondCar.iPosition; j++)
        {
            printf("*");

        }

        // Represent the track length
        printf("\n       |------------------------------------------------------------------------------------------|\n");

        // PLAYER TWO'S TURN
        // Wait for user input then clear screen
        printf("Player 2 press enter.");
        getchar();
        system("CLS");

        // Represent the track length
        printf("       |------------------------------------------------------------------------------------------|\n");

        // RNG function call for movement increment
        if(stSecondCar.iPosition < iTrackLength)
        {
            stSecondCar.iPosition += fniRandGenMove(iLowerBound1, iUpperBound1);

        }

        // Print the car number for 1st car
        printf("Car #%d\t", stFirstCar.iCarNumber);
        // Print the number of asterisks for 1st car
        for(i = 0; i < stFirstCar.iPosition; i++)
        {
            printf("*");

        }

        // Print the car number for 2nd car
        printf("\nCar #%d\t", stSecondCar.iCarNumber);
        // Print the number of asterisks for 2nd car
        for(j = 0; j < stSecondCar.iPosition; j++)
        {
            printf("*");

        }

        // Represent the track length
        printf("\n       |------------------------------------------------------------------------------------------|\n");

    // All while under the length of the track (90)
    } while((stFirstCar.iPosition < iTrackLength) && (stSecondCar.iPosition < iTrackLength));

    // If/else block to find 1st/2nd place
    if (stFirstCar.iPosition > stSecondCar.iPosition)
    {
        // Print 1st and 2nd place
        printf("\nThe winning car is %s in car #%d.\n", stFirstCar.cDriverName, stFirstCar.iCarNumber);
        printf("Second place goes to %s in car #%d.\n", stSecondCar.cDriverName, stSecondCar.iCarNumber);

        // Assign first and second place
        stFirstCar = stCarArray[iPlayer1Choice];
        stSecondCar = stCarArray[iPlayer2Choice];

    }

    else
    {
        // Print 1st and 2nd place
        printf("\nThe winning car is %s in car #%d.\n", stSecondCar.cDriverName, stSecondCar.iCarNumber);
        printf("Second place goes to %s in car #%d.\n", stFirstCar.cDriverName, stFirstCar.iCarNumber);

        // Assign first and second place
        stFirstCar = stCarArray[iPlayer2Choice];
        stSecondCar = stCarArray[iPlayer1Choice];

    }

    // Function call to print race results to file
    fnvAppendManualFile(stFirstCar, stSecondCar, FILENAME_2);

}


// Function to record manual race results to file
void fnvAppendManualFile(struct CarSpecs stFirstCar, struct CarSpecs stSecondCar, char arrcFileName[])
{
    // Declare file pointer
    FILE *Fappend;
    // Declare
    int i;

    // Open file for appending
    Fappend = fopen(arrcFileName, "a");

    // If returned NULL, file isn't there
    if (Fappend == NULL)
    {
        printf("%s does not exist.", arrcFileName);

    }

    // Otherwise, append race results to file
    else
    {
        // Print results to file
        fprintf(Fappend, "------ MANUAL RACE ------\n");
        fprintf(Fappend, "Place 1 - %s in car #%d\n", stFirstCar.cDriverName, stFirstCar.iCarNumber);
        fprintf(Fappend, "Place 2 - %s in car #%d\n", stSecondCar.cDriverName, stSecondCar.iCarNumber);
        fprintf(Fappend, "\n");

    }

    // Close file
    fclose(Fappend);


}


// Read file function
void fnvReadFile(struct CarSpecs stCarArray[], int iArraySize)
{
    // Create reading file pointer
    FILE *Fread;
    // Declare
    int i;

    // Open file for reading
    Fread = fopen(FILENAME_1, "r");

    // If returned NULL, file isn't there
    if (Fread == NULL)
    {
        printf("%s does not exist.", FILENAME_1);

    }

    // Otherwise, begin reading and save all specs to the structured array
    else
    {
        for(i = 0; i < iArraySize; i++)
        {
            fscanf(Fread, "%s %s %d %s", stCarArray[i].cDriverName, stCarArray[i].cCarType, &stCarArray[i].iCarNumber, stCarArray[i].cCarColor);
            printf("%d)  %-10s %-16s %-7d %-12s\n", (i+1), stCarArray[i].cDriverName, stCarArray[i].cCarType, stCarArray[i].iCarNumber, stCarArray[i].cCarColor);

        }

    }

    // Close file
    fclose(Fread);

}


// Sorting algorithm to be used in fnvMoveSpacesAuto (commonly referred to as bubblesort)
// This takes whatever amount of numeric data is put in and literally sorts them from top to bottom
// Used to find 1st, 2nd, 3rd and 4th places in order, in the context of this program
void fnvBubbleSort(struct CarSpecs stCarArray[], int iArraySize)
{
    // Declare and initialize
    int iSwapCount = 0;
    int i;

    do
    {
        // Reassign iSwapCount to 0 every time the loop runs around
        // This is to ensure that the number of swaps for each iteration starts at 0
        iSwapCount = 0;

        // Check index 0 against index 1, check index 1 against index 2...
        // Until the second to last index, which does not need to be checked (in this case, until index 2)
        for(i = 0; i < (iArraySize - 1); i++)
        {
            // The [i+1] in the last half of the if statement's argument is to ensure that
            // the previous [i] index is compared to the next one [i+1] and also to
            // catch the last index without actually using it to check against something
            // If element [i] is less than element [i+1], swap places... repeat until not true
            if (stCarArray[i].iPosition < stCarArray[i+1].iPosition)
            {
                // Function call to swap indexes
                fnvSwap(stCarArray, i, i+1);
                // Add to counter variable to ensure the do-while loop continues
                iSwapCount += 1;

            }

        }

    } while(iSwapCount != 0);

}


// Swap function to be used in fnvBubbleSort
void fnvSwap(struct CarSpecs stCarArray[], int iIndex1, int iIndex2)
{
    // Assign the first number to be checked against to a temporary variable
    struct CarSpecs temp = stCarArray[iIndex1];
    // Assign the second number to be checked to the first number
    stCarArray[iIndex1] = stCarArray[iIndex2];
    // Assign the temporary variable to the second number being checked
    stCarArray[iIndex2] = temp;

}


// Function to print title screen
void fnvTitleScreen()
{
    printf("======   ======   \\\\   //   ======         =====        ===       ====   ======   =====                     \n");
    printf("  ||     |         \\\\ //      ||           ||  \\\\      // \\\\     //      |        ||  \\\\                     \n");
    printf("  ||     |=====     ) (       ||           ||__//     //___\\\\    ||      |=====   ||__//                   \n");
    printf("  ||     |         // \\\\      ||           || \\\\     //     \\\\   \\\\      |        || \\\\                              \n");
    printf("  ||     |=====   //   \\\\     ||           ||  \\\\   //       \\\\   ====   |=====   ||  \\\\                            \n\n");


    printf("________________________________________________________________________________________________________________________\n");

    printf("  ,,  .,      |-____-.                          , ,      |-____-.\n");
    printf("     , ..  ,..| [ 1 ]|                      ,  .    . . ,| [ 5 ]|\n");
    printf("        ., .  |_----_.                  . ,        .     |_----_.\n");

    printf("\n\n=======================================================================================================================\n\n");

    printf("                        ,  ,      |-____-.                                  ,  ,            |-____-.\n");
    printf("                          , .  ,. | [ 7 ]|                                          , .  ,. | [ 9 ]|\n");
    printf("                      .,       .,.|_----_.                                               . .|_----_.\n");

    printf("\n\n________________________________________________________________________________________________________________________\n\n");

    system("PAUSE");
    system("CLS");

}

