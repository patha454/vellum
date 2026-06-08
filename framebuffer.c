#include <stdbool.h>
#include <stdlib.h>

#include "ve_framebuffer.h"

struct VeDefaultFramebuffer {
    const struct VeFramebufferBackend* vtable;
    size_t width;
    size_t height;
    struct VeCell* cells;
};

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

struct VeFramebuffer* veCreateDefaultFramebuffer(
    const size_t width, const size_t height)
{
    if (isSizeUnsafe(width, height)) {
        return NULL;
    }
    struct VeDefaultFramebuffer* framebuffer
        = calloc(1, sizeof(struct VeDefaultFramebuffer));
    if (framebuffer == NULL) {
        return NULL;
    }
    struct VeCell* cells
        = calloc(width * height, sizeof(struct VeCell));
    if (cells == NULL) {
        free(framebuffer);
        return NULL;
    }
    framebuffer->vtable = &veDefaultFramebufferFunctions;
    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->cells = cells;
    return (struct VeFramebuffer*)framebuffer;
}

void veDestroyDefaultFramebuffer(struct VeFramebuffer* framebuffer)
{
    if (framebuffer == NULL) {
        return;
    }
    struct VeDefaultFramebuffer* fb
        = (struct VeDefaultFramebuffer*)framebuffer;
    fb->width = 0;
    fb->height = 0;
    if (fb->cells != NULL) {
        free(fb->cells);
        fb->cells = NULL;
    }
    free(framebuffer);
}

struct VeCell* veGetDefaultFramebufferCell(
    const struct VeFramebuffer* framebuffer, const size_t x,
    const size_t y)
{
    if (framebuffer == NULL) {
        return NULL;
    }
    struct VeDefaultFramebuffer* fb
        = (struct VeDefaultFramebuffer*)framebuffer;
    if (x >= fb->width || y >= fb->height) {
        return NULL;
    }
    return &fb->cells[y + x * fb->height];
}

const struct VeFramebufferBackend
    veDefaultFramebufferFunctions = {
        .create = veCreateDefaultFramebuffer,
        .destroy = veDestroyDefaultFramebuffer,
        .get_cell = veGetDefaultFramebufferCell,
    };
