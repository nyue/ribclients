/*  -*- C -*- */
/*
  Visual Information Insight copyright notice stub
 */

#ifndef VII_LOGGER
#define VII_LOGGER

#include <stdio.h>
#include <time.h>

#ifndef NDEBUG /* Debug build */

typedef enum { FATAL, ERROR, WARNING, INFO } LogLevel;

static char time_str[256];

inline static void SwitchConsole2File(const char* filename)
{
    freopen(filename,"w",stderr);
}

inline static char* now()
{
 time_t rawtime;
 struct tm *tm;
 time(&rawtime);
 tm = localtime(&rawtime);

 sprintf(time_str,"%4d/%02d/%02d %02d:%02d:%02d%c",
	 tm->tm_year + 1900,
	 tm->tm_mon,
	 tm->tm_mday,
	 tm->tm_hour,
	 tm->tm_min,
	 tm->tm_sec,
	 (tm->tm_isdst) > 0 ? '+' : ' ' );
 return time_str;

}

inline static const char* LogLevel2Str(LogLevel level)
{
    switch (level)
    {
    case FATAL:
        return "Fatal";
    case ERROR:
        return "Error";
    case WARNING:
        return "Warning";
    case INFO:
        return "Info";
    default:
        return "Unknown log level";
    }
}

#define VII_LOG(LOG_LEVEL, LOG_MESSAGE)                           \
    fprintf(stderr,"%s|%s|%s\n", LogLevel2Str(LOG_LEVEL), now(),#LOG_MESSAGE);

#else /* Debug build */

#define VII_LOG(LOG_LEVEL, LOG_MESSAGE) /* void (nothing) */

#endif /* Debug build */

#endif /* VII_LOGGER */

