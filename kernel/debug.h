#ifndef DEBUG_H
#define DEBUG_H

//#ifdef _SYSTEM
//#define DEBUG_PRINT(params, level) do { if (verboseboot >= (level)) printf params; } while (0)

//#define DEBUGBASIC(params) DEBUG_PRINT(params, VERBOSEBOOT_BASIC)
//#define DEBUGEXTRA(params) DEBUG_PRINT(params, VERBOSEBOOT_EXTRA)
//#define DEBUGMAX(params)   DEBUG_PRINT(params, VERBOSEBOOT_MAX)
//#endif



//#define BUILD_BUG_ON_TRUE(e) typedef char BUG[-!!(e)] BUILD_BUG
//#define BUILD_BUG_ON_FALSE(e)
//#define BUILD_BUG_ON_NULL(e) ((void *)sizeof(struct { int:-!!(e); }))


#define BUILD_BUG(true,mess) _Static_assert(true,mess)
_Static_assert(1, "Static assertions not available");


#ifdef DEBUG
#define RUN_BUG(true,mess) ( true ?{ kputs(mess); __builtin_trap() })
#else
#define RUN_BUG(true,mess)
#endif // DEBUG



#ifdef DEBUG
#define assert(e) ( e ? __builtin_trap() )
#else
#define assert(e)
#endif // DEBUG

// void __builtin_unreachable() indicates that the code should never reach that point
// int   __builtin_LINE()
// const char* __builtin_FILE()
// const char* __builtin_FUNCTION()

#endif /* DEBUG_H */
