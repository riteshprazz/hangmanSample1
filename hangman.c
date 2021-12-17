#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAXNUMWORDS 2048
#define MAXWORDLENGTH 64

int main(){

    srand(time(NULL));

    char guessWords[MAXNUMWORDS][MAXWORDLENGTH];
    int wordsReadIn = 0;

    FILE *fp = fopen("guess.txt","r");
    if(fp==NULL){
        printf("Failed to open File\n");
        exit(0);
    }
    char input[64];

    while(fgets(input, 63, fp)){
        sscanf(input, "%s" , guessWords[wordsReadIn]);
        printf("Scanned: input: %s guessWords[%d]: %s \n",input, wordsReadIn, guessWords[wordsReadIn]);
        wordsReadIn++;
    }
    printf("Total Words Read In:%d\n", wordsReadIn);
    fclose(fp);

    // char guessWords[][16] = {
    //     "green",
    //     "yellow",
    //     "purple",
    //     "windows",
    //     "linux",
    //     "apple"
    // };

    //index for random word
    int randomIndex = rand() % wordsReadIn;
    int numLives = 5;
    int numCorrect = 0;
    int oldCorrect = 0;

    int lengthOfWord = strlen(guessWords[randomIndex]);
    int letterGuessed[8] = {0,0,0,0,0,0,0,0};

    int quit = 0;

    int loopIndex = 0;
    
    char guess[16];
    char letterGuess;

    //printf("guessWords: %s randomIndex: %d lengthOfWord: %d\n",guessWords[randomIndex],randomIndex,lengthOfWord);
    //game loop
    while (numCorrect < lengthOfWord)
    {
        printf("\n\nNew Turn ......\nHangman Word: ");
        for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
            //prevent repeating correct guess
            if(letterGuessed[loopIndex] == 1){
                printf("%c",guessWords[randomIndex][loopIndex]);
            }
            else{
                printf("-");
            }
        }
        printf("\n");

        printf("Number Correct So Far: %d\n",numCorrect);
        printf("Enter a guess letter:");
        fgets(guess, 16, stdin);

        if(strncmp(guess, "quit", 4)==0){
            quit = 1;
            break;
        }
        letterGuess = guess[0];
        printf("letterGuessed: %c \n",letterGuess);

        oldCorrect = numCorrect;

        for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
            //prevent repeating correct guess
            if(letterGuessed[loopIndex] == 1){
                continue;
            }

            if (letterGuess == guessWords[randomIndex][loopIndex]){
                letterGuessed[loopIndex] = 1;
                numCorrect++;
            }
        }

        if(oldCorrect == numCorrect) {
            numLives--;
            printf("Sorry!! Wrong Guess\n");
            if(numLives == 0){
                break;
            }
        }
        else{
            printf("Correct Guess :-) \n");
        }
    }

    if(quit == 1){
        printf("The user quit early\n");
    }
    else if(numLives == 0){
        printf("\n Sorry You Lose :-( \n The Word was: \" %s \" ", guessWords[randomIndex]);
    }
    else{
        printf("You Win :-)\n");
    }
    

    // int fullrand = 0;
    // for (loopIndex =0 ;loopIndex < 10; loopIndex++){
    //     fullrand = rand();
    //     randomIndex = fullrand % 6;
    //     printf("%d -> %d\n", fullrand, randomIndex);
    // }
    return 0;
}