#pragma once

// ---------- Includes ------------
#include <stdio.h>
#include "Utils/Utils.h"

// ---------- Defines -------------
#define __DBG_ACTIVATED__ TRUE

#if __DBG_ACTIVATED__ == TRUE
	#ifdef __DEBUG_OBJECT__
		#define dbg(format, ...) 	\
			_dbg("[" __DEBUG_OBJECT__ "] " format "\n", ##__VA_ARGS__)
	#else
		#define dbg(format, ...) 	\
			_dbg("[%s] " format "\n", ((strrchr(__FILE__, '\\')) != NULL) ? &(strrchr(__FILE__, '\\'))[1] : __FILE__, ##__VA_ARGS__)
	#endif

	#ifdef __DEBUG_OBJECT__
		#define fail(format, ...) 	\
			_fail("[FAIL] [" __DEBUG_OBJECT__ "] " format "\n", ##__VA_ARGS__)
	#else
		#define fail(format, ...) 	\
			_fail("[FAIL] [%s] " format "\n", ((strrchr(__FILE__, '\\')) != NULL) ? &(strrchr(__FILE__, '\\'))[1] : __FILE__, ##__VA_ARGS__)
	#endif

	#ifdef __DEBUG_OBJECT__
		#define warn(format, ...) 	\
			_warn("[" __DEBUG_OBJECT__ "] " format "\n", ##__VA_ARGS__)
	#else
		#define warn(format, ...) 	\
			_warn("[%s] " format "\n", ((strrchr(__FILE__, '\\')) != NULL) ? &(strrchr(__FILE__, '\\'))[1] : __FILE__, ##__VA_ARGS__)
	#endif
#else
	#define dbg(format, ...)
	#define fail(format, ...)
	#define warn(format, ...)
#endif

void _dbg  (char *format, ...);
void _fail (char *format, ...);
void _warn (char *format, ...);

void dbg_set_output (FILE *output);

// ----------- Methods ------------
