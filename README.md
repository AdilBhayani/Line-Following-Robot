# TODO

> "Excellence is a continuous process and not an accident" - *A. P. J. Abdul Kalam*

## Analogue Circuits

* Light Sensor Circuits
    * ~~Sensor Arrangement~~
        * ~~Very important to make an efficiently moving robot~~
        * ~~Need to consider ease of processing and accuracy/precision~~
        * Decided on using the Straight Line Sensor Arrangment
    * Analogue processing of signals
        * ~~Pure SMT vs THM or Mixture?~~ **Pure SMT**
        * Do we convert to Digital? or keep as Analogue?
        * What reference values do we use?
        * What sort of circuit do we use?
        * Use internal opamps/comparators of PSoC?
        * If converting, how to set reference?

* Quadrature Encoder/Decoder
    * Used to detect rotation of axis
    * Need to get working to figure out speed of robot
    * Need it to calculate distance travelled
    * Necessary so that we can damp the oscillations of the robot

* DIP Switches to control mode and On/Off switch

## Digital Coding Stuff

* MatLab Algorithms (Adil)
    * Pathfinding Stuff
        * DFS Search - Done in matlab
        * BFS Search
        * Greedy Best-First
        * Dijkstra's Algorithm
        * A* Algorithm
    * Need to implement possibly multiple algorithms to best achieve the goals
    * Integrate in PSoC
    * Intelligent way to figure out which algorithm to use for which situation

* Motion Control Code (ALMOST DONE)
    * ~~Need to fine tune the parameters~~
    * Possibly use an FSM or two to do this
    * ~~Will control the H Bridge~~
    * ~~Use PWM to achieve necessary speeds~~
    * ~~Should be modular and easy to interface with~~
    * ~~Should never allow circuits to go past physical limits~~

* RF Communication
    * ~~Receive data~~
    * Recieve binary data stream and extract struct
    * Handle data to perform some useful function

* Bluetooth Communication (WHEN ARE THEY GIVING US THIS MODULE????)
    * Used for debugging purposes
    * Bidirectional connection

* ADC to read Voltage/Current Levels of the battery
    * Shouldn't be too hard, but for some reason its a deliverable

* Software / Hardware Integration