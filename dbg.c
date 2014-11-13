#include "dbg.h"

#include <stdarg.h>
#include <stdio.h>
#include "Win32Tools/Win32Tools.h"

FILE *_output = NULL;

void
_dbg (char *format, ...)
{
	#ifndef NO_COLOR
	console_set_col(0x02);
	#endif

	if (!_output)
		_output = stdout;

    va_list args;

    va_start (args, format);
        vfprintf (_output, format, args);
        fflush (_output);
    va_end (args);

	#ifndef NO_COLOR
	console_set_col(0x07);
	#endif
}

void
_fail (char *format, ...)
{
	#ifndef NO_COLOR
	console_set_col(0x0C);
	#endif

	if (!_output)
		_output = stdout;

    va_list args;

    va_start (args, format);
        vfprintf (_output, format, args);
        fflush (_output);
    va_end (args);

	#ifndef NO_COLOR
	console_set_col(0x07);
	#endif
}

void
dbg_set_output (FILE *output)
{
	_output = output;
}
