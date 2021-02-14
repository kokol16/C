#include"grid.h"
#define true 1
#define false 0
#include<stdio.h>
/* return value of i,j */

int grid_read_value(Grid_T g, int i, int j)
{
    return g.elts[i][j].value;
}
/* update value of i,j to n */

void grid_update_value(Grid_T *g, int i, int j, int n)
{
    g->elts[i][j].value=n;
}
void grid_clear_value(Grid_T *g, int i, int j)
{
	g->elts[i][j].value = 0;
}
/* set (to 1)  choice n for elt i,j */

void grid_set_choice(Grid_T *g, int i, int j, int n)
{
    g->elts[i][j].choices.num[n]=1;

}

/* clear (to 0) choice n for elt i,j */
void grid_clear_choice(Grid_T *g, int i, int j, int n)
{
    g->elts[i][j].choices.num[n]=0;

}

/* true if choice n for elt i,j is valid */
int grid_choice_is_valid(Grid_T g, int i, int j, int n)
{
    if(g.elts[i][j].choices.num[n])
    {
        return true;
    }
    return false;
}

/* remove n from choices of elt i,j and adjust count only if n is a
   valid choice for elt i,j */
void grid_remove_choice(Grid_T *g, int i, int j, int n)
{
    if ( g->elts[i][j].choices.num[n] )
    {
        g->elts[i][j].choices.num[n]=0;
        g->elts[i][j].choices.count--;
    }

}
/* return count,  or clear (to 0) count for elt i, j */
int grid_read_count(Grid_T g, int i, int j)
{
    return  g.elts[i][j].choices.count;
}
/*  set count (to 9) for elt i, j */
void grid_set_count(Grid_T *g, int i, int j)
{
    g->elts[i][j].choices.count=9;
}
/*  clear count  (to 0) for elt i, j */
void grid_clear_count(Grid_T *g, int i, int j)
{
    g->elts[i][j].choices.count=0;
}

/* return val unique flag for g */
int grid_read_unique(Grid_T g)
{
    return  g.unique;

}
/*  set (to 1) unique flag for g */

void grid_set_unique(Grid_T *g)
{
    g->unique=1;
}
/*  clear (to 0) unique flag for g */

void grid_clear_unique(Grid_T *g)
{
    g->unique=0;
}