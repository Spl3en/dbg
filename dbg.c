/** * @license <license placeholder> */// ---------- Includes ------------#include "dbg.h"#include <stdarg.h>#include <stdio.h>#include <string.h>#include <ctype.h>// ------ Structure declaration -------// ------ Static declaration -------// ------ Extern function implementation ------int windows = 1;int enableDebug = 1;void dbg_enableDebug (int enable) {    enableDebug = enable;}int dbg_isEnabled (void) {    return enableDebug;} void dbg_setWindows (int isWindows) {    windows = isWindows; }void _dbg (    int level,    FILE *output,    const char *format,    ...) {    if (!enableDebug) return;    va_list args;    if (windows) {        switch (level) {            // Windows            case DBG_LEVEL_INFO:        SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 0x0A); break;            case DBG_LEVEL_DEBUG:       break;            case DBG_LEVEL_WARNING:     SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 0x0E); break;            case DBG_LEVEL_ERROR:       SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 0x0C); break;            case DBG_LEVEL_IMPORTANT:   SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 0x0C); break;            case DBG_LEVEL_SPECIAL:     SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 0x0D); break;        }    } else {        switch (level) {            // Linux            case DBG_LEVEL_INFO:      fprintf (output, "\x1b[32m"); break;            case DBG_LEVEL_DEBUG:     fprintf (output, "\x1b[37m"); break;            case DBG_LEVEL_WARNING:   fprintf (output, "\x1b[1;33m"); break;            case DBG_LEVEL_ERROR:     fprintf (output, "\x1b[1;31m"); break;            case DBG_LEVEL_IMPORTANT: fprintf (output, "\x1b[1;31m"); break;            case DBG_LEVEL_SPECIAL:   fprintf (output, "\x1b[1;34m"); break;        }    }    va_start (args, format);        vfprintf (output, format, args);    va_end (args);    if (windows) {        // Windows        SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), 0x07);    } else {        fprintf (output, "\033[0;0m");    }        fflush (output);}/** * @brief Dump a buffer in the standard output * @param buffer An allocated buffer to dump * @param bufferSize The buffer size * @param prefix A string printed before each line of the dump * @return */void_buffer_print (    void *buffer,    int bufferSize,    const char *prefix,    const char *filename,    int lineNumber,    const char *functionName) {    if (!enableDebug) return;    int curPos = 0;    printf ("[%s:%d in %s] %s ===== buffer size = %d (0x%x) ================\n",        filename, lineNumber, functionName, prefix, bufferSize, bufferSize);    while (curPos < bufferSize) {        int offset;        printf ("[%s:%d in %s] %s", filename, lineNumber, functionName, prefix);        for (offset = 0; offset < 16 && curPos < bufferSize; offset++, curPos++) {            printf (" %02X", ((unsigned char *) buffer)[curPos]);        }        if (offset != 16) {            int j;            for (j = 0; j < 16 - offset; j++) {                printf("   ");            }        }        printf (" | ");        curPos -= offset;        for (offset = 0; offset < 16 && curPos < bufferSize; offset++, curPos++) {            unsigned char c = ((unsigned char *) buffer)[curPos];            printf ("%c", isprint(c) ? c : '.');        }        printf("\n");    }    printf ("[%s:%d in %s] %s ===============================================\n",        filename, lineNumber, functionName, prefix);}