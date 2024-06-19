//
// cleanup.h - Cleanup allocations
//
#ifndef CSYNTH_CLEANUP_H
#define CSYNTH_CLEANUP_H

#include "../core/func.h"
#include "../event/event.h"
#include "../ui/display.h"

void cleanup_all()
{
    event_clear();
    display_clear();
    func_free();
}

#endif // CSYNTH_CLEANUP_H
