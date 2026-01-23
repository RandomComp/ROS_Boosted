#include "charset/control_chars.h"

#include "graphics/font/font.h"

void ControlCharsLoad() {
    UGSMloadGlyphSet((Font){ 0 }, 4);
}