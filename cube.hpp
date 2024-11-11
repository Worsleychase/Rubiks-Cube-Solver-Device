// cube.hpp

#include "piece.hpp"

#ifndef CUBE
#define CUBE

class virCube {
public:
    piece pieces[3][9]; // Array of pieces, where the first index is the "layer", so pieces[0]: z=1, pieces[1]: z=0, pieces[2]: z=-1
                        // Second index is the position facing the XY plane (front-facing), in a square going from 0-8.

    // Front = pieces[0]                                            col[2]
    // Right = pieces[0]2,5,8 + pieces[1]2,5,8 + pieces[2]2,5,8     col[0]
    // Back = pieces[2]                                             col[2]
    // Left = pieces[0]0,3,6 + pieces[1]0,3,6 + pieces[2]0,3,6      col[0]
    // Up = pieces[0]0,1,2 + pieces[1]0,1,2 + pieces[2]0,1,2        col[1]
    // Down = pieces[0]6,7,8   pieces[1]6,7,8 + pieces[2]6,7,8      col[1]


    virCube() {
        for (int layer = 0; layer < 3; layer++) {
            for (int position = 0; position < 9; position++) {
                int x = position % 3 - 1;
                int y = position / 3 - 1;
                int z = layer - 1;
                pieces[layer][position] = piece(x, y, z);

                if (layer == 0) {
                    pieces[layer][position].col[2]='O'; // Front Color
                } else if (layer == 2) {
                    pieces[layer][position].col[2]='R'; // Back Color
                }

                if (position % 3 == 0) {
                    pieces[layer][position].col[0]='G'; // Left Color
                } else if (position % 3 == 2) {
                    pieces[layer][position].col[0]='B'; // Right Color
                }

                if (position / 3 == 0) {
                    pieces[layer][position].col[1]='Y'; // Top Color
                } else if (position / 3 == 2) {
                    pieces[layer][position].col[1]='W'; // Bottom Color
                }
            }
        }
    }

    void printCube() {
        // Print top face
        std::cout << "       ";
        for (int i = 0; i < 3; i++) {
            std::cout << pieces[0][i].col[1] << " ";
        }
        std::cout << std::endl;
        std::cout << "       ";
        for (int i = 0; i < 3; i++) {
            std::cout << pieces[1][i].col[1] << " ";
        }
        std::cout << std::endl;
        std::cout << "       ";
        for (int i = 0; i < 3; i++) {
            std::cout << pieces[2][i].col[1] << " ";
        }
        std::cout << std::endl;

        // Print left, front, right, and back faces
        for (int i = 0; i < 3; i++) {
            // Left face
            for (int j = 0; j < 3; j++) {
                std::cout << pieces[j][i * 3].col[0] << " ";
            }
            std::cout << " ";

            // Front face
            for (int j = 0; j < 3; j++) {
                std::cout << pieces[0][i * 3 + j].col[2] << " ";
            }
            std::cout << " ";

            // Right face
            for (int j = 0; j < 3; j++) {
                std::cout << pieces[j][i * 3 + 2].col[0] << " ";
            }
            std::cout << " ";

            // Back face
            for (int j = 0; j < 3; j++) {
                std::cout << pieces[2][i * 3 + j].col[2] << " ";
            }
            std::cout << std::endl;
        }

        // Print bottom face
        std::cout << "       ";
        for (int i = 0; i < 3; i++) {
            std::cout << pieces[0][i + 6].col[1] << " ";
        }
        std::cout << std::endl;
        std::cout << "       ";
        for (int i = 0; i < 3; i++) {
            std::cout << pieces[1][i + 6].col[1] << " ";
        }
        std::cout << std::endl;
        std::cout << "       ";
        for (int i = 0; i < 3; i++) {
            std::cout << pieces[2][i + 6].col[1] << " ";
        }
        std::cout << std::endl;
    }

    // f = front clockwise, F = front counter clockwise, u = upper clockwise, etc...
    void rotateFace(char face) {
        rotMatrix rotMatricies;

        switch (face)
        {
        case 'f':
            
            break;
    } 

};

#endif