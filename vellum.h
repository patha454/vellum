#ifndef VELLUM_LIBRARY_H
#define VELLUM_LIBRARY_H

#include "ve_colour.h"
#include <uchar.h>

/** An unstyled text character. */
typedef char32_t ve_char_t;


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

#endif // VELLUM_LIBRARY_H
