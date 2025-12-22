#include "charset/control_chars.h"

#include "charset/ugsm.h"

void ControlCharsInit() {
    UGSMloadGlyphSet((UGSMGlyphSet){ 0 }, 4);
}