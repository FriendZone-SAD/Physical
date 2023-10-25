#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <locale.h>

#define TIME_LIMIT 180 

char *questions[] = {
    "Q1: it has two wings and two legs",
    "Q2: How many months are there in 1 year? (Answer in numbers)",
    "Q3: Kept for its eggs and meat",
    "Q4: How many days are there in a week?",
    "Q5: Which animal is known as the king of the jungle?",
    "Q6: Name the National fruit of India?",
    "Q7: Which is the smallest month of the year?",
    "Q8: Which colour symbolises peace?",
    "Q9: How many sides are there in a triangle?",
    "Q10: Name the largest planet of our Solar System?",
    "Q11: Name the smallest continent?",
    "Q12: Which is the principal source of energy for the Earth?",
    "Q13: Name the planet nearest to the Earth?",
    "Q14: Name a bird that lays the largest eggs and run very fast?",
    "Q15: Name the National animal of Thailand",
    "Q16: Which is the tallest mountain in the world?",
    "Q17: Which planet is known for its beautiful rings?",
    "Q18: Name the hardest substance available on Earth?",
    "Q19: Name the National animal of India?",
    "Q20: Which animal is known as the ""'Ship of the Desert'"""
};

char *answers[] = {
    "Bird",
    "12",
    "Chicken",
    "7",
    "Lion",
    "Mango",
    "February",
    "White",
    "Three",
    "Jupiter",
    "Australia",
    "Sun",
    "Mercury",
    "Ostrich",
    "Elephant",
    "Everest",
    "Saturn",
    "Diamond",
    "Tiger",
    "Camel"
};

char* getHint(char* answer, char* hint, bool* revealed);

int main() {
    setlocale(LC_ALL, "th_TH.UTF-8");
    srand(time(NULL));
    int allQuestions = sizeof(questions) / sizeof(questions[0]);

    printf("Welcome to Guess the word !!\n\n");
    
    int wrong = 0;
    int hintCount = 0;
    time_t start_time, end_time;
    start_time = time(NULL); 
    int score = 0;
    

    while (wrong < 5) {
        
        int index = rand() % allQuestions;
        char hint[100] = {0};
        bool revealed[100] = {false};
        strncpy(hint, answers[index], sizeof(hint) - 1);
        for (int i = 0; hint[i]; i++) {
            if (hint[i] != ' ') hint[i] = '_';
        }

        char guess[100];
        bool correct = false;
        int tmpscore = 100;

        while (!correct && wrong < 5) {
            end_time = time(NULL);
            int time_elapsed = (int)difftime(end_time, start_time);
            int time_remaining = TIME_LIMIT - time_elapsed;

            int minutes = time_remaining / 60;
            int seconds = time_remaining % 60;
            
            printf("Your score : %dpt.\n\n",score);
            printf("Time remaining: %02d:%02d\n\n", minutes, seconds);
            printf("!!!QUESTIONS!!!\n\n");
            printf("%s\n\n", questions[index]);
            
            

            printf("Guess the word (Type \"Hint\" for hint): ");
            
            fgets(guess, sizeof(guess), stdin);
            

            end_time = time(NULL); 
           if (time_remaining <= 0) {
                printf("Sorry, time's up!\n");
                printf("\nThank you for playing the game.\n");
                return 0;
            }

            size_t len = strlen(guess);
            if (len > 0 && guess[len-1] == '\n') guess[len-1] = '\0';

            if (strcmp(guess, "Hint") == 0 && hintCount < 5) {
                char* currentHint = getHint(answers[index], hint, revealed);
                hintCount++;
                tmpscore -= 15;
                if(hintCount != 5){
                    printf("\nYou can use 5 Hints, Now you use %d out of 5 and your score will be decrease by 10pt.\n",hintCount);
                }
                else{
                    printf("\n       ANSWER NOW !!!       \n");
                }
                printf("_________________________________\n");
                printf("\nHint: %s\n", currentHint);
                printf("_________________________________\n\n");
                
                continue;
            }

            if (strcmp(guess, answers[index]) == 0) {
                printf("\n*********************************\n\n");
                printf("Congrats! Thats correct.\n\n");
                printf("Your score +%d.\n\n",tmpscore);
                score += tmpscore;
                printf("*********************************\n\n");
                correct = true;
                hintCount = 0; 
                
            } else {
                wrong++;
                printf("\nWrong! You have %d more chance to guess.\n", 5 - wrong);
                printf("____________________________________________________\n\n");
            }
        }

        if (wrong == 5) {
            printf("\n!!! You guessed wrong more than 5 times! The game is over. !!!d\n\n");
            for (int i = 0; i < allQuestions; i++) {
                printf("%s || Answer is: %s\n", questions[i], answers[i]);
            }
            break;
        }
    }

    printf("\nThank you for playing the game.\n");
    return 0;
}

char* getHint(char* answer, char* hint, bool* revealed) {
    int len = strlen(answer);
    int r;
    do {
        r = rand() % len;
    } while(revealed[r] || answer[r] == ' '); 
    hint[r] = answer[r];
    revealed[r] = true;

    return hint;
}  