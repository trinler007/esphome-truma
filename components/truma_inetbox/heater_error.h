// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) 2026 trinler007
// Added 2026-11-05: CP Plus display mapping verified against a Combi D6E capture.
#pragma once

#include <cstdint>
#include <cstdio>
#include <string>

namespace esphome {
namespace truma_inetbox {

// Do not treat the second byte as decimal hundreds for verified display codes.
// Its general meaning is not established. In particular, do not infer W/E for
// other codes from this single capture, or truncate every code to eight bits.
constexpr bool heater_error_is_w164h(uint8_t low, uint8_t high) { return low == 0xA4 && high == 0x02; }

constexpr uint16_t heater_error_legacy_number(uint8_t low, uint8_t high) { return high * 100U + low; }

constexpr uint16_t heater_error_display_number(uint8_t low, uint8_t high) {
  return heater_error_is_w164h(low, high) ? 164U : heater_error_legacy_number(low, high);
}

inline std::string heater_error_display_text(uint8_t low, uint8_t high) {
  if (low == 0 && high == 0)
    return "None";
  if (heater_error_is_w164h(low, high))
    return "W164H";
  char text[40];
  std::snprintf(text, sizeof(text), "Unknown (raw %02X %02X)", low, high);
  return text;
}

}  // namespace truma_inetbox
}  // namespace esphome
