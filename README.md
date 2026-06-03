# Vellum

**A high-performance terminal rasterization and diffing engine.**

Vellum is not a CLI framework. It is not a UI toolkit or a widget library. Vellum is an engine dedicated to solving one
problem: *How can we update the terminal screen with the least ANSI escape sequence overhead and CPU usage possible?*

By optimizing the delta between frames, Vellum enables developers to implement complex, high-performance terminal
animations and TUI components with near-zero overhead.

## Key Features

- *Efficient*: Focused on two primary goals: minimizing the byte-count sent to stdout and minimizing the CPU cycles
required to calculate those changes.
- *Portable*: Written in modern, portable C17 with zero external dependencies beyond the standard C library.
- *Zero-cost*: No hidden memory allocations, no opaque state management, and no mandatory event loops.

## Project Philosophy

- *No input handling*: Vellum is not concerned with keyboard or mouse input; it manages output only.
- *No layout engine*: Managing spatial logic and element positioning is the responsibility of the consumer. Vellum only
 renders what it is explicitly told to.
- *No widgets*: There are no buttons, textboxes, or complex UI elements: only primitive primitives such as text, lines,
and boxes.
