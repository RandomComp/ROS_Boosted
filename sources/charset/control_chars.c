#include "charset/control_chars.h"

#include "charset/font.h"

void ControlCharsLoad() {
    UGSMloadGlyphSet((Font){ 0 }, 4);
}