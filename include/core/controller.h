#ifndef _CONTROLLER_H
#define _CONTROLLER_H

#include "core/types.h"

typedef struct UsbController {
    struct UsbController* next;

    void* hc;

    void (*poll)(struct UsbController* controller);
} UsbController;

extern UsbController* g_usbControllerList;

#endif