/**
 * \file canvas.h
 *
 * \brief Vellum style API.
 *
 * \copyright 2026 H Paterson (Alicorn Software).
 * \license BSL-1.0
 */

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
