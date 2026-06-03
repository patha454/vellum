#ifndef VELLUM_VE_COLOUR_H
#define VELLUM_VE_COLOUR_H

#include <stdint.h>

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

#endif //VELLUM_VE_COLOUR_H
