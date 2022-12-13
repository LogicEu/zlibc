#include <zctype.h>
#include <zstdlib.h>

int zatoi(const char* str)
{
    int n = 0, sign = 1;

    while (_isspace(*str)) { 
        ++str; 
    }

    if (*str == '+') {
        ++str;
    }
    else if (*str == '-') {
        sign = -1;
        ++str;
    }

    while (_isdigit(*str)) {
        n = n * 10 + *str++ - '0'; 
    }
    
    return n * sign;
}

long zatol(const char* str)
{
    long n = 0, sign = 1;

    while (_isspace(*str)) { 
        ++str; 
    }

    if (*str == '+') {
        ++str;
    }
    else if (*str == '-') {
        sign = -1;
        ++str;
    }

    while (_isdigit(*str)) {
        n = n * 10 + *str++ - '0'; 
    }
    
    return n * sign;
}

double zatof(const char* str) 
{
    int dot = 0;
    double n = 0.0, sign = 1.0, f;

    while (_isspace(*str)) { 
        ++str; 
    }

    if (*str == '+') {
        ++str;
    }
    else if (*str == '-') {
        sign = -1.0;
        ++str;
    }
    else if (*str == '.') {
        ++dot;
        ++str;
    } 

    while (_isdigit(*str)) {
        f = (double)(*str++ - '0');
        if (!dot) {
            n = n * 10.0 + f;
            if (*str == '.') {
                ++dot;
                ++str;
            }
        }
        else {
            dot *= 10;
            n += f / (double)dot;
        }
    }

    return n * sign;
}

