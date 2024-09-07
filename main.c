#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Taps for LFST are: 32, 27, 18, 13, 9
extern unsigned randomizeA(unsigned *inSeed, int inIterations, int inLimit);
extern int compareA(const int inRandom, const int inGuess, int *inNum);

void getInpt(char *input)
{
    while (1)
    {
        if (!scanf("%c", input))
        {
            fflush(stdin);
            printf("Please provide a valid input[Y/N]: ");
        }
        else if (*input != 'Y' && *input != 'y' && *input != 'N' && *input != 'n')
        {
            fflush(stdin);
            printf("Please provide a valid input[Y/N]: ");
        }
        else
        {
            fflush(stdin);
            break;
        }
    }
}

int main()
{
    time_t T;
    srand((unsigned)time(&T)); // all rand() function calls will generate different number each time

    // Declaration
    unsigned seed = rand();
    int iterations = rand() % 100; // number of iteration in the function randomizeA is also random
    int ranNum, guess, limit, corr, numGuess;
    char inpt;
    FILE *rcrd = NULL;
    char fRcrd[10];

    printf("\tWelcome to Guessing Game!\n");

    rcrd = fopen("Record.txt", "rb");
    fscanf(rcrd, "%s", fRcrd);
    fclose(rcrd);

    printf("\nDo you want to clear your record ?[Y/N]: ", fRcrd);
    getInpt(&inpt);
    printf("%c", inpt);
    if (inpt == 'Y' || inpt == 'y')
    {
        rcrd = fopen("Record.txt", "w");
        fprintf(rcrd, "%s", "1000"); // Write insenly high number instead of deleting it completly.
        fclose(rcrd);
    }
    else
        printf("\nYour Record as it stands now is: %s", fRcrd);

    do
    { // MAIN LOOP TO RUN THE PROGRAM AGAIN
        printf("\nPlease insert the upper bound (limit) for the number: ");
        while (1)
        {
            if (!scanf("%d", &limit))
            {
                fflush(stdin);
                printf("Please insert a valid number: ");
            }
            else if (limit <= 1)
            {
                fflush(stdin);
                printf("Please insert a positive integer larger than 1: ");
            }
            else
            {
                fflush(stdin);
                break;
            }
        }

        ranNum = randomizeA(&seed, iterations, limit);
        printf("Random number between 1-%d is generated.\n", limit);

        numGuess = 0;
        while (1)
        {
            printf("\nplease take a guess on what the number is: ");
            while (1)
            {
                if (!scanf("%d", &guess))
                {
                    fflush(stdin);
                    printf("Please insert a valid number: ");
                }
                else if (guess <= 0 || guess >= limit)
                {
                    fflush(stdin);
                    printf("your guess should be in range 1-%d: ", limit);
                }
                else
                {
                    fflush(stdin);
                    break;
                }
            }

            corr = compareA(ranNum, guess, &numGuess);

            if (corr == 2)
                printf("Your guess is higher than the number.\n");
            if (corr == 1)
                printf("Your guess is lower than the number.\n");
            if (corr == 0)
            {
                printf("Your Guess is SPOT ON!\n");
                break;
            }
        }

        printf("\n\tAnswer is: %d\n\n", ranNum);
        printf("Number of guesses you took was: %d\n", numGuess);
        printf("Do you want to continue playing?[Y/N]: ");
        getInpt(&inpt);

        rcrd = fopen("Record.txt", "rb");
        fscanf(rcrd, "%s", fRcrd);
        fclose(rcrd);

        if (atoi(fRcrd) > numGuess)
        {
            sprintf(fRcrd, "%d", numGuess);
            rcrd = fopen("Record.txt", "w");
            fputs(fRcrd, rcrd);
            fclose(rcrd);
        }

    } while (inpt != 'N' && inpt != 'n');

    printf("\nBye!\n");

    return 0;
}
