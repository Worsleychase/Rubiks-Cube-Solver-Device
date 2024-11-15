#ifndef CUBESOLVER
#define CUBESOLVER

#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <functional>

#include "cube.hpp"
#include "timer.hpp"

class CubeSolver {
public:
    std::vector<char> solutionMoves;
    CubeSolver(const virCube& initialCube) : cube(initialCube) {}

    struct CubeState {
        virCube cube;
        std::vector<char> moves;
        int depth;

        CubeState(const virCube& initialCube, const std::vector<char>& initialMoves = {}, int depth = 0)
            : cube(initialCube), moves(initialMoves), depth(depth) {}
    };

    std::unordered_map<char, char> oppositeMoves = {
        {'f', 'F'}, {'F', 'f'}, {'r', 'R'}, {'R', 'r'}, {'b', 'B'}, {'B', 'b'},
        {'l', 'L'}, {'L', 'l'}, {'d', 'D'}, {'D', 'd'}, {'u', 'U'}, {'U', 'u'}
    };

    void solve() {
        Timer timer;
        timer.Start();
        thistle();
        timer.Stop();
        std::cout << "Solution moves: ";
        for (char c : solutionMoves) {
            std::cout << c << " ";
        }
        std::cout << "found in " << timer.Time() << " seconds." << std::endl;
    }

    void thistle() {
        phase1();
        phase2();
        phase3();
        phase4();
    }

    void phase1() {
        solutionMoves.clear(); // Clear solutionMoves at the start of phase1
        
        std::queue<CubeState> queue;
        std::unordered_set<std::string> visited;
        queue.push(CubeState(cube, {}, 0));
        visited.insert(cube.getStateID());

        while (!queue.empty()) {
            CubeState currentState = queue.front();
            queue.pop();

            // Check if the Cross is solved
            if (currentState.cube.isCross()) {
                for (char c : currentState.moves) {
                    solutionMoves.push_back(c);  // Add moves for phase 1
                }
                std::cout << "Phase 1 finished" << std::endl;
                return;
            }

            // Generate moves and push to the queue
            for (char move : {'f', 'F', 'r', 'R', 'b', 'B', 'l', 'L', 'd', 'D', 'u', 'U'}) {
                virCube nextCube = applyMovesToCube(currentState.cube, {move});
                std::string nextStateID = nextCube.getStateID();

                if (visited.find(nextStateID) == visited.end()) {
                    visited.insert(nextStateID);
                    std::vector<char> nextMoves = currentState.moves;
                    nextMoves.push_back(move);
                    queue.push(CubeState(nextCube, nextMoves, currentState.depth + 1));
                }
            }
        }
    }

    void phase2() {
        solutionMoves.clear(); // Clear solutionMoves at the start of phase2

        std::queue<CubeState> queue;
        std::unordered_set<std::string> visited;
        queue.push(CubeState(cube, solutionMoves, 0)); // Start with moves from phase1
        visited.insert(cube.getStateID());

        while (!queue.empty()) {
            CubeState currentState = queue.front();
            queue.pop();

            // Check if the top layer is oriented
            if (currentState.cube.isTopLayerOriented()) {
                for (char c : currentState.moves) {
                    solutionMoves.push_back(c);  // Add new moves for phase 2
                }
                std::cout << "Phase 2 finished" << std::endl;
                return;
            }

            // Generate moves and push to the queue
            for (char move : {'f', 'F', 'r', 'R', 'b', 'B', 'l', 'L', 'd', 'D', 'u', 'U'}) {
                virCube nextCube = applyMovesToCube(currentState.cube, {move});
                std::string nextStateID = nextCube.getStateID();

                if (visited.find(nextStateID) == visited.end()) {
                    visited.insert(nextStateID);
                    std::vector<char> nextMoves = currentState.moves;
                    nextMoves.push_back(move);
                    queue.push(CubeState(nextCube, nextMoves, currentState.depth + 1));
                }
            }
        }
    }

    void phase3() {
        solutionMoves.clear(); // Clear solutionMoves at the start of phase3

        std::queue<CubeState> queue;
        std::unordered_set<std::string> visited;
        queue.push(CubeState(cube, solutionMoves, 0)); // Start with moves from phase2
        visited.insert(cube.getStateID());

        while (!queue.empty()) {
            CubeState currentState = queue.front();
            queue.pop();

            // Check if the middle layer is solved
            if (currentState.cube.isMiddleLayerSolved()) {
                for (char c : currentState.moves) {
                    solutionMoves.push_back(c);  // Add new moves for phase 3
                }
                std::cout << "Phase 3 finished" << std::endl;
                return;
            }

            // Generate moves and push to the queue
            for (char move : {'f', 'F', 'r', 'R', 'b', 'B', 'l', 'L', 'd', 'D', 'u', 'U'}) {
                virCube nextCube = applyMovesToCube(currentState.cube, {move});
                std::string nextStateID = nextCube.getStateID();

                if (visited.find(nextStateID) == visited.end()) {
                    visited.insert(nextStateID);
                    std::vector<char> nextMoves = currentState.moves;
                    nextMoves.push_back(move);
                    queue.push(CubeState(nextCube, nextMoves, currentState.depth + 1));
                }
            }
        }
    }

    void phase4() {
        solutionMoves.clear(); // Clear solutionMoves at the start of phase4

        std::queue<CubeState> queue;
        std::unordered_set<std::string> visited;
        queue.push(CubeState(cube, solutionMoves, 0)); // Start with moves from phase3
        visited.insert(cube.getStateID());

        while (!queue.empty()) {
            CubeState currentState = queue.front();
            queue.pop();

            // Check if the cube is solved
            if (currentState.cube.isSolved()) {
                for (char c : currentState.moves) {
                    solutionMoves.push_back(c);  // Add final moves for phase 4
                }
                std::cout << "Phase 4 finished" << std::endl;
                return;
            }

            // Generate moves and push to the queue
            for (char move : {'f', 'F', 'r', 'R', 'b', 'B', 'l', 'L', 'd', 'D', 'u', 'U'}) {
                virCube nextCube = applyMovesToCube(currentState.cube, {move});
                std::string nextStateID = nextCube.getStateID();

                if (visited.find(nextStateID) == visited.end()) {
                    visited.insert(nextStateID);
                    std::vector<char> nextMoves = currentState.moves;
                    nextMoves.push_back(move);
                    queue.push(CubeState(nextCube, nextMoves, currentState.depth + 1));
                }
            }
        }
    }

private:
    virCube cube;

    // Helper function to apply moves to a cube state
    virCube applyMovesToCube(const virCube& cube, const std::vector<char>& moves) {
        virCube newCube = cube;
        for (char move : moves) {
            newCube.rotateFace(move);
        }
        return newCube;
    }
};

#endif
