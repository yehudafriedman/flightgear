#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<unordered_map>
#include<queue>
#include "Server.h"
#include <thread>
#include <mutex>

#define GENERIC_SMALL 36

using namespace std;

class DataSimulator
{
    
    DataSimulator(int port, int samples_seccend);

    static DataSimulator* dataSimulator;
    unordered_map<string,string>simulator_table;
    void initInSimulatorTable();

   string key[GENERIC_SMALL] = {"/instrumentation/airspeed-indicator/indicated-speed-kt",
                                "/sim/time/warp",
                                "/controls/switches/magnetos",
                                "/instrumentation/heading-indicator/indicated-heading-deg",
                                "/instrumentation/altimeter/indicated-altitude-ft",
                                "/instrumentation/altimeter/pressure-alt-ft",
                                "/instrumentation/attitude-indicator/indicated-pitch-deg",
                                "/instrumentation/attitude-indicator/indicated-roll-deg",
                                "/instrumentation/attitude-indicator/internal-pitch-deg",
                                "/instrumentation/attitude-indicator/internal-roll-deg",
                                "/instrumentation/encoder/indicated-altitude-ft",
                                "/instrumentation/encoder/pressure-alt-ft",
                                "/instrumentation/gps/indicated-altitude-ft",
                                "/instrumentation/gps/indicated-ground-speed-kt",
                                "/instrumentation/gps/indicated-vertical-speed",
                                "/instrumentation/heading-indicator/indicated-heading-deg",
                                "/instrumentation/magnetic-compass/indicated-heading-deg",
                                "/instrumentation/slip-skid-ball/indicated-slip-skid",
                                "/instrumentation/turn-indicator/indicated-turn-rate",
                                "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
                                "/controls/flight/aileron",
                                "/controls/flight/elevator",
                                "controls/flight/rudder",
                                "/controls/flight/flaps",
                                "/controls/engines/engine/throttle",
                                "/controls/engines/current-engine/throttle",
                                "/controls/switches/master-avionics",
                                "/controls/switches/starter",
                                "/engines/active-engine/auto-start",
                                "/controls/flight/speedbrake",
                                "/sim/model/c172p/brake-parking",
                                "/controls/engines/engine/primer",
                                "/controls/engines/current-engine/mixture",
                                "/controls/switches/master-bat",
                                "/controls/switches/master-alt",
                                "/engines/engine/rpm"
                            };
   
    queue<string> q;
    void fiilQueueVal();
    void insertSimulatorTable();
    void updataSimulatorTable();

    
    public:
        ~DataSimulator();
        unordered_map<string,string> get_simulator_table();
        string return_value_by_key(string key);
        Server* server;
        static DataSimulator* getInstance(int port, int samples_seccend);
        thread t1;
        mutex m;
        


};