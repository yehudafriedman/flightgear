#include "testdatasimulator.h"
using namespace std;



DataSimulator* DataSimulator::dataSimulator = NULL;
DataSimulator::DataSimulator(int port, int samples_second)
{
    initInSimulatorTable();
    server = new Server(port,samples_second);
    server->connecting();

     t1 = thread(&DataSimulator::updataSimulatorTable,this);
}
DataSimulator::~DataSimulator()
{
    t1.join();
}

DataSimulator* DataSimulator::getInstance(int port, int samples_second)
{
	if (dataSimulator == NULL) {
		dataSimulator = new DataSimulator(port, samples_second);
	}
	return dataSimulator;
}

void DataSimulator::initInSimulatorTable()
{
     for(int i=-0; i<GENERIC_SMALL; i++)
     {
         simulator_table[key[i]]="0";
     }
      
}

//A function that queues the values ​​to maintain their order
void DataSimulator::fiilQueueVal()
{
    string value = "";
    for(int i=0; i < server->size_buff ;i++)
    {
        
        if(server->buffer[i] !=',' && server->buffer[i] != '\n'  )
        {
            value += server->buffer[i];
        }
        else
        {
            q.push(value);
            value = "";
            if (q.size()==36)
            {
               insertSimulatorTable(); 
            }
        }
        
        
    }
}

//A function that fills the simulator data from the queue
void DataSimulator::insertSimulatorTable()
{
    for(int i=0; i<GENERIC_SMALL; i++)
    {
        m.lock();
        simulator_table[key[i]] = q.front();
        m.unlock();
        q.pop();
    }
}

//Function for managing the samples (enters the queue and if there are 36 values ​​in the queue it passes to the simulator and waits a tenth of a second
void DataSimulator::updataSimulatorTable()
{
    while(true)
    {
        server->reader();
        fiilQueueVal();
        usleep((server->samples_second));
    }

}

unordered_map<string,string> DataSimulator::get_simulator_table()
{
    return simulator_table;
}

string DataSimulator::return_value_by_key(string key)
{
    string value;
    m.lock();
    value = simulator_table[key];
    m.unlock();
    return value;
}




