#include "auto/autoselector.hpp"

#include <atomic>
#include <cstdint>

#include "main.h"

namespace autoselector {

namespace {

// ---------------------------------------------------------------------------
// Button layout (brain screen is 480 x 240 pixels)
//
//   Row 1:  [Red Left] [Red Right] [Blue Left] [Blue Right]
//   Row 2:  [        Skills       ] [     Quick Skills     ]
//   Bottom: "Selected: ..." status text
// ---------------------------------------------------------------------------
struct Button {
  int x, y, w, h;
  const char* label;
  Routine routine;
  std::uint32_t color;  // 0xRRGGBB, used when selected / for the outline
};

constexpr int kMargin = 10;
constexpr int kRowH = 90;
constexpr int kRow1Y = 10;
constexpr int kRow2Y = kRow1Y + kRowH + kMargin;  // 110
constexpr int kSmallW = 107;                      // 4 buttons per row
constexpr int kWideW = 225;                       // 2 buttons per row
constexpr int kTextOffsetX = 50;  // pixels to shift labels left; raise if still too far right

constexpr std::uint32_t kRed = 0xCC2222;
constexpr std::uint32_t kBlue = 0x2255CC;
constexpr std::uint32_t kGreen = 0x22AA44;
constexpr std::uint32_t kOrange = 0xDD8800;
constexpr std::uint32_t kDarkGrey = 0x303030;
constexpr std::uint32_t kWhite = 0xFFFFFF;
constexpr std::uint32_t kBlack = 0x000000;

const Button kButtons[] = {
    {kMargin + 0 * (kSmallW + kMargin), kRow1Y, kSmallW, kRowH, "Red Left", Routine::red_left, kRed},
    {kMargin + 1 * (kSmallW + kMargin), kRow1Y, kSmallW, kRowH, "Red Right", Routine::red_right, kRed},
    {kMargin + 2 * (kSmallW + kMargin), kRow1Y, kSmallW, kRowH, "Blue Left", Routine::blue_left, kBlue},
    {kMargin + 3 * (kSmallW + kMargin), kRow1Y, kSmallW, kRowH, "Blue Right", Routine::blue_right, kBlue},
    {kMargin + 0 * (kWideW + kMargin), kRow2Y, kWideW, kRowH, "Skills", Routine::skills, kGreen},
    {kMargin + 1 * (kWideW + kMargin), kRow2Y, kWideW, kRowH, "Quick Skills", Routine::quick_skills, kOrange},
};
constexpr int kNumButtons = sizeof(kButtons) / sizeof(kButtons[0]);

// Routine selected at boot (before anyone touches the screen).
std::atomic<Routine> selected{Routine::red_left};

// ---------------------------------------------------------------------------
// Drawing
// ---------------------------------------------------------------------------
void draw() {
  pros::screen::set_eraser(kBlack);
  pros::screen::erase();

  const Routine current = selected.load();

  for (int i = 0; i < kNumButtons; i++) {
    const Button& b = kButtons[i];
    const bool isSelected = (b.routine == current);

    // Fill: bright team color if selected, dark grey otherwise
    pros::screen::set_pen(isSelected ? b.color : kDarkGrey);
    pros::screen::fill_rect(b.x, b.y, b.x + b.w, b.y + b.h);

    // Outline: white if selected, team color otherwise
    pros::screen::set_pen(isSelected ? kWhite : b.color);
    pros::screen::draw_rect(b.x, b.y, b.x + b.w, b.y + b.h);

    // Label (text is drawn over the eraser color, so match it to the fill)
    pros::screen::set_eraser(isSelected ? b.color : kDarkGrey);
    pros::screen::set_pen(kWhite);
    pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, b.x + b.w / 2 - kTextOffsetX, b.y + b.h / 2, "%s", b.label);
  }

  // Status line at the bottom
  pros::screen::set_eraser(kBlack);
  pros::screen::set_pen(kWhite);
  pros::screen::print(pros::E_TEXT_MEDIUM_CENTER, 240, 220, "Selected: %s", name(current));
}

// ---------------------------------------------------------------------------
// Touch handling
// ---------------------------------------------------------------------------
void handleTouch(int x, int y) {
  for (int i = 0; i < kNumButtons; i++) {
    const Button& b = kButtons[i];
    if (x >= b.x && x <= b.x + b.w && y >= b.y && y <= b.y + b.h) {
      if (selected.load() != b.routine) {
        selected.store(b.routine);
        draw();
      }
      return;
    }
  }
}

void touchTask() {
  bool wasPressed = false;
  while (true) {
    pros::screen_touch_status_s_t touch = pros::screen::touch_status();
    const bool isPressed = (touch.touch_status == pros::E_TOUCH_PRESSED);

    // Only react on the moment of a new press (not while the finger is held)
    if (isPressed && !wasPressed) {
      handleTouch(touch.x, touch.y);
    }
    wasPressed = isPressed;

    pros::delay(20);
  }
}

}  // namespace

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------
const char* name(Routine routine) {
  switch (routine) {
    case Routine::red_left:     return "Red Left";
    case Routine::red_right:    return "Red Right";
    case Routine::blue_left:    return "Blue Left";
    case Routine::blue_right:   return "Blue Right";
    case Routine::skills:       return "Skills";
    case Routine::quick_skills: return "Quick Skills";
  }
  return "Unknown";
}

Routine get() { return selected.load(); }

void init() {
  draw();
  static pros::Task task(touchTask, "autoselector");
}

}  