#ifndef PROFILING_H
#define PROFILING_H

#ifdef TRACY_ENABLE

#include <tracy/Tracy.hpp>

#else

#define ZoneScoped
#define ZoneScopedN(name)
#define FrameMark
#define TracyAlloc(ptr, size)
#define TracyFree(ptr)

#endif

inline void set_profiler_thread_name(const char* name) {
#ifdef TRACY_ENABLE
    tracy::SetThreadName(name);
#else
    (void)name;
#endif
}

#endif