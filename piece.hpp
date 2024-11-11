// piece.hpp

#include <iostream>
#include "rotMatricies.hpp"

#ifndef PIECE
#define PIECE

class piece {
public:
    int pos[3]; // Position array, (0,0,0) = center piece
    char col[3]; // Color array (x,y,z) => ('O','W','B')... ('B','NULL','G')
    // White = 'W'
    // Red = 'R'
    // Blue = 'B'
    // Green = 'G'
    // Orange = 'O'
    // Yellow = 'Y'

    rotMatrix rotMatricies;

    piece(int x = 0, int y = 0, int z = 0) {
        pos[0] = x;
        pos[1] = y;
        pos[2] = z;
        col[0] = 'N';
        col[1] = 'N';
        col[2] = 'N';
    }

    void setColor(char colorX, char colorY, char colorZ) {
        col[0] = colorX;
        col[1] = colorY;
        col[2] = colorZ;
    }

    void rotate(int rotMatrix[3][3]) {
        int newPos[3];
        char newCol[3];

        for (int i = 0; i < 3; i++) {
            newPos[i] = 0;
            for (int j = 0; j < 3; j++) {
                newPos[i] += rotMatrix[i][j] * pos[j];
            }
        }

        for (int i = 0; i < 3; i++) {
            pos[i] = newPos[i];
        }

        for (int i = 0; i < 3; i++) {
            char temp = col[i];
            col[i] = col[(int)newPos[i]];
            col[(int)newPos[i]] = temp;
        }

    }


};

#endif