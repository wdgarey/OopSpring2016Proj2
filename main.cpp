/* 
 * Author: Wesley Garey
 * Date: April 14, 2016
 */

#define TRACE

#include <cstdlib>
#include <memory>
#include <sstream>

#include "call.h"
#include "call-producer.h"
#include "delete-me.h"
#include "event.h"
#include "exp-rnd-gen.h"
#include "norm-rnd-gen.h"
#include "sim-stats.h"
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
    
    shared_ptr<Taker> taker = make_shared<Taker>();
    taker->stats = make_shared<SimStats>();
    
    shared_ptr<ExpRndGen> rnd = make_shared<ExpRndGen>(60, 25);
    
    CallProducer producer(rnd, taker);
    
    producer.Start(SimTime(5), SimTime(60));
    
    Simulator::Run(SimTime());
    
    stringstream ss;
    
    ss << *(taker->stats);
    
    Trace::WriteLineToInst(ss.str());
    
#ifdef TRACE
    Trace::CloseInst();
#endif
    
    return EXIT_SUCCESS;
}

