#ifndef HAS_DATATYPE_H
#define HAS_DATATYPE_H

#ifndef _LINUX_
#ifndef __cplusplus
#define bool	int
#define false	0
#define true	1
#endif /* __cplusplus */
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
#else
#include <stdint.h>
#include <stdbool.h>
#endif /* _LINUX_ */
#endif /* HAS_DATATYPE_H */
