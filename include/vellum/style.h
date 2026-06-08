#ifndef VELLUM_VE_STYLE_H
#define VELLUM_VE_STYLE_H

#include "vellum/colour.h"

/**
 * \breuf Rules dictating cells' (characters') appearance.
 */
struct VeStyle {
    /** Foreground colour of the styled cells. */
    ve_colour_t foreground;

    /** Background colour of the styled cells. */
    ve_colour_t background;
};

#endif // VELLUM_VE_STYLE_H
