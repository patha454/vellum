#ifndef VELLUM_VE_FRAMEBUFFER_H
#define VELLUM_VE_FRAMEBUFFER_H

#include "ve_cell.h"
#include <stddef.h>

/**
 * \brief Grid of "cells" which forms Vellum's framebuffer.
 *
 * Each cell in the framebuffer is a single character (or
 * empty space) in the terminal.
 *
 * \internal
 * Vellum stores cells column-major order. Vellum's
 * implementation is expected to move to Z-order as an
 * optimization once an initial implementation is complete.
 */
struct VeFramebuffer {
    /** Width of the framebuffer, in cells. */
    size_t width;

    /** Height of the framebuffer, in cells. */
    size_t height;

    /**
     * Framebuffer contents.
     *
     * The framebuffer is a 2-dimensional array of cells (
     * width * height cells total.)
     */
    struct VeCell * cells;
};

/**
 * \brief Access a framebuffer cell.
 *
 * Framebuffer cells are accessed via zero-indexed
 * coordinates, where the x-axis increases from left to
 * right and the y-axis increases from top to bottom.
 *
 * \note The memory layout of cells within the framebuffer
 * is defined in \ref VeFramebuffer.
 *
 * @param framebuffer Framebuffer to query.
 * @param x X coordinate of the cell.
 * @param y Y coordinate of the cell
 *
 * @return Cell at (x, y) in the framebuffer, or null if:
 *   - The coordinates are out of range.
 *   - The framebuffer is null or invalid.
 */
struct VeCell * veGetFramebufferCell(
    const struct VeFramebuffer * framebuffer,
    size_t x,
    size_t y
);

/**
 * \brief Allocate a new Vellum framebuffer.
 *
 * Performs a deep allocation of the framebuffer and its
 * underlying cell array.
 *
 * @param width Width of the new framebuffer, in cells.
 * @param height Height of the new framebuffer, in cells.
 *
 * @return Newly allocated framebuffer, or null if
 * allocation failed.
 */
struct VeFramebuffer * veAllocateFramebuffer(
    size_t width,
    size_t height
);

/**
 * \brief Deallocate a Vellum framebuffer.
 *
 * Performs a deep deallocation freeing both the
 * framebuffer and its underlying cell array.
 *
 * @param framebuffer Framebuffer to be deallocated. No
 * action is taken if the framebuffer is null.
 */
void veDeallocateFramebuffer(
    struct VeFramebuffer * framebuffer
);

#endif //VELLUM_VE_FRAMEBUFFER_H
