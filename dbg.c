/**
 * @license GNU GENERAL PUBLIC LICENSE - Version 2, June 1991
 *          See LICENSE file for further information
 */

// ---------- Includes ------------
#include "dbg.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

// ------ Structure declaration -------
FILE *_output = NULL;
int dbgTabulations = -1;

// ------ Static declaration -------

// ------ Extern function implementation ------

void dbgSetCustomOutput(char *filename) {

    // Special case : stdout
    if (strcmp(filename, "stdout") == 0) {
        dbgSetOutput(stdout);
        return;
    }

    FILE *out = fopen(filename, "ab+");
    if (!out) {
        error("Cannot open filename '%s'", filename);
        return;
    }

    dbgSetOutput(out);
}

void dbgSetOutput(FILE *output) {
    _output = output;
}

void dbgClose(void) {
    if (_output && _output != stdout && _output != stderr) {
        fclose(_output);
    }

    _output = stdout;
}

void _dbg(int level, char *format, ...) {
    va_list args;

    if (_output == NULL) {
        _output = stdout;
    }

    for (int i = 0; i < dbgTabulations; i++) {
        fprintf(_output, "  ");
    }

    switch (level) {
        #if defined(WIN32) || defined(__CYGWIN__)
        case DBG_LEVEL_INFO:    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0x0A); break;
        case DBG_LEVEL_DEBUG: break;
        case DBG_LEVEL_WARNING: SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0x0E); break;
        case DBG_LEVEL_ERROR:   SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0x0C); break;
        case DBG_LEVEL_SPECIAL: SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0x0B); break;
        #else
        case DBG_LEVEL_INFO: fprintf(_output, "\x1b[32m"); break;
        case DBG_LEVEL_DEBUG: fprintf(_output, "\x1b[37m"); break;
        case DBG_LEVEL_WARNING: fprintf(_output, "\x1b[33m"); break;
        case DBG_LEVEL_ERROR: fprintf(_output, "\x1b[31m"); break;
        case DBG_LEVEL_SPECIAL: fprintf(_output, "\x1b[35m"); break;
        #endif
    }

    va_start(args, format);
        vfprintf(_output, format, args);
    va_end(args);

    #if defined(WIN32) || defined(__CYGWIN__)
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE), 0x07);
    #else
    fprintf(_output, "\033[0m");
    #endif

    fflush(_output);
}

void
_bufferPrint(void *buffer, int bufferSize, char *prefix) {

    int curPos = 0;

    if (_output == NULL) {
        _output = stdout;
    }

    fprintf(_output, "%s ===== buffer size = %d (0x%x) ================\n", prefix, bufferSize, bufferSize);

    while (curPos < bufferSize) {
        int offset;
        fprintf(_output, "%s", prefix);
        for (offset = 0; offset < 16 && curPos < bufferSize; offset++, curPos++) {
            fprintf(_output, " %02X", ((uint8_t *) buffer)[curPos]);
        }
        if (offset != 16) {
            for (int j = 0; j < 16 - offset; j++) {
                fprintf(_output, "   ");
            }
        }

        fprintf(_output, " | ");
        curPos -= offset;

        for (offset = 0; offset < 16 && curPos < bufferSize; offset++, curPos++) {
            uint8_t c = ((uint8_t *) buffer)[curPos];
            fprintf(_output, "%c", isprint(c) ? c : '.');
        }

        fprintf(_output, "\n");
    }
    fprintf(_output, "%s=================================================\n", prefix);
    fflush(_output);
}


/* Crash handlers */
#if defined(WIN32) || defined(__CYGWIN__)
LONG WINAPI crashHandler(EXCEPTION_POINTERS *ExceptionInfo) {
    #ifdef __x86_64__
    die("Application crashed at %p. Exception code = %x",
         ExceptionInfo->ContextRecord->Rip, ExceptionInfo->ExceptionRecord->ExceptionCode);
    #else
    die("Application crashed at %p. Exception code = %x",
         ExceptionInfo->ContextRecord->Eip, ExceptionInfo->ExceptionRecord->ExceptionCode);
    #endif

    return EXCEPTION_EXECUTE_HANDLER;
}

#else
void printTrace(void) {
    void *array[20];
    size_t size;
    char **strings;

    size = backtrace(array, sizeof(array) / sizeof(*(array)));
    strings = backtrace_symbols(array, size);

    error("Obtained %zd stack frames.", size);

    for (size_t i = 0; i < size; i++) {
        error("Frame %d : %s", i, strings[i]);
    }

    error("==================================");

    free(strings);
}

void crashHandler(int sig, siginfo_t *siginfo, void *_context) {
    int exceptionCode = siginfo->si_errno;
    ucontext_t *context = (ucontext_t*) _context;
#if __x86_64__
    uintptr_t ip = context->uc_mcontext.gregs[REG_RIP];
#else
    uintptr_t ip = context->uc_mcontext.gregs[REG_EIP];
#endif    

    // Avoid unused variables warning
    (void) ip;
    (void) exceptionCode;

    if (sig == SIGABRT) {
        printTrace();
    }

    die("Application crashed at %p. Exception code = %x", ip, exceptionCode);
}
#endif
