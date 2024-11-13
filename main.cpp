// main.cpp

#include "cube.hpp"

int main() {
    virCube cube;


    cube.printCube();
    cube.pieces[0][3].print();
    cube.rotateFace('f');
    std::cout << std::endl;
    cube.printCube();
    cube.pieces[0][3].print();




    return 0;
}