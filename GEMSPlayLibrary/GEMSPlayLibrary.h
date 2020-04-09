#pragma once

#ifdef GEMSPLAYLIBRARY_EXPORTS
#define GEMSPLAYLIBRARY_API __declspec(dllexport)
#else
#ifdef GEMSPLAY_NO_LIBRARY
#define GEMSPLAYLIBRARY_API
#else
#define GEMSPLAYLIBRARY_API __declspec(dllimport)
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

GEMSPLAYLIBRARY_API int gemsplay_init(
	const unsigned char* PatPtr, const unsigned char* EnvPtr,
	const unsigned char* SeqPtr, const unsigned char* SmpPtr);

GEMSPLAYLIBRARY_API void gemsplay_cleanup(void);

GEMSPLAYLIBRARY_API void gemsplay_stop(void);

GEMSPLAYLIBRARY_API void gemsplay_pause(void);

GEMSPLAYLIBRARY_API void gemsplay_play(void);

GEMSPLAYLIBRARY_API void gemsplay_set_gems28mode(int enabled);

#ifdef __cplusplus
}
#endif