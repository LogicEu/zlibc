#include <zstdlib.h>
#include <zstring.h>
#include <zmath.h>

int zitoa(int num, char* buf, const int base)
{
    int i = 0, neg = 0;
    if (!num) {
        buf[i++] = '0';
        buf[i] = 0;
        return i;
    }
 
    if (num < 0 && base == 10) {
        ++neg;
        num = -num;
    }
 
    while (num) {
        int rem = num % base;
        buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    if (neg) {
        buf[i++] = '-';
    }
 
    buf[i] = 0;
    zstrnrev(buf, i);
    return i;
}

int zltoa(long num, char* buf, const int base)
{
    int i = 0, neg = 0;
    if (!num) {
        buf[i++] = '0';
        buf[i] = 0;
        return i;
    }
 
    if (num < 0 && base == 10) {
        ++neg;
        num = -num;
    }
 
    while (num) {
        int rem = num % base;
        buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    if (neg) {
        buf[i++] = '-';
    }
 
    buf[i] = 0;
    zstrnrev(buf, i);
    return i;
}

int zlltoa(long long num, char* buf, const int base)
{
    int i = 0, neg = 0;
    if (!num) {
        buf[i++] = '0';
        buf[i] = 0;
        return i;
    }
 
    if (num < 0 && base == 10) {
        ++neg;
        num = -num;
    }
 
    while (num) {
        int rem = num % base;
        buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    if (neg) {
        buf[i++] = '-';
    }
 
    buf[i] = 0;
    zstrnrev(buf, i);
    return i;
}

int zutoa(unsigned int num, char* buf, const int base)
{
    int i = 0;
    if (!num) {
        buf[i++] = '0';
        buf[i] = 0;
        return i;
    }
 
    while (num) {
        int rem = num % base;
        buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    buf[i] = 0;
    zstrnrev(buf, i);
    return i;
}

int zultoa(unsigned long num, char* buf, const int base)
{
    int i = 0;
    if (!num) {
        buf[i++] = '0';
        buf[i] = 0;
        return i;
    }
 
    while (num) {
        int rem = num % base;
        buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    buf[i] = 0;
    zstrnrev(buf, i);
    return i;
}

int zulltoa(unsigned long long num, char* buf, const int base)
{
    int i = 0;
    if (!num) {
        buf[i++] = '0';
        buf[i] = 0;
        return i;
    }
 
    while (num) {
        int rem = num % base;
        buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    buf[i] = 0;
    zstrnrev(buf, i);
    return i;
}

int zztoa(size_t num, char* buf, const int base)
{
    int i = 0;
    if (!num) {
        buf[i++] = '0';
        buf[i] = 0;
        return i;
    }
 
    while (num) {
        int rem = num % base;
        buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / base;
    }
 
    buf[i] = 0;
    zstrnrev(buf, i);
    return i;
}

int zftoa(double f, char *buf, int precision)
{
    char c;
	int i = 0;
	long intPart;

	if (precision > 10) {
		precision = 10;
    }
    else if (precision < 0) {
        double n = 100000.0;
        for (precision = 0; f < n && precision < 7; ++precision) {
            n /= 10.0;
        }
	}

	if (f < 0.0) {
		f = -f;
		buf[i++] = '-';
	}

    f += 0.5 / zpow(10, precision);
	intPart = (long)f;
	f -= (double)intPart;

	if (intPart) {
		while (intPart) {
			buf[i++] = '0' + intPart % 10;
			intPart /= 10;
		}
        buf[i] = 0;
        zstrnrev(buf + (*buf == '-'), i - (*buf == '-'));
	}
    else buf[i++] = '0';

	if (precision) {
		buf[i++] = '.';
		while (precision--) {
			f *= 10.0;
			c = (char)f;
			buf[i++] = '0' + c;
			f -= (float)c;
		}
	}

	buf[i] = 0;
	return i;
}
