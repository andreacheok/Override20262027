#pragma once

/**
 * Usage:
 *   - call autoselector::init() once in initialize()
 *   - call autoselector::get() inside autonomous() to see what was picked
 */
namespace autoselector {

enum class Routine {
  red_left,
  red_right,
  blue_left,
  blue_right,
  skills,
  quick_skills,
};

/** Draws the selector and starts the touch-handling task. Call from initialize(). */
void init();

Routine get();

const char* name(Routine routine);

}  