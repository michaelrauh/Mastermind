#include "stdio.h"
#include "stdlib.h"

int main()
{
  
  /*preliminary masks to figure out what digits we have to work with*/
  int points,newPoints;
  int i,j;
  int digits[10];
  int mask;
  int pos;

  int guess(int * pos,int answer[],int digit, int mask,int score);
  printf("Come up with a six digit number. I will guess numbers. Tell me how many digits are correct.\n");
  
 start:
  i=0;
  points = 0;
  while(i<10 && points < 6)
    {
      printf("%i%i%i%i%i%i \n",i,i,i,i,i,i);
      scanf("%d",&digits[i]);
      points += digits[i];
      i++;
    }
  
  if (points != 6)
    {
      printf("Inconceivable! Try again.\n");
      goto start;
    }
  
  /* Now that we have the digits, we can find a mask. This defaults to 9*/
  if (i < 9)
    {
      mask = 9;
    }
  else /*otherwise we have to search*/
    {
      i=0;
      while (digits[i] != 0)
	{
	  i++;
	}
      mask = i;
    }
  
  /*Now a mask is applied to find the position of the first digit*/
  points = 0;
  newPoints = 0;
  int answer [6] = {mask,mask,mask,mask,mask,mask}; /*guess starts as mask*/
  for (i=0;i<10;i++) /*for each digit*/
    {
      for (j=0;j<digits[i];j++) /*for each instance of the digit*/
	{
	  while (newPoints == points) /*keep searching until things improve*/
	    {
	      newPoints = guess(&pos,answer,i,mask,points);
	    }

	  /*get ready to find next spot*/
	  points = newPoints; 
	  pos = 0;
	  if(points == 6)
	    {
	      printf("Good game! \n");
	      return 0;
	    }
	  else if (points > 6)
	    {
	      printf("Looks like you made a mistake. Let's start over.\n");
	      goto start;
	    }
	}
    }
  return 0;
}

/*This will make a guess in the current position (skipping taken places)
and return the score from the user. It takes in a position, the digits, 
the current guess where it stands, and the current number we're on.

The trick is that we are replacing the last mask with the digit. If score 
does not improve we need to put it back*/
int guess(int * pos,int answer[],int digit, int mask,int score)
{
  /* Make a guess here */
  int temp;
  int iter = *pos;
  int try[6];

  for (temp = 0;temp<6;temp++) /*make copy to work with*/
    {
      try[temp] = answer[temp];
    }

  while (try[iter] != mask) /*find the next mask position, starting at pos*/
    {
      iter++;
    }
  try[iter] = digit; /*This makes the guess*/

  /*print the guess*/
  for (temp = 0; temp<6;temp++)
    {
      printf("%d",try[temp]);
    }
  printf("\n");

  /*get response*/
  int response;
  scanf ("%d",&response);

  /* if the response is good, then replace the guess with this guess
otherwise, leave the mask*/
  if (response > score)
    {
      answer[iter] = digit;
    }

  /*increment position for next time*/
  *pos = *pos + 1;
  return response; 
}
