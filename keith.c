#include <sys\timeb.h>
#include<stdio.h>
#include<stdlib.h>
#include <mpir.h>
#include<math.h>
#include<string.h>
#include<memory.h>
#include<assert.h>
#include<stdint.h>

#define DIGITS 7
#define SUM 7
#define START 8
#define END 9




int main(int argc, char *argv[])
{	
	mpz_t queue[DIGITS + 3]; //+3 because we are being insane
	char startString[DIGITS+1]; //leave room for a string terminator
	char endString[DIGITS+1];		


	//all of our GMP numbers will be in here, all in memory together
	for (unsigned char i = 0; i < DIGITS + 3; i++)
	{
		mpz_init(queue[i]);		
	}
		
	//For the number of digits we are searching
	//Set up start and end numbers. ex: 100 through 999
	for (unsigned char i = 0; i < DIGITS; i++)
	{
		printf("Setting string at:%d\n", i);
		startString[i] = '0';
		endString[i] = '9';
	}
	startString[0] = '1';
	startString[DIGITS] = '\0';
	endString[DIGITS] = '\0';

	printf("startstring:%s\n", startString);
	printf("endString:%s\n", endString);

	//use the strings to set the start and end GMP numbers
	mpz_set_str(queue[START], startString, 10);
	mpz_set_str(queue[END], endString, 10);

	//to evaluate how fast we went	
	struct timeb starttime, endtime;
	int diff;
	ftime(&starttime);
			
	//keep an array around of the digits of the current number we are checking
	//this makes it faster to set up new GMP numbers, rather than using a string
	unsigned char digits[DIGITS];
	char *s = mpz_get_str(NULL, 10, queue[START]);
	for (unsigned char i = 0; i < DIGITS; i++)
	{
		digits[i] = s[i] - '0';
	}

	//an index into out position in the 'queue'
	int idx = 0;
	while (mpz_cmp(queue[START], queue[END]) <= 0)
	{
		//set each GMP number in the queue to a digit in the current number being checked
		idx = 0;
		for (int i = 0; i < DIGITS; i++)
		{						
			mpz_set_ui(queue[i], digits[i]);			
		}
			
		//check if the current number is a keith number
		int r = -1;		
		while (r<0) {			
			mpz_set(queue[SUM], queue[0]);
			for (unsigned char i = 1; i < DIGITS; i++)
			{				
				//90% of execution time is in this add method
				mpz_add(queue[SUM], queue[SUM], queue[i]);
			}
			r = mpz_cmp(queue[SUM], queue[START]);
			//swap is faster than set
			mpz_swap(queue[idx],queue[SUM]);
			//advance 1 in the queue
			idx = (idx+1) % DIGITS;			
		}
		
		//if r is 0 we found a keith number!
		if (r==0)
		{
			gmp_printf("%Zd\n", queue[START]);
		}
		
		//check the next number
		mpz_add_ui(queue[START], queue[START], 1);
		//update our digit array by one. 
		for (int i = DIGITS - 1; i >= 0; i--)
		{
			if (digits[i] == 9)
			{
				digits[i] = 0;
			}
			else
			{
				digits[i]++;
				break;
			}
		}
	}

	ftime(&endtime);
	diff = (int)(1000.0 * (endtime.time - starttime.time)
		+ (endtime.millitm - starttime.millitm));

	printf("Time Taken: %d\n", diff);
	return 0;

}





