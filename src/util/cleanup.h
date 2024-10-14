#ifndef CSYNTH_CLEANUP_H
#define CSYNTH_CLEANUP_H

#include "../core/func.h"
#include "../event/event.h"
#include "../func/gen/sine.h"
#include "../io/file.h"
#include "../ui/display.h"

/**
 * @brief Cleanup allocations and resources.
 */
void cleanup_all(void)
{
    event_free();
    display_free();
    func_free();
#ifdef ALLOC_TRACE
    if (!alloc_list_is_empty())
    {
        log_error("Memory leak detected");
        alloc_list_dump();
        alloc_list_clear();
    }
#endif
#ifdef FILE_TRACE
    if (!file_list_is_empty())
    {
        log_error("Open file detected");
        file_list_dump();
        file_list_clear();
    }
#endif
}

#endif // CSYNTH_CLEANUP_H
