#define _CRT_SECURE_NO_WARNINGS
#include "sudoku.h"
#include <string.h>
#define rows 9
#define columns 9
#define Max_Value 9
#define Min_Value 0

/* 
    This method removes the choice n
    from the row of the cell (r,c)
*/
static void sudoku_eliminate_row(Grid_T *g, int r,int c, int n)
{
    int col=0;
    for (col=0; col<columns; col++)
    {
        if( (col!=c) )
        {
			if (grid_read_value(*g, r, c) == 0)

            grid_remove_choice(g,r,c,n);

        }
    }
}
/* 
    This method removes the choice n
    from the column of the cell (r,c)
*/

static void sudoku_eliminate_column(Grid_T *g, int r,int c, int n)
{
    int row=0;
    for (row=0; row<rows; row++)
    {
        if( (row!=r) )
        {
			if(grid_read_value(*g,r,c)==0)
			grid_remove_choice(g,r,c,n);

        }
    }
}
/* 
    This method removes the choice n
    from the box of the cell (r,c)
*/

static void sudoku_eliminate_box(Grid_T *g, int r,int c, int n)
{
	int row_start,col_start,row_end,col_end;
    int col,row;
    row_start= r/3*3;
    row_end=row_start+3;
    col_start=c/3*3;
    col_end=col_start+3;
    for(row=row_start; row<row_end; row++)	
    {
        for(col=col_start; col<col_end; col++)
        {
            if( row!=r || col!=c	)
            {
				if (grid_read_value(*g, r, c) == 0)

                grid_remove_choice(g,row,col,n);

            }
        }
    }
 
}

/* 
    This method removes the choice n
    from the row ,column,box of the cell (r,c)
*/

static void sudoku_eliminate_choice(Grid_T *g, int r, int c, int n)
{
    sudoku_eliminate_box(g,r,c,n);
    sudoku_eliminate_row(g,r,c,n);
    sudoku_eliminate_column(g,r,c,n);
}



/*
    This method remove the choice from the cell(i,j)
    and update it's value to n
    @returns the number of choices that left for(i,j)
*/
static int sudoku_update_choice(Grid_T *g, int i, int j, int n)
{
	if (g->elts[i][j].choices.num[n])
	{
        /*clear the choice from the cell*/
		g->elts[i][j].choices.num[n] = 0;
		g->elts[i][j].choices.count--;
        /*update it's value to n*/
		grid_update_value(g,i,j,n);
	}

    return grid_read_count(*g,i,j);
}
/* 
    This method search for a cell with unique choice
    or for a cell that has multiple choices
    @returns the choice that we picked
    or 0 if a cell has no choice
*/
static int sudoku_try_next(Grid_T g, int *row, int *col)
{
    int r,c,row_started,col_started,val;
	for(r=0;r<rows; r++)
    {
        for(c=0;c<columns; c++)
        {
            if(grid_read_value(g,r,c)==0)
            {
                row_started=r;
                col_started=c;
                r=rows;
                break;
            }
        }
    }
    for(r=row_started; r<rows; r++)
    {
        for(c=col_started; c<columns; c++)
        {
            if (   ( grid_read_value(g,r,c)==0 ) )
            {
				*row = r;
				*col = c;
				if (grid_read_count(g, r, c) == 0)
				{
					return 0;
				}
				else if (grid_read_count(g, r, c) == 1)
				{
					for (val = 1; val < Max_Value + 1; val++)
					{
						if (grid_choice_is_valid(g, r, c, val))
						{
							return val;
						}
					}
				}
				

                
            }       
        }
    }
    for(r=0; r<rows; r++)
    {
        for(c=0; c<columns; c++)
        {
            if( ( r==row_started && c==col_started ) ){
				r = rows;
				break;

			}
			if ((grid_read_value(g, r, c) == 0))
			{
				*row = r;
				*col = c;
				if (grid_read_count(g, r, c) == 0)
				{
					return 0;
				}
				else if (grid_read_count(g, r, c) == 1)
				{
					for (val = 1; val < Max_Value + 1; val++)
					{
						if (grid_choice_is_valid(g, r, c, val))
						{
							return val;
						}
					}
				}



			}
        }
    }

    
    for(r=0; r<rows; r++)
    {
        for(c=0; c<columns; c++)
        {
            
            if (  grid_read_value(g,r,c)==0   )
            {
				*row = r;
				*col = c;
				if ((grid_read_count(g, r, c) > 0))
				{
					for (val = 1; val < Max_Value + 1; val++)
					{
						if (grid_choice_is_valid(g, r, c, val))
						{
							return val;
						}
					}
				}
				else
				{
					return 0;
				}
				
			
                
            }       
        }
    }
    


    return 0;
}

/* 
    This method check the row of the (r,col)
    for errors,,ignoring the 0's
    @return if an error found (0) or not (1)
*/
static int  check_row(Grid_T board, int r,int col,int val,int to_print)
{
    int c=0;
    board.elts[r][col].value=0;/*in order not to check myself*/
    for (c=0;c<rows; c++)
    {
        if(board.elts[r][c].value==val && val!=0)
        {
            if(to_print){printf("error,in column : %d row : %d\n",c,r);}


            return 0;
        }
    }
    return 1;
}
/* 
    This method check the row of the (r,col)
    for errors.
    @return if an error found (0) or not (1)
*/
static int  check_row_without_zero(Grid_T board, int r,int col,int val)
{
    int c=0;
    board.elts[r][col].value=0;/*in order not to check myself*/
    for (c=0;c<rows; c++)
    {
        if(board.elts[r][c].value==val)
        {
            return 0;
        }
    }
    return 1;
}
/* 
    This method check the column of the (r,col)
    for errors,,ignoring the 0's
    @return if an error found (0) or not (1)
*/
static int  check_column(Grid_T board, int row,int c,int val,int to_print)
{
    int r=0;
    board.elts[row][c].value=0;/*in order not to check myself*/
    for (r=0;r<columns; r++)
    {
        if(board.elts[r][c].value==val && val!=0)
        {
            if(to_print){printf("error,in column : %d row : %d\n",c,r);}
            return 0;
        }
    }
    return 1;
}
/* 
    This method check the column of the (r,col)
    for errors.
    @return if an error found (0) or not (1)
*/
static int  check_column_without_zero(Grid_T board, int row,int c,int val)
{
    int r=0;
    board.elts[row][c].value=0;/*in order not to check myself*/
    for (r=0;r<columns; r++)
    {
        if(board.elts[r][c].value==val)
        {
            return 0;
        }
    }
    return 1;
}
/* 
    This method check the box of the (r,col)
    for errors,ignoring the 0's
    @return if an error found (0) or not (1)
*/
static int check_boxes(Grid_T board,int c,int r,int val,int to_print)
{
    int row_start,col_start,row_end,col_end;
    int col,row;
    row_start= r/3*3;
    row_end=row_start+3;
    col_start=c/3*3;
    col_end=col_start+3;
    board.elts[r][c].value=0;/*in order not to check myself*/
    for(row=row_start; row<row_end; row++)
    {
        for(col=col_start; col<col_end; col++)
        {
            if(board.elts[row][col].value==val && val!=0)
            {
               /* printf("check boxes error\n");*/
                 if(to_print){printf("error,in box with row: %d - %d , column : %d - %d \n",row_start,row_end,col_start,col_end);}
                return 0;
            }
        }
    }
    return 1;

}
/* Print all row, col, sub-grid errors/conflicts found in puzzle g;
   some errors may be reported more than once. */
void sudoku_print_errors(Grid_T g)
{
    int row , col,val;
    for(row=0; row<rows; row++)
    {
        for(col=0; col<columns; col++)
        {
            val=grid_read_value(g,row,col);
            check_boxes(g,col,row,val,1);
            check_column(g,row,col,val,1);
            check_row(g,row,col,val,1);

        }
    }
}
/* 
    This method check the box of the (r,col)
    for errors.
    @return if an error found (0) or not (1)
*/
static int check_boxes_without_zero(Grid_T board,int c,int r,int val)
{
    int row_start,col_start,row_end,col_end;
    int col,row;
    row_start= r/3*3;
    row_end=row_start+3;
    col_start=c/3*3;
    col_end=col_start+3;
    board.elts[r][c].value=0;/*in order not to check myself*/
    for(row=row_start; row<row_end; row++)
    {
        for(col=col_start; col<col_end; col++)
        {
            if(board.elts[row][col].value==val)
            {
               /* printf("check boxes error\n");*/

                return 0;
            }
        }
    }
    return 1;

}
/* 
    This method initializes the choices of every cell
*/
static void sudoku_init_choices(Grid_T *g)
{
    int r,c,val=1;
    for(r=0; r<rows; r++)
    {
        for(c=0; c<columns; c++)
        {
            if(g->elts[r][c].value==0)
            {

                for(val=1; val<Max_Value+1; val++)
                {
                    if( ( check_column(*g,r,c,val,0) ) && (check_row(*g,r,c,val,0) ) && ( check_boxes(*g,c,r,val,0) ) )
                    {
						if (g->elts[r][c].choices.num[val]==0)
						{
							grid_set_choice(g,r,c,val);
							g->elts[r][c].choices.count++;

						}

                    }
					else
					{
						if (g->elts[r][c].choices.num[val]==1)
						{
							g->elts[r][c].choices.num[val] = 0;
							g->elts[r][c].choices.count--;
						}
					}
					

                }
            }
        }
    }
}
/*
    This method checks if a board is correct,
    having 0's.
*/
int sudoku_is_correct_solution(Grid_T g)
{
    int r,c,val;
    for(r=0; r<rows; r++)
    {
        for(c=0; c<columns; c++)
        {
            val=g.elts[r][c].value;
            if( ( !check_column(g,r,c,val,0) ) || (!check_row(g,r,c,val,0) ) || (! check_boxes(g,c,r,val,0) ) )
            {
                return 0;
            }
        }
    }
    return 1;
}

/* Return true iff puzzle g is correct. */
int sudoku_is_correct(Grid_T g)
{
    int r,c,val;
    for(r=0; r<rows; r++)
    {
        for(c=0; c<columns; c++)
        {
            val=g.elts[r][c].value;
            if( ( !check_column_without_zero(g,r,c,val) ) || (!check_row_without_zero(g,r,c,val) ) || (! check_boxes_without_zero(g,c,r,val) ) || val==0 )
            {
                return 0;
            }
        }
    }
    return 1;
}
/* 
    This method initializes the board to it's defualt state
*/
static void init_board(Grid_T* board)
{
    int i=0,j=0,k;
	grid_set_unique(board);
	for(i=0; i<rows; i++)
    {
        for(j=0; j<columns; j++)
        {
			(board->elts[i][j]).choices.count = 0;
            grid_clear_value(board,i,j);
			for (k=0; k<Max_Value+1; k++)
            {
                (board->elts[i][j]) .choices.num[k]=0;
            }
        }
    } 
}

/* 
    This method take a sudoku
    as input from stdin
    @return the Grid with the sudoku
*/
Grid_T sudoku_read(void)
{
    Grid_T board;
    int r=0,c=0,number;
    init_board(&board);
    while(  (scanf("%d",&number) )!=EOF)
    {
       
        if(number!=' ' && number!='\n')
        {
            
            board.elts[r][c].value=number;
           
            if(c<columns-1)/*check if we filled the row*/
            {
                c++;
            }
            else/*change row*/
            {
                c=0;
                r++;
            }
        }
        if(r==9){break;}
        
        
        
    
    }
    return board;
}

/*
    This method copys the data of the grid g
    to another board and returns it
*/
Grid_T copy_grid(Grid_T g)
{
	int r, c, val = 1;
	Grid_T grid;
	grid.unique = g.unique;
	for (r = 0; r < rows; r++)
	{
		for (c = 0; c < columns; c++)
		{
			grid.elts[r][c].value = g.elts[r][c].value;
			grid.elts[r][c].choices.count = g.elts[r][c].choices.count;

			for (val = 0; val < Max_Value + 1; val++)
			{
				grid.elts[r][c].choices.num[val] = g.elts[r][c].choices.num[val];

			}
			
		}
	}
	return grid;
}




/* Sovle puzzle g and return the solved puzzle; if the puzzle has
   multiple solutions, return one of the possible solutions. */
Grid_T sudoku_solve(Grid_T g)
{
	int r , c;
    int remain_choices;
	Grid_T tmp_g;
	static int  n = 0,solved=0;
	sudoku_init_choices(&g);
	
	while (1)
	{
	
		n = sudoku_try_next(g, &r, &c);
		
        if (n == 0)/*no choices available*/
		{

			return g;
		}
		remain_choices = sudoku_update_choice(&g, r, c, n);
		
		if (remain_choices == 0)/*we have a unique choice*/
		{
			sudoku_eliminate_choice(&g, r, c, n);
		}
		else
		{
			grid_clear_unique(&g);
		}
		
		
        tmp_g = copy_grid(g);
		if (sudoku_is_correct(tmp_g))
		{
			

			solved = 1;
			return tmp_g;

		}
		tmp_g = sudoku_solve(tmp_g);
		grid_clear_value(&g, r, c);
		grid_clear_unique(&g);
	
		if (solved)
		{
			return tmp_g;

		}				
	}
	
}

/*
    This method returns a ready puzzle solved.
*/
static Grid_T sudoku_ready_puzzle(void)
{
    Grid_T new_grid;
    init_board(&new_grid);
 

    return sudoku_solve(new_grid);
}
/*
    This method trys to create a puzzle, 
    n trys can only be performed or a 
    presolved sudoku is returned

*/
static Grid_T sudoku_create_puzzle(Grid_T g)
{
    int r , c;
    int remain_choices;
	Grid_T tmp_g,ready_grid;
	static int  n = 0, solved=0,failed_tries=0,made_ready_board=0;
	sudoku_init_choices(&g);
	if(!made_ready_board)
    {
        ready_grid = sudoku_ready_puzzle();
    }

	while (1)
	{
        made_ready_board=1;
  
		n = sudoku_try_next(g, &r, &c);
        if (n == 0)/*no choices available*/
		{
            failed_tries++;
			
	

			return g;
		}
       
		remain_choices = sudoku_update_choice(&g, r, c, n);
        if (remain_choices == 0)/*we have a unique choice*/
		{
			sudoku_eliminate_choice(&g, r, c, n);
		}
		else
		{
			grid_clear_unique(&g);
		}
		
	
        tmp_g = copy_grid(g);

		if (sudoku_is_correct(tmp_g))
		{
			solved = 1;
			return tmp_g;

		}
		tmp_g = sudoku_create_puzzle(tmp_g);
		grid_clear_value(&g, r, c);
			
		
		if (solved)
		{
			return tmp_g;

		}		
        if(failed_tries==500)
        {
           
            return ready_grid;
        }		
	}
}

/* 
    This method generates a complete sudoku puzzle.
*/
static Grid_T sudoku_generate_complete(void)
{
    Grid_T grid;
	init_board(&grid);
    grid=sudoku_create_puzzle(grid);
    return grid;
}


/* Generate and return a sudoku puzzle with "approximately" nelts
   elements having non-0 value. The smaller nelts the harder may be to
   generate/solve the puzzle. For instance, nelts=81 should return a
   completed and correct puzzle. */
Grid_T sudoku_generate(int nelts)
{
    Grid_T new_grid;
    int row,col,deleted_cells=81,generate_unique=0;
    int val;
    new_grid=sudoku_generate_complete();
    printf("GENERATED BOARD BEFORE ELIMINATING NELTS\n");
    sudoku_print(stderr,new_grid);
    /* if the nelts >81 it means that we want to generate
       sudoku with unique choice,(i add to nelts 100 so 
       in order to know if we want a unique one) 
    */
    if(nelts>81)
    {
        generate_unique=1;
        nelts-=100;
        if(nelts<27)
        {
            nelts=30;
        }
    }
/*    srand(getpid());*/
    deleted_cells-=nelts;
    while(deleted_cells>0)
    {
        /* pick random row and column to delete*/
        row=rand()%9;
        col=rand()%9;
        if(new_grid.elts[row][col].value!=0 )
        {
            val=grid_read_value(new_grid,row,col);
			grid_update_value(&new_grid, row, col, 0);
			/*check_grid = sudoku_solve(new_grid);*/
			
            if(generate_unique)
            {
                /* check if the current deletion returns a unique sudoku 
                   solution , and apply it or ignore it*/ 
                if (sudoku_solution_is_unique(new_grid) )
			    {
        	    	grid_set_choice(&new_grid,row,col,val);
			    	new_grid.elts[row][col].choices.count++;
			    	deleted_cells--;

			    }
			    else
			    {
			    	grid_update_value(&new_grid, row, col, val);
			    }
                if(deleted_cells!=0)
                {
                    grid_set_unique(&new_grid);

                }
            }
            else
            {
                grid_set_choice(&new_grid,row,col,val);
			    new_grid.elts[row][col].choices.count++;
			    deleted_cells--;

            }
            
            
            
          
		        
        }

    }
    return new_grid;
}

/* Returns true if solution g, as returned by sudoku_solve, has a
   unique choice for each step (no backtracking required). (Note, g
   must have been computed with the use of sudoku_solve.) */
int sudoku_solution_is_unique(Grid_T g)
{
	Grid_T grid;
	grid=sudoku_solve(g);

    

	return grid_read_unique(grid);
}

/* main function */
int main(int argc, char *argv[])
{
    Grid_T board;
	init_board(&board);
	
    if(argv[1]!=NULL && strcmp(argv[1],"-c" )==0)
    {
	    board=sudoku_read();
        sudoku_print(stderr,board);

        sudoku_print_errors(board);
        if(sudoku_is_correct_solution(board))
        {
            printf("Correct board!\n");
        }
        
    }
    else if(argv[1]!=NULL && strcmp ( argv[1],"-g" )==0 )
    {
        if(argv[2]==NULL){return 0;}
        if(argv[3]!=NULL && strcmp ( argv[3],"-u" )==0)
        {
	        board=sudoku_generate(atoi(argv[2])+100);

        }
        else
        {
	        board=sudoku_generate(atoi(argv[2]));
        }
        
        printf("Board after eliminating %d nelts\n",atoi(argv[2]));
        sudoku_print(stderr,board);

        if (sudoku_solution_is_unique(board))
	    {
		    printf("unique solution!!\n");
	    }
	    else
	    {
		    printf("not a unique solution\n");
	    }
    }
    else
    {
	    board=sudoku_read();
        sudoku_print(stderr,board);

        board=sudoku_solve(board);
        if (sudoku_is_correct(board))
        {

            if(grid_read_unique(board))
            {
                printf("Puzzle has a (unique choice) solution\n");
            }
            else
            {
                printf("The are many solutions for this Puzzle\n");
            }
            
        
        }
        else
        {
            printf("Puzzle has no sulution\n");
        }
        sudoku_print(stderr,board);
        sudoku_print_errors(board);
        
       
    }
    
    
    return 0;
}


/* Print the sudoku puzzle defined by g to stream s in the same format
   as expected by sudoku_read(). */
void sudoku_print(FILE *s, Grid_T g)
{
    int r,c,val;
    for(r=0; r<rows; r++)
    {
        for(c=0; c<columns; c++)
        {
            val=grid_read_value(g,r,c);
            fprintf(s,"%d", val);
            fprintf(s," ");
        }
        fprintf(s,"\n");
    }
}
