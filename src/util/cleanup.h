#ifndef CSYNTH_CLEANUP_H
#define CSYNTH_CLEANUP_H

#include "../core/func.h"
#include "../event/event.h"
#include "../func/gen/sine.h"
#include "../ui/display.h"

/**
 * @brief Cleanup allocations and resources.
 */
void cleanup_all(void)
{
    event_free();
    display_free();
    func_free();
}

#endif // CSYNTH_CLEANUP_H
