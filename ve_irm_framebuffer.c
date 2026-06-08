/**
 * \file ve_irm_framebuffer.c
 *
 * \brief Interleaved, row-major (IRM) framebuffer
 * implementation.
 *
 * The IRM framebuffer stores cells in a single array. Each
 * array member contains the full style data and character
 * rendered in a cell.
 *
 * The IRM framebuffer is a relatively naive, unoptimized
 * implementation intended for use as a benchmarking and
 * behaviour-testing baseline.
 */

#include <stdbool.h>
#include <stdlib.h>

#include "ve_framebuffer.h"

struct VeIRMFramebuffer {
    const struct VeFramebufferBackend* backend;
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

struct VeFramebuffer* veCreateIRMFramebuffer(
    const struct VeFramebufferBackend* backend,
    const size_t width, const size_t height)
{
    if (isSizeUnsafe(width, height)) {
        return NULL;
    }
    struct VeIRMFramebuffer* framebuffer
        = calloc(1, sizeof(struct VeIRMFramebuffer));
    if (framebuffer == NULL) {
        return NULL;
    }
    struct VeCell* cells
        = calloc(width * height, sizeof(struct VeCell));
    if (cells == NULL) {
        free(framebuffer);
        return NULL;
    }
    framebuffer->backend = backend;
    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->cells = cells;
    return (struct VeFramebuffer*)framebuffer;
}

void veDestroyIRMFramebuffer(
    struct VeFramebuffer* framebuffer)
{
    if (framebuffer == NULL) {
        return;
    }
    struct VeIRMFramebuffer* fb
        = (struct VeIRMFramebuffer*)framebuffer;
    fb->width = 0;
    fb->height = 0;
    if (fb->cells != NULL) {
        free(fb->cells);
        fb->cells = NULL;
    }
    free(framebuffer);
}

struct VeCell* veGetIRMFramebufferCell(
    const struct VeFramebuffer* framebuffer, const size_t x,
    const size_t y)
{
    if (framebuffer == NULL) {
        return NULL;
    }
    struct VeIRMFramebuffer* fb
        = (struct VeIRMFramebuffer*)framebuffer;
    if (x >= fb->width || y >= fb->height) {
        return NULL;
    }
    return &fb->cells[x + y * fb->width];
}

const struct VeFramebufferBackend
    VE_INTERLEAVED_ROW_MAJOR_FRAMEBUFFER = {
        .create = veCreateIRMFramebuffer,
        .destroy = veDestroyIRMFramebuffer,
        .get_cell = veGetIRMFramebufferCell,
    };
