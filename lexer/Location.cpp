//
// Created by albert on 6/9/23.
//
#include <stdlib.h>

#include "Location.h"

Location* createLocation(int line, int column){
    auto* location = (Location *) malloc(sizeof (Location));
    location->line = line;
    location->column = column;
    return location;
}

int getColumn(Location* location) {
    return location->column;
}

int getLine(Location* location) {
    return location->line;
}
