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

    int rotationCount;

    virCube() {
        rotationCount = 0;
        for (int layer = 0; layer < 3; layer++) {
            for (int position = 0; position < 9; position++) {
                int x = position % 3 - 1;
                int y = 1 - position / 3;
                int z = 1- layer;
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
            std::cout << pieces[2][i].col[1] << " ";
        }
        std::cout << std::endl;
        std::cout << "       ";
        for (int i = 0; i < 3; i++) {
            std::cout << pieces[1][i].col[1] << " ";
        }
        std::cout << std::endl;
        std::cout << "       ";
        for (int i = 0; i < 3; i++) {
            std::cout << pieces[0][i].col[1] << " ";
        }
        std::cout << std::endl;

        // Print left, front, right, and back faces
        for (int i = 0; i < 3; i++) {
            // Left face
            for (int j = 0; j < 3; j++) {
                std::cout << pieces[2-j][i * 3].col[0] << " ";
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
            for (int j = 2; j >= 0; j--) {
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
        rotationCount++;
        rotMatrix rotMatricies;
        piece temp[9];
        switch (face)
        {
        case 'f': {
            for (int i = 0; i < 9; i++) {
                temp[i] = pieces[0][i];
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.FCW);
            }

            for (int i = 0; i < 9; i++) {
                int x = temp[i].pos[0];
                int y = temp[i].pos[1];
                int newIndex = (1 - y) * 3 + (x + 1);
                pieces[0][newIndex] = temp[i];
            }
            break;
            }

        case 'F': {
            for (int i = 0; i < 9; i++) {
                temp[i] = pieces[0][i];
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.FCCW);
            }

            for (int i = 0; i < 9; i++) {
                int x = temp[i].pos[0];
                int y = temp[i].pos[1];
                int newIndex = (1 - y) * 3 + (x + 1);
                pieces[0][newIndex] = temp[i];
            }
            break;
            }

        case 'r': {
            int index = 0;
            for (int layer = 0; layer < 3; layer++) {
                for (int pos = 2; pos < 9; pos += 3) {
                    temp[index++] = pieces[layer][pos];
                }
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.RCW);
            }

            for (int i = 0; i < 9; i++) {
                int y = temp[i].pos[1];
                int z = temp[i].pos[2];
                int layer = 1 - z;
                int pos = (1 - y) * 3 + 2;
                pieces[layer][pos] = temp[i];
            }
            break;            
            }

        case 'R': {
            int index = 0;
            for (int layer = 0; layer < 3; layer++) {
                for (int pos = 2; pos < 9; pos += 3) {
                    temp[index++] = pieces[layer][pos];
                }
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.RCCW);
            }

            for (int i = 0; i < 9; i++) {
                int y = temp[i].pos[1];
                int z = temp[i].pos[2];
                int layer = 1 - z;
                int pos = (1 - y) * 3 + 2;
                pieces[layer][pos] = temp[i];
            }
            break;
        }

        case 'b': {
            int index = 0;
            for (int i = 0; i < 9; i++) {
                temp[i] = pieces[2][i];
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.BCW);
            }

            for (int i = 0; i < 9; i++) {
                int x = temp[i].pos[0];
                int y = temp[i].pos[1];
                int newIndex = (1 - y) * 3 + (x + 1);
                pieces[2][newIndex] = temp[i];
            }
            break;
        }

        case 'B': {
            int index = 0;
            for (int i = 0; i < 9; i++) {
                temp[i] = pieces[2][i];
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.BCCW);
            }

            for (int i = 0; i < 9; i++) {
                int x = temp[i].pos[0];
                int y = temp[i].pos[1];
                int newIndex = (1 - y) * 3 + (x + 1);
                pieces[2][newIndex] = temp[i];
            }
            break;
        }

        case 'l': {
            int index = 0;
            for (int layer = 0; layer < 3; layer++) {
                for (int pos = 0; pos < 9; pos += 3) {
                    temp[index++] = pieces[layer][pos];
                }
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.LCW);
            }

            for (int i = 0; i < 9; i++) {
                int y = temp[i].pos[1];
                int z = temp[i].pos[2];
                int layer = 1 - z;
                int pos = (1 - y) * 3;
                pieces[layer][pos] = temp[i];
            }
            break;
        }

        case 'L': {
            int index = 0;
            for (int layer = 0; layer < 3; layer++) {
                for (int pos = 0; pos < 9; pos += 3) {
                    temp[index++] = pieces[layer][pos];
                }
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.LCCW);
            }

            for (int i = 0; i < 9; i++) {
                int y = temp[i].pos[1];
                int z = temp[i].pos[2];
                int layer = 1 - z;
                int pos = (1 - y) * 3;
                pieces[layer][pos] = temp[i];
            }
            break;
        }

        case 'd': {
            int index = 0;
            for (int layer = 0; layer < 3; layer++) {
                for (int pos = 6; pos < 9; pos++) {
                    temp[index++] = pieces[layer][pos];
                }
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.DCW);
            }

            for (int i = 0; i < 9; i++) {
                int x = temp[i].pos[0];
                int z = temp[i].pos[2];
                int layer = 1 - z;
                int pos = 6 + (x + 1);
                pieces[layer][pos] = temp[i];
            }
            break;
        }

        case 'D': {
            int index = 0;
            for (int layer = 0; layer < 3; layer++) {
                for (int pos = 6; pos < 9; pos++) {
                    temp[index++] = pieces[layer][pos];
                }
            }

            for (int i = 0; i < 9; i++) {
                temp[i].rotate(rotMatricies.DCCW);
            }

            for (int i = 0; i < 9; i++) {
                int x = temp[i].pos[0];
                int z = temp[i].pos[2];
                int layer = 1 - z;
                int pos = 6 + (x + 1);
                pieces[layer][pos] = temp[i];
            }
            break;
        }
        case 'u': {// R L F2 B2 R' L' D R L F2 B2 R' L' 
            rotationCount += 16;
            rotateFace('r');
            rotateFace('l');
            rotateFace('f');
            rotateFace('f');
            rotateFace('b');
            rotateFace('b');
            rotateFace('R');
            rotateFace('L');
            rotateFace('d');
            rotateFace('r');
            rotateFace('l');
            rotateFace('f');
            rotateFace('f');
            rotateFace('b');
            rotateFace('b');
            rotateFace('R');
            rotateFace('L');
            break;
            }

        case 'U': {// L R F2 B2 L' R' D' L R F2 B2 L' R'
            rotationCount += 16;
            rotateFace('l');
            rotateFace('r');
            rotateFace('f');
            rotateFace('f');
            rotateFace('b');
            rotateFace('b');
            rotateFace('L');
            rotateFace('R');
            rotateFace('D');
            rotateFace('l');
            rotateFace('r');
            rotateFace('f');
            rotateFace('f');
            rotateFace('b');
            rotateFace('b');
            rotateFace('L');
            rotateFace('R');
            break;
            }
        }   
    }

    void randomize(int numMoves) {
        const char moves[] = {'f', 'F', 'r', 'R', 'b', 'B', 'l', 'L', 'd', 'D', 'u', 'U'};
        
        for (int i = 0; i < numMoves; i++) {
            int randomIndex = rand() % 12;
            char move = moves[randomIndex];
            rotateFace(move);
        }
    }


};

#endif