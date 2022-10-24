#ifndef Z_CTYPE_H
#define Z_CTYPE_H

#define _isbetween(c, min, max) (((c) >= (min)) && ((c) <= (max)))
#define _isascii(c) ((c) >= 0)
#define _isspace(c) ((c) == ' ')
#define _isdigit(c) _isbetween(c, '0', '9')
#define _isalpha(c) (_isbetween(c, 'A', 'Z') || _isbetween(c, 'a', 'z'))
#define _isalnum(c) (_isdigit(c) || _isalpha(c))
#define _iscntrl(c) (_isbetween(c, 0, 31) || ((c) == 127))
#define _isgraph(c) _isbetween(c, 33, 126)
#define _isprint(c) _isbetween(c, 32, 126)
#define _islower(c) _isbetween(c, 'a', 'z')
#define _isupper(c) _isbetween(c, 'A', 'Z')
#define _ispunct(c) (_isgraph(c) && !_isalnum(c))
#define _isxdigit(c) (_isdigit(c) || _isbetween(c, 'A', 'F') || _isbetween(c, 'a', 'f'))
#define _toascii(c) ((c) & 0x7f)
#define _tolower(c) ((c) + 32)
#define _toupper(c) ((c) - 32)

int isalnum(int c);
int isalpha(int c);
int isascii(int c);
int iscntrl(int c);
int isdigit(int c);
int isgraph(int c);
int islower(int c);
int isprint(int c);
int ispunct(int c);
int isspace(int c);
int isupper(int c);
int isxdigit(int c);
int toascii(int c);
int tolower(int c);
int toupper(int c);

#endif /* Z_CTYPE_H*/