# TODO

> "Excellence is a continuous process and not an accident" - *A. P. J. Abdul Kalam*

* Assembly of both PCBs (சகாயன்)

* Pacman Algorithms (आदिल)
    * Calculate the shortest path initially then start moving in that path
    * We will assume that we are timed from when robot starts moving, not start-up
    * Ignore sensor readings for Pacman
        * Just go off the motion control functions finishing (based on quadrature readings)
        * and the RF data for now
    * Fill in functions in pacman.c
    * Add any additional helper functions to pacman.c
    * Please use only the following functions for motion control:
        * void robot_forward(uint8 value);
        * void robot_backward(uint8 value);
        * void robot_right_turn();
        * void robot_left_turn();
        * Note: These functions will only return once the movement has been finished.
    * Use 'system_state' to access RF data
    * Sample map and food list in pacman.h

* Bluetooth Communication (వైష్ణవి)
    * Function definitions to abstract two way communication over Bluetooth have been added
    * Please complete the functions to enable this
    * Treat as if this is just a normal UART port (BT_UART)

* Motion Control Code (Alexandra)
    * Complete the four new functions mentioned above
    * Use quadrature readings to ensure both turns are exactly 90 and travelled distance is a multiple of grid units
    * Some calibration will be required
    * (Don't really know grid size, just make a good guess and keep it flexible (ie. maybe some #define ??))