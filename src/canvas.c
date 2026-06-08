#include "vellum/canvas.h"

#include <stdlib.h>

struct VeCanvas* veCreateCanvas(
    FILE* output, const size_t width, const size_t height)
{
    if (height == 0 || width == 0) {
        return NULL;
    }
    struct VeCanvas* canvas
        = calloc(1, sizeof(struct VeCanvas));
    if (canvas == NULL) {
        return NULL;
    }
    canvas->backBuffer = veFramebufferCreate(
        &VE_INTERLEAVED_ROW_MAJOR_FRAMEBUFFER, width,
        height);
    if (canvas->backBuffer == NULL) {
        veDestroyCanvas(canvas);
        return NULL;
    }
    canvas->frontBuffer = veFramebufferCreate(
        &VE_INTERLEAVED_ROW_MAJOR_FRAMEBUFFER, width,
        height);
    if (canvas->frontBuffer == NULL) {
        veDestroyCanvas(canvas);
        return NULL;
    }
    canvas->output = output;
    return canvas;
}

void veDestroyCanvas(struct VeCanvas* canvas)
{
    if (canvas == NULL) {
        return;
    }
    if (canvas->frontBuffer != NULL) {
        veFramebufferDestroy(canvas->frontBuffer);
        canvas->frontBuffer = NULL;
    }
    if (canvas->backBuffer != NULL) {
        veFramebufferDestroy(canvas->backBuffer);
        canvas->backBuffer = NULL;
    }
    free(canvas);
}

void veStageCharacter(const struct VeCanvas* canvas,
    const ve_char_t character, const size_t x,
    const size_t y, const struct VeStyle style)
{
    if (canvas == NULL) {
        return;
    }
    struct VeCell* cell
        = veFramebufferGetCell(canvas->backBuffer, x, y);
    if (cell == NULL) {
        return;
    }
    cell->character = character;
    cell->style = style;
}

void veDisplayCanvas(const struct VeCanvas* canvas)
{
    // TODO: Implement `veDisplayCanvas
    if (canvas == NULL) {
        return;
    }
}