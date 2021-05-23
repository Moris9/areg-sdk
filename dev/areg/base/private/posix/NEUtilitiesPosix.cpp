/************************************************************************
 * \file        areg/base/private/NEUtilitiesPosix.cpp
 * \ingroup     AREG SDK, Asynchronous Event Generator Software Development Kit
 * \author      Artak Avetyan (mailto:artak@aregtech.com)
 * \brief       AREG POSIX specific hidden utility methods.
 *
 ************************************************************************/

#include "areg/base/NEUtilities.hpp"

#ifdef  _POSIX

#include "areg/base/String.hpp"
#include "areg/base/NEMemory.hpp"
#include "areg/base/GEMacros.h"
#include <time.h>
#include <unistd.h>

namespace NEUtilities {

#if 0
    void _generateName( const char * prefix, char * out_buffer, int length, const char * specChar )
    {
        static const char * formatStr = "%s%03d%s%03d%s%03d%s%03d%s%03d%s%03d%s%03d%s%03d";
        if ( out_buffer != NULL )
        {
            const char * spec = specChar != NULL ? specChar : NEUtilities::DEFAULT_SPECIAL_CHAR;
            *out_buffer = '\0';
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            struct tm now = *localtime(&ts.tv_sec);

            int milli =  ts.tv_nsec / 1000000;
            int micro = (ts.tv_nsec / 1000) - (milli * 1000);

            int tick1 = static_cast<int>(micro);
            int tick2 = static_cast<int>(milli);
            int tick3 = static_cast<int>(now.tm_sec);
            int tick4 = static_cast<int>(now.tm_min);
            int tick5 = static_cast<int>(now.tm_hour);
            int tick6 = static_cast<int>(now.tm_mday);
            int tick7 = static_cast<int>(now.tm_mon + 1);
            int tick8 = static_cast<int>(now.tm_year + 1900);

            String::formatString( out_buffer, length, formatStr,
                prefix != NULL ? prefix : NEUtilities::DEFAULT_GENERATED_NAME,
                tick8, spec, tick7, spec, tick6, spec, tick5, spec, tick4, spec, tick3, spec, tick2, spec, tick1 );
        }
    }

#else

    void _generateName( const char * prefix, char * out_buffer, int length, const char * specChar )
    {
        static const char * strFormat = "%s%s%08x%s%08x";
        if ( out_buffer != NULL )
        {
            const char * spec = specChar != NULL ? specChar : NEUtilities::DEFAULT_SPECIAL_CHAR;
            *out_buffer = '\0';
            struct timespec now;
            clock_gettime(CLOCK_REALTIME, &now);
            String::formatString( out_buffer, length, strFormat, prefix != NULL ? prefix : NEUtilities::DEFAULT_GENERATED_NAME, spec, now.tv_sec, spec, now.tv_nsec);
        }
    }

#endif

    static inline void _convertMicrosecs(const TIME64 & quad, time_t & outSecs, unsigned short &outMilli, unsigned short &outMicro)
    {
        time_t secs = static_cast<time_t>(quad / SEC_TO_MICROSECS);
        time_t rest = static_cast<time_t>(quad % SEC_TO_MICROSECS);
        outSecs     = secs;
        outMilli    = static_cast<unsigned short>(rest / MILLISEC_TO_MICROSECS);
        outMicro    = static_cast<unsigned short>(rest % MILLISEC_TO_MICROSECS);

    }
}

AREG_API bool NEUtilities::convToLocalTime( const TIME64 & inUtcTime, sSystemTime & outLocalTime )
{
    bool result = false;

    // time_t secs = static_cast<time_t>(inUtcTime / SEC_TO_MICROSECS);
    // time_t rest = inUtcTime - (secs * SEC_TO_MICROSECS);
    // unsigned short milli = static_cast<unsigned short>(rest / MILLISEC_TO_MICROSECS);
    // unsigned short micro = static_cast<unsigned short>(rest - (milli * MILLISEC_TO_MICROSECS));

    time_t secs;
    unsigned short milli, micro;
    _convertMicrosecs(inUtcTime, secs, milli, micro);

    struct tm * conv = localtime(&secs);
    if (conv != NULL)
    {
        outLocalTime.stYear      = conv->tm_year + 1900;
        outLocalTime.stMonth     = conv->tm_mon  + 1;
        outLocalTime.stDay       = conv->tm_mday;
        outLocalTime.stHour      = conv->tm_hour;
        outLocalTime.stMinute    = conv->tm_min;
        outLocalTime.stSecond    = conv->tm_sec;
        outLocalTime.stDayOfWeek = conv->tm_wday;
        outLocalTime.stMillisecs = milli;
        outLocalTime.stMicrosecs = micro;

        result = true;
    }

    return result;
}

AREG_API bool NEUtilities::convToLocalTime( const sSystemTime &inUtcTime, sSystemTime & outLocalTime )
{
    bool result = false;
    TIME64 quad = NEUtilities::convToTime(inUtcTime);

    // time_t secs = static_cast<time_t>(quad / SEC_TO_MICROSECS);
    // time_t rest = quad - (secs * SEC_TO_MICROSECS);
    // unsigned short milli = static_cast<unsigned short>(rest / MILLISEC_TO_MICROSECS);
    // unsigned short micro = static_cast<unsigned short>(rest - (milli * MILLISEC_TO_MICROSECS));

    time_t secs;
    unsigned short milli, micro;
    _convertMicrosecs(quad, secs, milli, micro);

    struct tm * conv = localtime(&secs);
    if (conv != NULL)
    {
        outLocalTime.stYear      = conv->tm_year + 1900;
        outLocalTime.stMonth     = conv->tm_mon  + 1;
        outLocalTime.stDay       = conv->tm_mday;
        outLocalTime.stHour      = conv->tm_hour;
        outLocalTime.stMinute    = conv->tm_min;
        outLocalTime.stSecond    = conv->tm_sec;
        outLocalTime.stDayOfWeek = conv->tm_wday;
        outLocalTime.stMillisecs = milli;
        outLocalTime.stMicrosecs = micro;

        result = true;
    }

    return result;
}

AREG_API uint64_t NEUtilities::getTickCount( void )
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);

    TIME64 result = (ts.tv_sec * SEC_TO_MILLISECS) + ts.tv_nsec / MILLISEC_TO_NS;
    return result;
}

AREG_API void NEUtilities::systemTimeNow( NEUtilities::sSystemTime & out_sysTime, bool localTime )
{
    struct timespec ts;
    struct tm now;

    clock_gettime(CLOCK_REALTIME, &ts);
    if (localTime)
    {
        ::localtime_r(&ts.tv_sec, &now);
    }
    else
    {
        ::gmtime_r(&ts.tv_sec, &now);
    }

    // unsigned short milli = static_cast<unsigned short>(ts.tv_nsec / MILLISEC_TO_NS);
    // unsigned short micro = static_cast<unsigned short>((ts.tv_nsec - (milli * MILLISEC_TO_MICROSECS)) / MICROSEC_TO_NS);

    unsigned short milli = static_cast<unsigned short>((ts.tv_nsec / MILLISEC_TO_NS));
    unsigned short micro = static_cast<unsigned short>((ts.tv_nsec % MILLISEC_TO_NS) / MICROSEC_TO_NS);

    out_sysTime.stYear      = now.tm_year + 1900;
    out_sysTime.stMonth     = now.tm_mon  + 1;
    out_sysTime.stDayOfWeek = now.tm_wday;
    out_sysTime.stDay       = now.tm_mday;
    out_sysTime.stHour      = now.tm_hour;
    out_sysTime.stMinute    = now.tm_min;
    out_sysTime.stSecond    = now.tm_sec;
    out_sysTime.stMillisecs = milli;
    out_sysTime.stMicrosecs = micro;
}

AREG_API void NEUtilities::systemTimeNow( NEUtilities::sFileTime & out_fileTime, bool localTime )
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    if (localTime)
    {
        struct tm now;
        ::localtime_r(&ts.tv_sec, &now);
        time_t local = ::mktime(&now);
        TIME64 quad = static_cast<TIME64>(local * SEC_TO_MICROSECS) + static_cast<TIME64>(ts.tv_nsec / MICROSEC_TO_NS);
        out_fileTime.ftLowDateTime  = MACRO_64_LO_BYTE32(quad);
        out_fileTime.ftHighDateTime = MACRO_64_HI_BYTE32(quad);
    }
    else
    {
        TIME64 quad = static_cast<TIME64>(ts.tv_sec * SEC_TO_MICROSECS) + static_cast<TIME64>(ts.tv_nsec / MICROSEC_TO_NS);
        out_fileTime.ftLowDateTime  = MACRO_64_LO_BYTE32(quad);
        out_fileTime.ftHighDateTime = MACRO_64_HI_BYTE32(quad);
    }
}

AREG_API TIME64 NEUtilities::systemTimeNow( void )
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    TIME64 quad = ts.tv_sec * SEC_TO_MICROSECS + ts.tv_nsec / MICROSEC_TO_NS;
    return quad;
}

AREG_API TIME64 NEUtilities::convToTime( const NEUtilities::sSystemTime & sysTime )
{
    TIME64 quad = 0;

    struct tm sys;
    sys.tm_year     = sysTime.stYear    - 1900;
    sys.tm_mon      = sysTime.stMonth   - 1;
    sys.tm_mday     = sysTime.stDay;
    sys.tm_hour     = sysTime.stHour;
    sys.tm_min      = sysTime.stMinute;
    sys.tm_sec      = sysTime.stSecond;
    sys.tm_wday     = sysTime.stDayOfWeek;
    sys.tm_isdst    = 0;

    time_t secs = mktime(&sys);
    if (secs != static_cast<time_t>(-1))
    {
        quad = (secs * SEC_TO_MICROSECS) + (sysTime.stMillisecs * MILLISEC_TO_MICROSECS) + sysTime.stMicrosecs;
    }

    return quad;
}

AREG_API void NEUtilities::convToSystemTime( const TIME64 &  timeValue, NEUtilities::sSystemTime & out_sysTime )
{
    NEMemory::zeroBuffer(&out_sysTime, sizeof(NEUtilities::sSystemTime));

    // time_t secs = static_cast<time_t>(timeValue / SEC_TO_MICROSECS);
    // time_t rest = timeValue - (secs * SEC_TO_MICROSECS);
    // unsigned short milli = static_cast<unsigned short>(rest / MILLISEC_TO_MICROSECS);
    // unsigned short micro = static_cast<unsigned short>(rest - (milli * MILLISEC_TO_MICROSECS));

    time_t secs;
    unsigned short milli, micro;
    _convertMicrosecs(timeValue, secs, milli, micro);

    struct tm * conv = gmtime(&secs);
    if (conv != NULL)
    {
        out_sysTime.stYear      = conv->tm_year + 1900;
        out_sysTime.stMonth     = conv->tm_mon  + 1;
        out_sysTime.stDay       = conv->tm_mday;
        out_sysTime.stHour      = conv->tm_hour;
        out_sysTime.stMinute    = conv->tm_min;
        out_sysTime.stSecond    = conv->tm_sec;
        out_sysTime.stDayOfWeek = conv->tm_wday;
        out_sysTime.stMillisecs = milli;
        out_sysTime.stMicrosecs = micro;
    }
}

AREG_API void NEUtilities::convToSystemTime( const NEUtilities::sFileTime & fileTime, NEUtilities::sSystemTime & out_sysTime )
{
    TIME64 quad = MACRO_MAKE_64(fileTime.ftHighDateTime, fileTime.ftLowDateTime);
    NEUtilities::convToSystemTime(quad, out_sysTime);
}

AREG_API void NEUtilities::convToFileTime( const NEUtilities::sSystemTime & sysTime, NEUtilities::sFileTime & out_fileTime )
{
    TIME64 quad = NEUtilities::convToTime(sysTime);
    out_fileTime.ftLowDateTime = MACRO_64_LO_BYTE32(quad);
    out_fileTime.ftHighDateTime= MACRO_64_HI_BYTE32(quad);
}


#endif // _POSIX
