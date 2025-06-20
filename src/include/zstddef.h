#ifndef Z_STDDEF_H
#define Z_STDDEF_H

#ifndef __ZSIZE_T
    #define __ZSIZE_T
    #define __ZSIZE_TYPE__ __SIZE_TYPE__
    typedef __ZSIZE_TYPE__ size_t;
#endif /* SIZE */

#ifndef __ZPTRDIFF_T
    #define __ZPTRDIFF_T
    #define __ZPTRDIFF_TYPE__ __PTRDIFF_TYPE__
    typedef __ZPTRDIFF_TYPE__ ptrdiff_t;
#endif /* PTRDIFF_T */

#ifndef __ZWCHAR_T
    #define __ZWCHAR_T
    #define __ZWCHAR_TYPE__ __WCHAR_TYPE__
    typedef __ZWCHAR_TYPE__ wchar_t;
#endif /* WCHAR */

#ifndef __ZNULL
    #define __ZNULL
    #define ZNULL ((void*)0)
    #ifndef NULL
        #define NULL ZNULL
    #endif
#endif /* NULL */

#define offsetof(s, m) ((size_t)&(((s*)0)->m))

#endif /* Z_STDDEF_H */
