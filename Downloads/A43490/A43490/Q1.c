#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "math.h"

#include <sys/timeb.h>

//2.2 A program to implement the Horspool’s algorithm. (20%)
//Essentially turns file into an array
#define LENGTH 2045

typedef struct BSTProb
{
    char letter;
    float prob;
} BSTProb;

typedef struct BSTFreq
{
    char *word;
    float frequency;
} BSTFreq;

typedef struct BSTRoot
{
    char *word;
    float root;
} BSTRoot;

//Remove spaces from a line that would otherwise ruin the word count
char *normalizedLine(char *selectedLine)
{
    char *line = malloc(256);
    strtok(selectedLine, "\n");                 // remove any newlines
    char *tempWord = strtok(selectedLine, " "); //gets the first word
    while (tempWord != NULL)
    {
        strcat(line, tempWord);
        strcat(line, " \0");
        tempWord = strtok(NULL, " "); //Resets
    }
    return line;
}

void dataToArray(FILE *fp, char arr[LENGTH][LENGTH])
{
    char buff[256];

    if (fp != NULL)
    {
        int length = 0;
        int currLine = 0;
        int i = 0;
        int j = 0;
        int index = 0;
        char *word = NULL;
        char *temp[1000];
        while (fgets(buff, 256, fp) != NULL)
        {

            temp[i] = malloc(strlen(buff) + 5);

            strcpy(temp[i], buff);
            i++;
            length++;
        }

        while (currLine != length)
        {
            word = malloc(2156);
            if (temp[currLine] == NULL)
            {
                currLine++;
                free(word);
                continue;
            }
            strcpy(word, temp[currLine]);

            char *line = normalizedLine(word);

            for (i = 0; i < (strlen(line)); i++)
            {

                if (line[i] == ' ' || line[i] == '\n')
                {

                    arr[index][j] = '\0';
                    j = 0;
                    index++;
                }
                else
                {

                    // printf("%c", word[i]);
                    arr[index][j] = line[i];
                    j++;
                }
            }

            //reset

            free(word);
            currLine++;
        }
    }
    else
    {
        printf("unable to open file");
    }
}
void addProbability(char *word, BSTProb *prob)
{
    long n = strlen(word);
    float P[n];

    //randomly assigns the first number
    float lastNum = 0;
    srand((unsigned)time(NULL));
    for (int i = 0; i < strlen(word); i++)
    {
        //move time
        float prob = ((float)rand() / RAND_MAX) * 10;
        lastNum = prob;
        //   P[0] = prob;
        //  sprintf(P[i][i], "%d", i);
        if (i == 2)
        {
            //P[0][0] = prob;
        }
    }
    float total = 0;
    int l = 0;
    int factor = 0;
    //10 - 19 character words
    if (strlen(word) >= 10 && strlen(word) < 20)
    {
        factor = 1;
    }
    //20 to 29 character words
    if (strlen(word) >= 20 && strlen(word) < 30)
    {
        factor = 2;
    }
    while (true)
    {

        float prob = (float)rand() / RAND_MAX;
        //change decimal places
        float value = 0;
        value = floorf(prob * 10) / 10;

        if (value < 0.1)
        {
            value = 0.1;
        }
        P[l] = (value) / (factor + 1);

        total += value;
        l++;
        if (l == strlen(word))
        {
            if (strlen(word) >= 10)
            {
                total = total - factor;
            }
            //Word add up to a probability of 1
            if ((total == 1.0) && ((l) == (strlen(word))))
            {
                printf("\ngood\n");
                break;
            }
            else
            {
                total = 0;
                l = 0;
            }
        }
    }
    //Leaving 0 to be blank, since keys start from 1
    total = 0;

    for (int i = 0; i < n; i++)
    {
        total += (P[i]);
        prob[i].letter = word[i];
        prob[i].prob = P[i];
        printf("num: %d, Letter: %c, prob: %f\n", i, prob[i].letter, prob[i].prob);

        //  printf("%c, %f\n",prob[i].letter, prob[i].prob);
    }
}

float weight(int key1, int key2, BSTFreq *freq)
{
    float total = 0;
    //if the index we put is 0, then we mean 1 since keys start from 1
    int i = 0;
    for (i = key1 + 1; i <= key2; i++)
    {

        total += freq[i].frequency;
    }
    // printf("are you changing? %f\n", prob[3].prob);
    printf("\n");
    // printf("Total%f\n", total);
    return total;
}
void BinaryTree()
{
}

void OptimalBST(BSTFreq *array, int length)
{
    int n = length;
    //e.g we allocate space for two more chars, just in case
    float C[n][n];
    BSTRoot R[n][n];
    int prevK = 0;

    for (int i = 0; i < n; i++)
    {
        C[i][i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        for (int d = 0; d <= n; d++)
        {
            int j = i + d;
            //We are setting where the min cost is 1 to make code maneageable
            if ((j - i) == 1)
            {
                //  C[i][j] = array[j].frequency;

                R[i][j].root = array[j].frequency;
            }
        }
    }

    for (int a = 1; a <= n; a++)
    {

        for (int b = a + 1; b <= n; b++)
        {
            int i = b - 1 - a;
            int j = b;
            int total = j - i;
            float minVal = 999;
            for (int k = total; k >= 1; k--)
            {
                prevK = k;
                C[i][j] = C[i][j - k] + C[(j - k) + 1][j] + weight(i, j, array);

                printf("\nC[%d][%d] = C[%d][%d] + C[%d][%d] + w(%d, %d)", i, j,
                       i, j - k,

                       (j - k) + 1, j, i, j);

                printf("first: %f || second: %f ||weighr %f \n ", C[i][j - k], +C[j - k + 1][j], weight(i, j, array));
                printf("Result: %f", C[i][j]);

                if ((prevK != k + 1) && (C[i][j] < minVal))
                {
                    minVal = C[i][j];

                    R[i][j].word = malloc(strlen(array[(j - k) + 1].word) + 1);
                    R[i][j].word = array[(j - k) + 1].word;
                    R[i][j].root = (j - k) + 1;
                }
            }
            if (minVal != 999)
            {
                C[i][j] = minVal;
            }
        }
    }

    //Final result;
    for (int a = 1; a <= n; a++)
    {

        for (int b = a + 1; b <= n; b++)
        {
            int i = b - 1 - a;
            int j = b;
            int total = j - i;
            float minVal = 999;
            for (int k = total; k >= 1; k--)
            {

                //  C[i][j] = C[i][j-k] + C[ (j-k)+1][j] + weight(i, j, key);

                // printf("\nWord:[%d][%d] = %s, root %f", i, j, R[i][j].word, R[i][j].root);
                // printf("\nWord:[%d][%d] = %s, frequency %f", i, j, R[i][j].word, C[i][j]);
            }
        }
    }

    //initialize
    //initialize
}
int main(int argc, const char *argv[])
{

    //Neccessary structs to find time
    struct timeb firstStart, firstEnd;
    int elapsedTime = 0;
    ftime(&firstStart);

    char array[LENGTH][LENGTH];
    char *array2[LENGTH];
    int freqArr[LENGTH];
    BSTFreq mainArray[LENGTH];

    FILE *fp = fopen("data_7.txt", "r");
    dataToArray(fp, array);
    //initialize

    for (int i = 0; i < 2045; i++)
    {
        array2[i] = malloc(25);
        strcpy(array2[i], " ");
    }
    int i2 = 0;
    mainArray[i2].word = malloc(20);
    mainArray[i2].frequency = 0;
    //let's see if it's seen before
    for (int i = 0; i < 2045; i++)
    {
        //     printf("%s\n", array[i]);
        //e.g coding
        char *word = array[i];
        float freq = 0;
        int exists = -1;

        for (int j = 0; j < 2045; j++)
        {
            //found

            if (strcmp(word, array[j]) == 0)
            {
                freq++;
                //Validate if it exists in the array
                for (int k = 0; k < 2045; k++)
                {
                    if (strcmp(array[j], array2[k]) == 0)
                    {
                        //exists
                        exists = 0;
                    }
                }
                if (exists == -1)
                {
                    i2++;
                    array2[i2] = malloc(strlen(word) + 1);
                    strcpy(array2[i2], word);

                    mainArray[i2].word = word;
                }
            }
        }
        if (freq > 0)
        {
            mainArray[i2].frequency = freq;
        }
    }

    //TEST
    for (int i = 0; i < i2; i++)
    {
        mainArray[i].frequency = mainArray[i].frequency / 2045;
        //  printf("%s %f\t \n", mainArray[i].word, mainArray[i].frequency);
    }

    //index starts at 0
    OptimalBST(mainArray, 600 - 1);

    /*
    BSTFreq second[5];
    //dummy
    second[0].frequency = 0;
    second[0].word = malloc(20);

    second[1].frequency = 4;
    second[1].word = malloc(20);
    strcpy(second[1].word, "A");

    second[2].frequency = 2;
    second[2].word = malloc(20);

    strcpy(second[2].word, "B");

    second[3].frequency = 6;
    second[3].word = malloc(20);

    strcpy(second[3].word, "c");

    second[4].frequency = 3;
    second[4].word = malloc(20);

    strcpy(second[4].word, "D");
*/
    // OptimalBST(second, 4);

    //my keys start at 1, not 0

    //Calculating the total time & if the time is less than 0ms, set to 0
    ftime(&firstEnd);
    elapsedTime = firstEnd.millitm - firstStart.millitm;
    if (elapsedTime <= 0)
    {
        elapsedTime = 0;
    }
    // printf("\nelasedTime for Horspool's technique %dms\n", elapsedTime);
    return 0;
}
