#ifndef VELLUM_VE_FRAMEBUFFER_H
#define VELLUM_VE_FRAMEBUFFER_H

#include <stddef.h>

#include "ve_cell.h"

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
    struct VeCell* cells;
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
 * \param framebuffer Framebuffer to query.
 * \param x X coordinate of the cell.
 * \param y Y coordinate of the cell
 *
 * \return Cell at (x, y) in the framebuffer, or null if:
 *   - The coordinates are out of range.
 *   - The framebuffer is null or invalid.
 */
struct VeCell* veGetFramebufferCell(
    const struct VeFramebuffer* framebuffer, size_t x,
    size_t y);

/**
 * \brief Allocate and initialize a new Vellum framebuffer.
 *
 * Create a mew framebuffer by allocating and initializing
 * all required resources.
 *
 * \param width Width of the new framebuffer, in cells.
 * \param height Height of the new framebuffer, in cells.
 *
 * \note Creating a framebuffer with the width or height
 * set to zero is invalid and will return null.
 *
 * \return Newly allocated framebuffer, or null if
 * allocation failed.
 */
struct VeFramebuffer* veCreateFramebuffer(
    size_t width, size_t height);

/**
 * \brief Destroy and deallocated a Vellum framebuffer.
 *
 * Destroy a framebuffer by freeing and deallocating the
 * resources it holds.
 *
 * \param framebuffer Framebuffer to be deallocated. No
 * action is taken if the framebuffer is null.
 */
void veDestroyFramebuffer(
    struct VeFramebuffer* framebuffer);

#endif // VELLUM_VE_FRAMEBUFFER_H
