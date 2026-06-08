#ifndef VELLUM_VE_CANVAS_H
#define VELLUM_VE_CANVAS_H

#include "vellum/framebuffer.h"
#include <stdio.h>

/**
 * \brief Canvas for drawing TUI elements.
 */
struct VeCanvas {
    /** Buffer where the next frame is being written. */
    struct VeFramebuffer* backBuffer;

    /** Buffer containing the previous frame displayed. */
    struct VeFramebuffer* frontBuffer;

    /** Stream where the canvas will render. */
    FILE* output;
};

/**
 * \brief Allocate and initialize a new canvas for rendering
 * text output.
 *
 * The canvas is Vellum's primary interface. A canvas
 * receives text elements to be displayed on each frame (via
 * "stage" calls such as `veStageCharacter`) to generate
 * an optimized set of terminal escape sequences which will
 * render the frame to a stream such as the stdout.
 *
 * \param output Stream where the canvas will render.
 * \param width Width of the canvas, in characters.
 * \param height Height of the canvas, in characters.
 *
 * \return Newly allocated canvas, or NULL if allocation
 * or initialization fails.
 */
struct VeCanvas* veCreateCanvas(
    FILE* output, size_t width, size_t height);

/**
 * \brief Destroy a canvas, freeing all resources held by
 * the canvas.
 *
 * \param canvas Canvas to destroy. No action is taken if
 * the canvas is NULL.
 */
void veDestroyCanvas(struct VeCanvas* canvas);

/**
 * \brief Render staged content to the terminal.
 *
 * @param canvas Canvas to render.
 */
void veDisplayCanvas(const struct VeCanvas* canvas);

/**
 * \brief Stage a character for rendering on the canvas.
 *
 * Stage a character to be rendered to the canvas on the
 * `veDisplayCanvas` call.
 *
 * @param canvas Canvas where the character will be staged.
 * @param character Character to stage.
 * @param x X coordinate of the character.
 * @param y Y coordinate of the character.
 * @param style Style to apply to the character.
 */
void veStageCharacter(const struct VeCanvas* canvas,
    ve_char_t character, size_t x, size_t y,
    struct VeStyle style);

#endif // VELLUM_VE_CANVAS_H
