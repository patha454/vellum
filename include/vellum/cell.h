#ifndef VELLUM_VE_CELL_H
#define VELLUM_VE_CELL_H

#include "vellum/char.h"
#include "vellum/style.h"

/**
 * \brief Vellum representation of a single cell of console
 * text.
 */
struct VeCell {
    /** Text character in the cell. */
    ve_char_t character;

    /** Appearance of the character in the cell. */
    struct VeStyle style;
};

#endif
