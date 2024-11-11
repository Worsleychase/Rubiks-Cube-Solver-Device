// rotMatricies.hpp
// Stores rotational matricies for each side/face

#ifndef MATRICIES
#define MATRICIES

class rotMatrix {
public:
    int FCW[3][3] = {
        {0, 1, 0},
        {-1, 0, 0},
        {0, 0, 1}
    };
    int FCCW[3][3] = {
        {0, -1, 0},
        {1, 0, 0},
        {0, 0, -1}
    };

    int RCW[3][3] = {
        {1, 0, 0},
        {0, 0, 1},
        {0, -1, 0}
    };
    int RCCW[3][3] = {
        {1, 0, 0},
        {0, 0, -1},
        {0, 1, 0}
    };

    int LCW[3][3] = {
        {1, 0, 0},
        {0, 0, 1},
        {0, -1, 0}
    };
    int LCCW[3][3] = {
        {1, 0, 0},
        {0, 0, -1},
        {0, 1, 0}
    };

    int UCW[3][3] = {
        {0, 0, -1},
        {0, 1, 0},
        {1, 0, 0}
    };
    int UCCW[3][3] = {
        {0, 0, 1},
        {0, 1, 0},
        {-1, 0, 0}
    };

    int DCW[3][3] = {
        {0, 0, -1},
        {0, 1, 0},
        {1, 0, 0}
    };
    int DCCW[3][3] = {
        {0, 0, 1},
        {0, 1, 0},
        {-1, 0, 0}
    };

    int BCW[3][3] = {
        {0, 1, 0},
        {-1, 0, 0},
        {0, 0, 1}
    };
    int BCCW[3][3] = {
        {0, -1, 0},
        {1, 0, 0},
        {0, 0, -1}
    };
};

#endif