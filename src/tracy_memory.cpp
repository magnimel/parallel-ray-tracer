#include <profiling.hpp>

#ifdef TRACY_ENABLE

#include <new>
#include <cstdlib>

void* operator new(std::size_t count) {
    void* ptr = std::malloc(count);
    if (!ptr) throw std::bad_alloc();

    TracyAlloc(ptr, count);
    return ptr;
}

void operator delete(void* ptr) noexcept {
    TracyFree(ptr);
    std::free(ptr);
}

void operator delete(void* ptr, std::size_t) noexcept {
    TracyFree(ptr);
    std::free(ptr);
}

void* operator new[](std::size_t count) {
    void* ptr = std::malloc(count);
    if (!ptr) throw std::bad_alloc();

    TracyAlloc(ptr, count);
    return ptr;
}

void operator delete[](void* ptr) noexcept {
    TracyFree(ptr);
    std::free(ptr);
}

void operator delete[](void* ptr, std::size_t) noexcept {
    TracyFree(ptr);
    std::free(ptr);
}

#endif