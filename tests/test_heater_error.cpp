// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) 2026 trinler007
#include "components/truma_inetbox/heater_error.h"
#include <array>
#include <cassert>

using namespace esphome::truma_inetbox;

int main() {
  // User capture, 2026-11-05, CP Plus displaying W164H after mains loss.
  constexpr std::array<uint8_t, 41> frame = {
      0xBB,0x00,0x1F,0x00,0x1E,0x00,0x00,0x22,0xFF,0xFF,0xFF,0x54,0x01,0x14,
      0x33,0x00,0x7F,0xF0,0x0A,0x01,0x00,0x08,0x07,0x00,0x00,0x08,0x07,0x02,
      0x02,0xFA,0x0A,0x0A,0x0B,0x05,0xA4,0x02,0x00,0x00,0x00,0x00,0x00};
  static_assert(heater_error_legacy_number(frame[34], frame[35]) == 364);
  static_assert(heater_error_display_number(frame[34], frame[35]) == 164);
  assert(heater_error_display_number(0, 0) == 0);
  // Guard against introducing a global -200 offset, dropping high bytes, or
  // changing unverified byte pairs based on one observation.
  for (unsigned high = 0; high < 256; ++high) {
    for (unsigned low = 0; low < 256; ++low) {
      if (low == 0xA4 && high == 0x02)
        continue;
      assert(heater_error_display_number(low, high) == high * 100 + low);
    }
  }
}
