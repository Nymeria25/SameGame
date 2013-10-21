#ifndef STRATEGY_H_INCLUDED
#define STRATEGY_H_INCLUDED

#include <vector>

using namespace std;

class World{

int **matrix;
const int rows, columns;
int points;


public:
    World(const int r, const int c);
    ~World();
    void Fill();
    const int get_rows();
    const int get_columns();
    int get_number(int, int);
    int add_points(int);
    vector <int> lee(int, int);
    vector <int> Move_buttons();
    vector <int> Move_blocks();




};


#endif // STRATEGY_H_INCLUDED
