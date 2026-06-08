/**
 * \file framebuffer.h
 *
 * \brief Vellum framebuffer API.
 *
 * \copyright 2026 H Paterson (Alicorn Software).
 * \license BSL-1.0
 */

#ifndef VELLUM_VE_FRAMEBUFFER_H
#define VELLUM_VE_FRAMEBUFFER_H

#include "vellum/cell.h"
#include <stddef.h>

/**
 * \brief Vellum framebuffer abstraction.
 *
 * Framebuffers contain cells of text characters and their
 * associated style attributes which will be rendered to a
 * terminal.
 *
 * Vellum framebuffers are polymorphic - members used by
 * any specific backend are hidden within their individual
 * implementation.
 *
 * \see veFramebufferCreate()
 * \see veFramebufferDestroy()
 * \see veFramebufferGetCell()
 */
struct VeFramebuffer {
    /**
     * Interface to an implementation of a framebuffer.
     */
    const struct VeFramebufferBackend* const backend;
};

/**
 * \brief Function signature for creating a framebuffer
 * implementation.
 *
 * Create a new framebuffer implementation by allocating
 * and initializing all required resources.
 *
 * \param backend Backend implementation to use for the
 * framebuffer.
 * \param width Width of the new framebuffer, in cells.
 * \param height Height of the new framebuffer, in cells.
 *
 * \note Creating a framebuffer with the width or height
 * set to zero is invalid and will return null.
 *
 *  \note This function is part of the abstract framebuffer
 * module interface. Consumers constructing framebuffers
 * should use \ref veFramebufferCreate to allocate a new
 * framebuffer.
 *
 * \return Newly allocated framebuffer, or null if
 * allocation failed.
 */
typedef struct VeFramebuffer* (*ve_framebuffer_create_t)(
    const struct VeFramebufferBackend* backend,
    size_t width, size_t height);

/**
 * \brief Function signature for destroying a framebuffer
 * implementation.
 *
 * Destroy a framebuffer implementation by freeing and
 * deallocating the resources it holds.
 *
 * \note This function is part of the abstract framebuffer
 * module interface. Consumers destroying framebuffers
 * should use \ref veFramebufferDestroy to destroy a
 * framebuffer.
 *
 * \param framebuffer Framebuffer to be deallocated. No
 * action is taken if the framebuffer is null.
 */
typedef void (*ve_framebuffer_destroy_t)(
    struct VeFramebuffer* framebuffer);

/**
 * \brief Function signature for accessing a cell of a
 * particular framebuffer implementation.
 *
 * Framebuffer implementations' cells are accessed via
 * zero-indexed coordinates, where the x-axis increases
 * from left to right and the y-axis increases from top to
 * bottom.
 *
 * \note The memory layout of cells within the framebuffer
 * is defined by the underlying backend implementation.
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

/**
 * \brief Implementation of a Vellum framebuffer.
 *
 * Virtual method table (vtable) providing the behaviour
 * for a specific framebuffer implementation. Users select
 * a framebuffer implementation with the instance passed to
 * \ref veFramebufferCreate().
 */
struct VeFramebufferBackend {
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

/**
 * \brief Interleaved, row-major (IRM) framebuffer
 * implementation.
 *
 * The IRM framebuffer stores cells in a single array. Each
 * array member contains the full style data and character
 * rendered in a cell.
 *
 * \note The IRM framebuffer is a relatively naive,
 * unoptimized implementation intended for use as a
 * benchmarking and behaviour-testing baseline.
 */
extern const struct VeFramebufferBackend
    VE_INTERLEAVED_ROW_MAJOR_FRAMEBUFFER;

/**
 * \brief Create a new framebuffer implementation by
 * allocating and initializing all required resources.
 *
 * \note Creating a framebuffer with the width or height
 * set to zero is invalid and will return null.
 *
 * \param backend Framebuffer implementation to use.
 * \param width Width of the new framebuffer, in cells.
 * \param height Height of the new framebuffer, in cells.
 *
 * \return Newly initialized framebuffer, or NULL on
 * failure.
 */
static inline struct VeFramebuffer* veFramebufferCreate(
    const struct VeFramebufferBackend* backend,
    const size_t width, const size_t height)
{
    if (backend == NULL || backend->create == NULL) {
        return NULL;
    }
    return backend->create(backend, width, height);
}

/**
 * \brief Destroy a framebuffer implementation by freeing
 * and deallocating all resources it holds.
 *
 * \note No action will be taken if the framebuffer is NULL.
 *
 * \param framebuffer Framebuffer to destroy.
 */
static inline void veFramebufferDestroy(
    struct VeFramebuffer* framebuffer)
{
    if (framebuffer == NULL || framebuffer->backend == NULL
        || framebuffer->backend->destroy == NULL) {
        return;
    }
    framebuffer->backend->destroy(framebuffer);
}

/**
 * \brief Access a single cell within a framebuffer.
 *
 * Framebuffer implementations' cells are accessed via
 * zero-indexed coordinates, where the x-axis increases
 * from left to right and the y-axis increases from top to
 * bottom.
 *
 * \param framebuffer Framebuffer to query.
 * \param x X coordinate of the cell.
 * \param y Y coordinate of the cell
 *
 * \return Cell at (x, y) in the framebuffer, or null if:
 *   - The coordinates are out of range.
 *   - The framebuffer is null or invalid.
 */
static inline struct VeCell* veFramebufferGetCell(
    const struct VeFramebuffer* framebuffer, size_t x,
    size_t y)
{
    if (framebuffer == NULL || framebuffer->backend == NULL
        || framebuffer->backend->get_cell == NULL) {
        return NULL;
    }
    return framebuffer->backend->get_cell(
        framebuffer, x, y);
}

#endif // VELLUM_VE_FRAMEBUFFER_H
