#include "strategy.h"
#include <time.h>
#include <cstdlib>
#include <iostream>

using namespace std;

World::World(const int number_of_rows, const int number_of_cols) : rows(number_of_rows), columns(number_of_cols)
{

     int i,j;

    points = 0; //initializes the number of points (score)

    matrix = new int * [rows];
    for(i=0; i<rows; i++)
      matrix[i] = new int [columns];

    for(i=0; i<rows; i++)
      for(j=0; j<columns; j++)
        matrix[i][j] = 0;


}

World :: ~World()
{

    for(int i=0; i<rows; i++)
      delete matrix[i];

    delete matrix;
}

void World::Fill()
{
    int i,j,r;

    //fills the strategy matrix with random numbers, simbolysing colors

    srand( time(NULL));
    for(i=0; i<rows; i++)
        for(j=0; j<columns; j++)
        {
            r = rand() % 139 + ( rand() % 49) + (rand() % 2053); //generate random number
            r = r%4 + 1; //must be between 1 and 4
            matrix[i][j] = r; //put the number in the matrix
        }

}

const int World::get_rows()
{
    return rows;
}

const int World::get_columns()
{
    return columns;
}


int World::get_number(int x, int y)
{
    return matrix[x][y];
}

int World::add_points(int x)
{
    points += x;
    return points;
}



vector <int> World::lee(int x, int y) //coordinates of the button from where the algorithm starts
{

    vector <int> coord; //coordinates
    int l[500], c[500];
    int i,j,a,b;

    int initial = matrix[x][y]; //the initial color of the button, in case there aren't enough buttons around

    i = j = 1;
    a = x;
    b = y;
    l[i] = x;
    c[i] = y;
    int info = matrix[a][b]; matrix[a][b] = -1;

    while( i<=j && info != -1)
    {
        a = l[i]; b = c[i];

        if(a < rows - 1 && matrix[a+1][b] == info)    {j++; l[j] = a+1; c[j] = b; matrix[a+1][b] = -1;}
        if(a > 0 && matrix[a-1][b] == info)           {j++; l[j] = a-1; c[j] = b; matrix[a-1][b] = -1;}
        if(b < columns - 1 && matrix[a][b+1] == info) {j++; l[j] = a; c[j] = b+1; matrix[a][b+1] = -1;}
        if(b > 0 && matrix[a][b-1] == info)           {j++; l[j] = a; c[j] = b-1; matrix[a][b-1] = -1;}

        i++;
    }

  int N = i-1;

  if( N>=2 ) //if there are enough buttons around, we delete them
  {
      for(int i = 1; i<=N; i++)
      {
          coord.push_back(l[i]);
          coord.push_back(c[i]);
      }



  }

  else matrix[x][y] = initial; //else we put back the initial color




  return coord;
 }

vector <int> World::Move_buttons()
{
    int i,j;
    vector <int> new_coord; //previous x, y and next x, y

    for(i=rows-1; i>0; i--)
        for(j=0; j<columns; j++)
          if(matrix[i][j] == -1 && matrix[i-1][j] != -1)
          {
              new_coord.push_back(i-1); //here are the previous x and y
              new_coord.push_back(j);

              int button = matrix[i-1][j];
              matrix[i-1][j] = -1;


              int k = i;
              while(matrix[k][j] == -1 ) {k++; if( k == rows) break;}

              k--;

              new_coord.push_back(k); // the next y
              matrix[k][j] = button;

          }


    return new_coord;

}

vector <int> World::Move_blocks()
{

     int i,j;
     vector <int> coord; // coord[0] keeps the ratio of moving blocks
     int first_gap = -1, first_column = -1, dif;

      for(i=0; i<columns; i++)
       {
           if(matrix[rows-1][i] == -1 && first_gap == -1) first_gap = i;
           if(first_gap != -1 && matrix[rows-1][i] != -1) {first_column = i; break;}

       }



      if(first_column != -1)
    {
      coord.push_back(first_gap);
      coord.push_back(first_column);

      dif = first_column - first_gap;



      for(i=0; i<rows; i++)
        for(j=0; j<columns; j++)
         if(j >= first_column) {matrix[i][j-dif] = matrix[i][j]; matrix[i][j] = -1;}



    return coord;

}

}





