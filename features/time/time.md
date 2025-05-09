# C Time Functions Reference

## TIME.H Overview

The `time.h` header provides functionality for working with date and time in C programs.

### time_t

A long integer capable of representing the time and date of the system in an encoded implementation-specific internal format. This is referred to as the calendar time.

### Key Functions

#### time()

```c
time_t time(time_t *systime);
```

- Returns the encoded calendar time of the system or -1 if no system time is available
- Places the encoded form of time into the variable pointed to by systime
- If systime is null, the argument is ignored

#### localtime()

```c
struct tm *localtime(time_t *systime);
```

- Returns a pointer to the broken-down form of systime
- The structure is internally allocated by the compiler and will be overwritten by each subsequent call

### struct tm

The `struct tm` represents broken-down time with the following members:

```c
struct tm {
    int tm_sec;   // seconds, 0-61
    int tm_min;   // minutes, 0-59
    int tm_hour;  // hours, 0-23
    int tm_mday;  // day of the month, 1-31
    int tm_mon;   // months since January, 0-11
    int tm_year;  // years from 1900
    int tm_wday;  // days since Sunday, 0-6
    int tm_yday;  // days since January 1, 0-365
    int tm_isdst; // Daylight Saving Time indicator
};
```

- For `tm_isdst` (Daylight Saving Time indicator):
  - Positive value: Daylight Saving Time is in effect
  - Zero: Daylight Saving Time is not in effect
  - Negative value: No information available
