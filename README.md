# TODO

> "Excellence is a continuous process and not an accident" - *A. P. J. Abdul Kalam*

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
        * void robot_full_turn();
    * Use 'system_state' to access RF data
    * Sample map and food list in pacman.c

* Bluetooth Communication (వైష్ణవి)
    * Please test and fix btGetString & btGetInt
    * Feel free to start from scratch

* Motion Control Code (Alexandra)
    * Grid size is in pixels and is approximately 4 pixels per cm
    * You can't recall the init functions all the time
    * Please try to bring an innovative solution
    * Also you can't just go and set the quad values to your liking, because other stuff is relying on that being consistent