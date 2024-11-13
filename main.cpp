// main.cpp

#include <string>
#include "cube.hpp"

void takeCommands();

int main() {
    takeCommands();
    
    return 0;
}

void takeCommands() {
    virCube cube;
    std::string command;

    cube.printCube();
    std::cout << std::endl;

    std::cout << "Enter commands (f,F,r,R,b,B,l,L,d,D,u,U), 'random', or 'q' to quit:" << std::endl;
    
    while (true) {
        std::cout << "> ";
        std::cin >> command;
        
        if (command == "q" || command == "Q") {
            break;
        }
        
        if (command == "random" || command == "randomize") {
            int moves;
            std::cout << "How many random moves? ";
            std::cin >> moves;
            cube.randomize(moves);  // or whatever number of moves you want
            cube.printCube();
            std::cout << std::endl;
        }
        else if (command.length() == 1 && 
            (command[0] == 'f' || command[0] == 'F' ||
            command[0] == 'r' || command[0] == 'R' ||
            command[0] == 'b' || command[0] == 'B' ||
            command[0] == 'l' || command[0] == 'L' ||
            command[0] == 'd' || command[0] == 'D' ||
            command[0] == 'u' || command[0] == 'U')) {
            cube.rotateFace(command[0]);
            cube.printCube();
            std::cout << std::endl;
        } else {
            std::cout << "Invalid command. Please try again." << std::endl;
        }
    }
}