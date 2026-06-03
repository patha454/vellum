#ifndef VELLUM_VE_CELL_H
#define VELLUM_VE_CELL_H

#include "ve_char.h"
#include "ve_colour.h"

/**
 * Vellum representation of a single cell of console text.
 *
 * \see ve_char_t
 * \see ve_colour_t
 */
struct VeCell {
    /** Text character in the cell. */
    ve_char_t character;

    /** Foreground colour of the cell. */
    ve_colour_t foreground;

    /** Background colour of the cell. */
    ve_colour_t background;
};

#endif
