#include <stdint.h>
#include <stdbool.h>
#include <malloc.h>

#if defined(_MSC_VER)
    //  Microsoft
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#else
    //  do nothing and hope for the best?
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#ifdef __cplusplus
extern "C" {
#endif
    EXPORT uint8_t* BayerRg8ToRgb(uint16_t width, uint16_t height, uint8_t* data, bool flipped);
    EXPORT void FreeRgbMemory(uint8_t* data);
#ifdef __cplusplus
} // extern "C"
#endif
