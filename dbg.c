#include "dbg.h"

#include <stdarg.h>
#include <stdio.h>
#include "Console/Console.h"

FILE *_output = NULL;

void
_dbg (char *format, ...)
{
	#ifndef NO_COLOR
	#ifdef CONSOLE_COLOR
	console_set_col(0x02);
	#endif
	#endif

	if (!_output)
		_output = stdout;

    va_list args;

    va_start (args, format);
        vfprintf (_output, format, args);
        fflush (_output);
    va_end (args);

	#ifndef NO_COLOR
	#ifdef CONSOLE_COLOR
	console_set_col(0x07);
	#endif
	#endif
}

void
_fail (char *format, ...)
{
	#ifndef NO_COLOR
	#ifdef CONSOLE_COLOR
	console_set_col(0x0C);
	#endif
	#endif

	if (!_output)
		_output = stdout;

    va_list args;

    va_start (args, format);
        vfprintf (_output, format, args);
        fflush (_output);
    va_end (args);

	#ifndef NO_COLOR
	#ifdef CONSOLE_COLOR
	console_set_col(0x07);
	#endif
	#endif
}

void
_warn (char *format, ...)
{
	#ifndef NO_COLOR
	#ifdef CONSOLE_COLOR
	console_set_col(0x0E);
	#endif
	#endif

	if (!_output)
		_output = stdout;

    va_list args;

    va_start (args, format);
        vfprintf (_output, format, args);
        fflush (_output);
    va_end (args);

	#ifndef NO_COLOR
	#ifdef CONSOLE_COLOR
	console_set_col(0x07);
	#endif
	#endif
}

void
dbg_set_output (FILE *output)
{
	_output = output;
}
