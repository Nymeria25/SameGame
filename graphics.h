#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED
#include <FL/Fl_Button.H>
#include <vector>

#include "strategy.h"

using namespace std;



class Graph {

World * world; //pointer to the strategy matrix's class
const int rows, columns;


public:

    Graph(World *, const int, const int);


};


#endif // GRAPHICS_H_INCLUDED
