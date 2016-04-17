/* 
 * Author: Wesley Garey
 * Date: April 14, 2016
 */

#define TRACE

#include <cstdlib>
#include <memory>
#include <sstream>

#include "call-action.h"
#include "event.h"
#include "sim-time.h"
#include "simulator.h"

#ifdef TRACE
#include "trace.h"
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
    
    SimTime stopTime;
    
    shared_ptr<Action> act(new CallAction());
    
    Event event(1, SimTime(10), act);
    
    Simulator::Schedule(event);
    
    Simulator::Run(stopTime);
    
#ifdef TRACE
    Trace::CloseInst();
#endif
    
    return EXIT_SUCCESS;
}

