//
// Created by albert on 6/9/23.
//

#ifndef BOMA_LOCATION_H
#define BOMA_LOCATION_H

typedef struct {
    int line;
    int column;
} Location;

Location* createLocation(int line, int column);
int getColumn(Location* location);
int getLine(Location* location);

#endif //BOMA_LOCATION_H
