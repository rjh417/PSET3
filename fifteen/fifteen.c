/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(1500000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // TODO
    // declare and initialize a variable to hold the number of each tile
    int tile_numbers = d * d - 1;
    
    // populate the board tiles with values in reverse sequential order
    for (int i = 0; i < d; i++)  
    {   
        for (int j = 0; j < d; j++)
        {
            board[i][j] = tile_numbers;
            tile_numbers--;
        }
    }
    
    // if numbered tiles on the board are odd, swap the number 1 and 2 tiles.       
    if (d % 2 == 0)
    {
        int temp = board[d - 1][d - 2];
        board[d - 1][d - 2] = board[d - 1][d - 3];
        board[d - 1][d - 3] = temp; 
    }
     
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // TODO
    // loop through board array
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // print a blank tile for the zero value in the board array
            if (board[i][j] == 0)
            {
                printf("    ");
            }
            // print the values of the board array
            else
            {
                printf("%4i", board[i][j]);
            }
            
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // TODO
    // loop through board array    
    for (int i = 0; i < d; i++)
    {   
        for (int j = 0; j < d; j++)
        { 
            // find value provided by user
            while (board[i][j] == tile)
            {   
                // test array bounds, check for blank space to left, if found
                // swap
                if (i - 1 >= 0 && board[i - 1][j] == 0)
                {
                    int temp = board[i][j];
                    board[i][j] = board[i - 1][j];
                    board[i - 1][j] = temp;
                    return true; 
                } 
                // test array bounds, check for blank space to right, if found
                // swap                  
                else if (i + 1 < d && board[i + 1][j] == 0)
                {
                     int temp = board[i][j];
                     board[i][j] = board[i + 1][j];
                     board[i + 1][j] = temp;
                     return true;
                }
                // test for array bounds, check for blank space above, if found
                // swap
                else if (j - 1 >= 0 && board[i][j - 1] == 0)
                {
                     int temp = board[i][j];
                     board[i][j] = board[i][j - 1];
                     board[i][j - 1] = temp;
                     return true;
                }
                // test for array bounds, check for blanks space below, if found
                // swap
                else if (j + 1 < d && board[i][j + 1] == 0)
                {
                    int temp = board[i][j];
                    board[i][j] = board[i][j + 1];
                    board[i][j + 1] = temp;
                    return true;
                }
                else
                {
                    return false;
                }
                          
             }
         }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // TODO
    // loop through board      
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        { 
            // test for combination of largest numbered tile and zero tile in 
            // in the last two array positions and return true if found.
            while (board[d-1][d-2] == d * d - 1 && board[d-1][d-1] == 0)
            {
                return true;
            }
                        
         }
     } 
   // if combination of largest numbered tile and zero tile are not in the 
   // last two array positions, return false.     
   return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
