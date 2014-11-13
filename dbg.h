#pragma once

// ---------- Includes ------------
#include <stdio.h>

// ---------- Defines -------------
#define TOSTRING(x) # x

#define __DBG_ACTIVATED__ TRUE

#if __DBG_ACTIVATED__ == TRUE
	#ifdef __DEBUG_OBJECT__
		#define dbg(format, ...) 	\
			_dbg(__DEBUG_OBJECT__ ":%d| " format "\n", __LINE__, ##__VA_ARGS__)
	#else
		#define dbg(format, ...) 	\
			_dbg("%s:%d| " format "\n", ((strrchr(__FILE__, '\\')) != NULL) ? &(strrchr(__FILE__, '\\'))[1] : __FILE__, __LINE__, ##__VA_ARGS__)
	#endif

	#ifdef __DEBUG_OBJECT__
		#define fail(format, ...) 	\
			_fail(__DEBUG_OBJECT__ ":%d| " format "\n", __LINE__, ##__VA_ARGS__)
	#else
		#define fail(format, ...) 	\
			_fail("%s:%d| " format "\n", ((strrchr(__FILE__, '\\')) != NULL) ? &(strrchr(__FILE__, '\\'))[1] : __FILE__, __LINE__, ##__VA_ARGS__)
	#endif
#else
	#define dbg(format, ...)
	#define fail(format, ...)
#endif

void _dbg  (char *format, ...);
void _fail (char *format, ...);
void dbg_set_output (FILE *output);

// ----------- Methods ------------
