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
#include "system-stats.h"
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
    
   
    
    stringstream ss;
    
    Trace::WriteLineToInst(ss.str());
    
#ifdef TRACE
    Trace::CloseInst();
#endif
    
    return EXIT_SUCCESS;
}

