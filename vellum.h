#ifndef VELLUM_LIBRARY_H
#define VELLUM_LIBRARY_H

#include <stdint.h>
#include <uchar.h>

/** An unstyled text character. */
typedef char32_t ve_char_t;

/**
 * Vellum's colour representation.
 *
 * \internal
 * Colours are stored as a 24-bit RGB value, 8 bits per
 * channel in R-G-B order. The high 8 bits are unused.
 *
 * \see veColour()
 */
typedef uint32_t ve_colour_t;


/**
 * Represents a colour using RGB values.
 *
 * \param red Red intensity, 0-255.
 * \param green Green intensity, 0-255.
 * \param blue Blue intensity, 0-255.
 *
 * \return Initialized Vellum colour.
 */
static inline ve_colour_t veColour(
    const uint8_t red,
    const uint8_t green,
    const uint8_t blue
) { return (red << 16) | (green << 8) | blue; }


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
