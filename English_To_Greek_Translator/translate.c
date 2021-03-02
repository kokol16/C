/* @author Georgios Kokolakis  ( csd4254@csd.uoc.gr)  */

/* Implemented with array of pointers to methods */

#include<stdio.h>
#include<stdlib.h>

#define Strange_tone 39
#define Tone  39
#define Strange_double_tone 34 




int ** init_letters_array();
void print_letters( int letter );

enum Translate_FSM  {init=0 ,M=1,N=2,m=3,n=4 }State ;

enum Translate_FSM simple_case(int letter);
enum Translate_FSM N_state(int letter);
 

enum Translate_FSM n_state(int letter);

enum Translate_FSM m_state(int letter);
enum Translate_FSM M_state(int letter);





int main(int argc, char * argv[])
{
	enum Translate_FSM (*Actions[5])(int);
	int iter = getchar();
	State=init;
	/*each array's index points to a method */
	Actions[0]=simple_case;
	Actions[1]=M_state;	
	Actions[2]=N_state;	
	Actions[3]=m_state;	
	Actions[4]=n_state;	


	
	while (iter != EOF)
	{
		State=Actions[State](iter);

		iter = getchar();

	

	}

	/* Those if checks if the user has inserted only the N or n or m or M alone and not other letter OR if the input has last character  N or M or n or m
		Note: This wouldn't be neccessary if we knew for sure that the input would have a space or \n at the end of the file */
	if (State==N)
	{
		putchar('N');
	}
	else if (State==n)
	{
		putchar('n');
	}
	else if (State==M)
	{
		putchar('M');
	}
	else if (State==n)
	{
		putchar('n');
	}
	


	return 0;
}

/* This method print the simple/not interesting ,letters from greek ->english*/
void print_letters(int letter)
{
	int j;	
	
	int **array = init_letters_array();
		for(j=0; j<3; j++)
		{
	
			if(array[letter][j]!=-1)
			{

				putchar(array[letter][j]);
		
			}
				
		}

		if(array[letter][0]==-1)
		{
			putchar(letter);
		}
	
}

/* This method is called when we are at the start state ,
	it determine the next state based on the letter that we got from input */
enum Translate_FSM simple_case(int letter)
{	


	if (letter==204  ) /*Μ*/
	{
		return M;

	}
	else if (letter==205)/*N*/
	{
		return N;

	}
	else if (letter==236 )/*μ*/
	{
	
		return m;
	}
	else if(letter==237)/*ν*/
	{
	
		return n;
	
	}
		print_letters(letter);
		return init;
		




	
}

/* This method is called when we have read character -> N and we need to decide what we will print based on the next character that we have read
   This method returns the state that we get into 
 */
   
enum Translate_FSM N_state(int letter)
{
	if (letter==204  ) /*Μ*/
	{
		putchar('N');
		return M;

	}
	else if (letter==205)/*N*/
	{
		putchar('N');
		return N;

	}
	else if (letter==236 )/*μ*/	
	{
	
		putchar('N');
		return m;
	}
	else if(letter==237)/*ν*/
	{
	
		putchar('N');
		return n;
	
	}else if(letter==212 || letter==244) /*Τ,τ*/
	{
		putchar('D');
		return init;
	}
	 
	

		putchar('N');
		print_letters(letter);
		return init;
	






	}
/* This method is called when we have read character -> n and we need to decide what we will print based on the next character that we have read
   This method returns the state that we get into 
 */
enum Translate_FSM n_state(int letter)
{
	if (letter==204  ) /*Μ*/
	{
		putchar('n');
		return M;

	}
	else if (letter==205)/*N*/
	{
		putchar('n');
		return N;

	}
	else if (letter==236 )/*μ*/
	{
	
		putchar('n');
		return m;
	}
	else if(letter==237)/*ν*/
	{
		putchar('n');
	
		return n;
	
	}else if(letter==212 || letter==244) /*Τ,τ*/
	{
		putchar('d');
		return init;
	}
	

		putchar('n');
		print_letters(letter);
		return init;



}
/* This method is called when we have read character -> m and we need to decide what we will print based on the next character that we have read
   This method returns the state that we get into 
 */
enum Translate_FSM m_state(int letter)
{
	if (letter==204  ) /*Μ*/
	{
		putchar('m');
		return M;

	}
	else if (letter==205)/*N*/
	{
		putchar('m');
		return N;

	}
	else if (letter==236 )/*μ*/
	{
	
		putchar('m');
		return m;
	}
	else if(letter==237)/*ν*/
	{
		putchar('m');
	
		return n;
	
	}else if(letter==208 || letter==240) /*π ,Π*/
	{
		putchar('b');
		return init;
	}

		putchar('m');
		print_letters(letter);
		return init;


}


/* This method is called when we have read character -> M and we need to decide what we will print based on the next character that we have read
   This method returns the state that we get into 
 */
enum Translate_FSM M_state(int letter)
{
	if (letter==204  ) /*Μ*/
	{
		putchar('M');
		return M;

	}
	else if (letter==205)/*N*/
	{
		putchar('M');
		return N;

	}
	else if (letter==236 )/*μ*/
	{
	
		putchar('M');
		return m;
	}
	else if(letter==237)/*ν*/
	{
		putchar('M');
	
		return n;
	
	}else if(letter==208 || letter==240) /*π ,Π*/
	{
		putchar('B');
		return init;
	}

		putchar('M');
		print_letters(letter);
		return init;


}
/* This method initialize the array that make the matches greek to -> english character
   Defulat initialization for every index is the value -1 */

int** init_letters_array()
{
	int i;
	int** match_arr;
	/* 2D array memory allocation */
	match_arr =(int**)  malloc(255 * sizeof(int*));
	for ( i = 0; i < 255; i++)
	{
		match_arr[i] = (int *) malloc( 3* sizeof(int));
	
	
	}

	/*array default initialization*/
	for (i=0; i<255; i++)
	{

		match_arr[i][0]=-1;
		match_arr[i][1]=-1;
		match_arr[i][2]=-1;


	}


	/*upercase*/

	match_arr[193][0] = 'A';
	match_arr[194][0] = 'V';
	match_arr[195][0] = 'G';
	match_arr[196][0] = 'D';
	match_arr[197][0] = 'E';
	match_arr[198][0] = 'Z';
	match_arr[199][0] = 'H';
	match_arr[200][0] = '8';
	match_arr[201][0]= 'I';
	match_arr[202][0] = 'K';
	match_arr[203][0] = 'L';
	match_arr[204][0] = 'M';
	match_arr[205][0] = 'N';
	match_arr[206][0] = 'K';
	
	match_arr[206][1] = 'S';
	
	
	
	
	match_arr[207][0] = 'O';
	match_arr[208][0] = 'P';
	match_arr[209][0] = 'R';
	match_arr[211][0] = 'S';
	match_arr[212][0] = 'T';
	match_arr[213][0] = 'Y';
	match_arr[214][0] = 'F';
	match_arr[215][0] = 'X';
	match_arr[216][0] = 'p';

	match_arr[216][1] = 'S';

	match_arr[217][0] = 'W';

	
	/*lowercase*/
	match_arr[225][0] = 'a';
	match_arr[226][0] = 'v';
	match_arr[227][0] = 'g';
	match_arr[228][0] = 'd';
	match_arr[229][0] = 'e';
	match_arr[230][0] = 'z';
	match_arr[231][0] = 'h';
	match_arr[232][0] = '8';
	match_arr[233][0] = 'i';
	match_arr[234][0] = 'k';
	match_arr[235][0] = 'l';
	match_arr[236][0] = 'm';
	match_arr[237][0] = 'n';
	match_arr[238][0] = 'k';

	match_arr[238][1] = 's';

	match_arr[239][0] = 'o';
	match_arr[240][0] = 'p';
	match_arr[241][0] = 'r';
	match_arr[243][0] = 's';
	match_arr[244][0] = 't';
	match_arr[245][0] = 'y';
	match_arr[246][0] = 'f';
	match_arr[247][0] = 'x';
	
	match_arr[248][0] = 'p';
	
	match_arr[248][1] = 's';
	
	match_arr[249][0] = 'w';
	
	/* symbols*/

	match_arr[10][0] = '\n';
	match_arr[32][0]=' ';
	match_arr[58][0]=58;
	match_arr[43][0]=43;
	match_arr[46][0]=46;
	/* Numbers */

	for (i=0; i<10; i++)
	{
		match_arr[i+48][0]=i+48;
	}
	/*tonoi*/

	match_arr[182][0] = Strange_tone;
	match_arr[182][1] = 'A';

	match_arr[184][0] = Strange_tone;
	match_arr[184][1] = 'E';


	match_arr[185][0] = Strange_tone;
	match_arr[185][1] = 'H';

	match_arr[186][0] = Strange_tone;
	match_arr[186][1] = 'I';
	
	match_arr[188][0] = Strange_tone;
	match_arr[188][1] = 'O';

	match_arr[191][0] = Strange_tone;
	match_arr[191][1] = 'W';
	
	
	match_arr[190][0] = Strange_tone;
	match_arr[190][1] = 'Y';
	
	match_arr[220][0] = 'a';
	match_arr[220][1] = '\'';
	
	match_arr[221][0] = 'e';
	match_arr[221][1] = '\'';
	
	match_arr[222][0] = 'h';
	match_arr[222][1] = '\'';
	
	match_arr[223][0] = 'i';
	match_arr[223][1] = '\'';
	
	match_arr[252][0] = 'o';
	match_arr[252][1] = '\'';
	
	match_arr[254][0] = 'w';
	match_arr[254][1] = '\'';
	
	match_arr[253][0] = 'y';
	match_arr[253][1] = '\'';

	match_arr[242][0]=115;	
	/* dialitika */

	
	match_arr[250][0] = 'i';
	match_arr[250][1] = Strange_double_tone;
	
	match_arr[251][0] = 'y';
	match_arr[251][1] = Strange_double_tone;

	match_arr[218][0] = 'I';
	match_arr[218][1] = Strange_double_tone;
	
	match_arr[219][0] = 'Y';
	match_arr[219][1] = Strange_double_tone;

	/*tonous kai dialitika*/

	match_arr[192][0] = 'i';
	match_arr[192][1] =Tone;
	match_arr[192][2]= Strange_double_tone;

	match_arr[224][0] = 'y';
	match_arr[224][1] = Tone;
	match_arr[224][2]= Strange_double_tone;






	return match_arr;
}
