#ifndef _RANDOM_OS_INFO_H
#define _RANDOM_OS_INFO_H

#define INFO_FIRST INFO_OK

#define INFO_LAST INFO_ERROR

typedef enum Info {
	INFO_UNKNOWN,
	INFO_OK,
	INFO_ERROR,
} Info;

#endif