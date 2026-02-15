#ifndef _RANDOM_OS_BUFFER_FWD_H
#define _RANDOM_OS_BUFFER_FWD_H

typedef enum Buffer_FlagsSeek {
	BUFFER_FLAG_SEEK_BEGIN,
	BUFFER_FLAG_SEEK_POS,
	BUFFER_FLAG_SEEK_END,
} Buffer_FlagsSeek;

typedef enum Buffer_CreationFlags {
	BUFFER_CREATION_STATIC = 	0b00000001,
	BUFFER_CREATION_NO_SEEK = 	0b00000010,
} Buffer_CreationFlags;

typedef struct Buffer Buffer;

#endif