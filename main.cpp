/* 
 * Author: Wesley Garey
 * Date: April 14, 2016
 */

#define TRACE

#include <cstdlib>
#include <memory>
#include <sstream>

#include "server.h"
#include "sim-time.h"
#include "simulator.h"
#include "system-stats.h"
#include "system.h"

#ifdef TRACE
#include "trace.h"
#include "call-producer.h"
#endif

using namespace std;
using namespace Project2;

/*
 * The entry point of the program.
 * @return The exit code.
 */
int main()
{
#ifdef TRACE
    Trace::OpenInst("trace.txt");
#endif
    
    double callsPerHour = 25;
    int servers = 3;
    double avgServTime = SimTime(0,6,0).GetSeconds();
    double stdDevServTime = SimTime(0,2,0).GetSeconds();
    
    shared_ptr<System> sys = make_shared<System>();
    
    for (int index = 0; index < servers; index++)
    {
        shared_ptr<NormRndGen> rnd = make_shared<NormRndGen>(avgServTime, stdDevServTime);
        shared_ptr<Server> server = make_shared<Server>((index + 1), sys.get(), rnd);
        
        sys->AddServer(server);
    }
    
    shared_ptr<ExpRndGen> rnd = make_shared<ExpRndGen>(3600, callsPerHour);
    
    CallProducer producer(rnd, sys);
    
    producer.Start(SimTime(0), SimTime(24,0,0));
    
    Simulator::Run(SimTime(0));
    
#ifdef TRACE
    
    stringstream ss;
    
    SystemStats stats = sys->GetStats();
    
    ss << stats;
    
    Trace::WriteLineToInst("");
    Trace::WriteLineToInst("Statistics: " + ss.str());
    
    Trace::CloseInst();
#endif
    
    return EXIT_SUCCESS;
}

