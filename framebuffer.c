#include <stdbool.h>
#include <stdlib.h>

#include "ve_framebuffer.h"

/**
 * Check if a framebuffer size will cause memory errors.
 *
 * A framebuffer size is considered unsafe if:
 * - Either the width or height are zero.
 * - The width and height (and struct VeCell size) would
 * cause integer overflow.
 *
 * \param width Proposed framebuffer width, in cells.
 * \param height Proposed framebuffer height, in cells.
 * \return True if the proposed framebuffer size is unsafe
 * to use, false otherwise.
 */
static bool isSizeUnsafe(
    const size_t width, const size_t height)
{
    if (width == 0 || height == 0) {
        return true;
    }
    if (width > SIZE_MAX / height) {
        // width * height overflows size_t
        return true;
    }
    const size_t cellCount = width * height;
    if (cellCount > SIZE_MAX / sizeof(struct VeCell)) {
        // width * height * cellCount overflows size_t
        return true;
    }
    return false;
}

struct VeFramebuffer* veCreateFramebuffer(
    const size_t width, const size_t height)
{
    if (isSizeUnsafe(width, height)) {
        return NULL;
    }
    struct VeFramebuffer* framebuffer
        = malloc(sizeof(struct VeFramebuffer));
    if (framebuffer == NULL) {
        return NULL;
    }
    struct VeCell* cells
        = calloc(width * height, sizeof(struct VeCell));
    if (cells == NULL) {
        free(framebuffer);
        return NULL;
    }
    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->cells = cells;
    return framebuffer;
}

void veDestroyFramebuffer(struct VeFramebuffer* framebuffer)
{
    if (framebuffer == NULL) {
        return;
    }
    framebuffer->width = 0;
    framebuffer->height = 0;
    if (framebuffer->cells != NULL) {
        free(framebuffer->cells);
        framebuffer->cells = NULL;
    }
    free(framebuffer);
}

struct VeCell* veGetFramebufferCell(
    const struct VeFramebuffer* framebuffer, const size_t x,
    const size_t y)
{
    if (framebuffer == NULL) {
        return NULL;
    }
    if (x >= framebuffer->width
        || y >= framebuffer->height) {
        return NULL;
    }
    return &framebuffer->cells[y + x * framebuffer->height];
}
