#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

/* Read 1 character without echo */
char getch(void) 
{
  return getch_(0);
}

int rps(char you,char comp)//returns 0 if its draw returns 1 if you win and returns -1 if you lose
{   int result =1;
    if (you == comp)
    return 0;

    else if (you == 'r' && comp == 'p'){
        return -1;
    }
    else if (you == 'p' && comp == 's'){
        return -1;
    }   
    else if (you == 's' && comp == 'r'){
        return -1;
    }
    return 1;
}
void abb(char a){       //prints rock for r scissor for s and paper for p
    if(a == 'r')
    printf("Rock");
    else if(a == 'p')
    printf("Paper");
    else
    printf("Scissor");
}

char comp_chc(){  //returns a random choice for computer!
    int num;
    srand(time(0));
    num = rand()%3 +1; //generates random no between 1 or 2 or 3

    if (num == 1)
        return 'r';

    else if (num == 2)
        return 'p';

    else
        return 's';
}

void main()
{
    char you='\0',comp,rep,num;
    int result;
    printf("\nWELCOME TO ROCK / PAPER / SCISSOR");

    do
    {
        comp = comp_chc();
        printf("\n\nChoose your option: Rock (r)  Paper (p)  Scissor (s)\n");
        you = getch();
        while (you != 'r' && you != 'p' && you != 's')
        {   
            printf("\nyour choice is invalid\n(rock - r  scissor - s  paper - p) \n");
            you = getch(); 
        }
        result = rps(you , comp);

        printf("\nYou chose ");
        abb(you);
        printf(" & Computer chose ");
        abb(comp);
        
        if (result == 0)
            printf("\n\nGame Draw!!");
        else if(result == 1)
            printf("\n\nYou win!!");
        else
            printf("\n\nYou lose!!");

        printf("\n\nPlay Again? (y/n) ");
        rep = getch();      
    } while(rep == 'y');    //repeats entire program if the user chose to play
}