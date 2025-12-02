#ifndef _BCD_H
#define _BCD_H

#include "core/types.h"

uint32 toBCD(uint32 num);

uint32 fromBCD(uint32 num);

Hour hourToBCD(Hour hour);

Hour hourFromBCD(Hour hour);

#endif