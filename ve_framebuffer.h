
#ifndef VELLUM_VE_FRAMEBUFFER_H
#define VELLUM_VE_FRAMEBUFFER_H

#include "ve_cell.h"
#include <stddef.h>

struct VeFramebuffer {
    /**
     * Interface to an implementation of a framebuffer.
     */
    const struct VeFramebufferFunctions* const vtable;
};

/**
 * \brief Allocate and initialize a new Vellum framebuffer.
 *
 * Create a mew framebuffer implementation by allocating
 * and initializing all required resources.
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
typedef struct VeFramebuffer* (*ve_framebuffer_create_t)(
    size_t width, size_t height);

/**
 * \brief Destroy and deallocated a Vellum framebuffer.
 *
 * Destroy a framebuffer implementation by freeing and
 * deallocating the resources it holds.
 *
 * \param framebuffer Framebuffer to be deallocated. No
 * action is taken if the framebuffer is null.
 */
typedef void (*ve_framebuffer_destroy_t)(
    struct VeFramebuffer* framebuffer);

/**
 * \brief Access a framebuffer cell.
 *
 * Framebuffer implementations' cells are accessed via
 * zero-indexed coordinates, where the x-axis increases
 * from left to right and the y-axis increases from top to
 * bottom.
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
typedef struct VeCell* (*ve_framebuffer_get_cell_t)(
    const struct VeFramebuffer* framebuffer, size_t x,
    size_t y);

struct VeFramebufferFunctions {
    /**
     * Create a new instance of a framebuffer
     * implementation.
     */
    ve_framebuffer_create_t create;

    /**
     * Destroy a disused instance of a framebuffer
     * implementation.
     */
    ve_framebuffer_destroy_t destroy;

    /**
     * Access details of a single cell in a framebuffer
     * implementation.
     */
    ve_framebuffer_get_cell_t get_cell;
};

extern const struct VeFramebufferFunctions
    veDefaultFramebufferFunctions;

#endif // VELLUM_VE_FRAMEBUFFER_H
