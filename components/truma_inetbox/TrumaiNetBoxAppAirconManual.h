// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) Fabian Schmidt and original contributors
// Copyright (c) RZ (@havanti) and contributors
// Imported from havanti/esphome-truma 1.0.43; attribution added 2026-10-14.
// See NOTICE and LICENSES/ESPHome-LICENSE for provenance and license notices.

#pragma once

#include "TrumaStausFrameResponseStorage.h"
#include "TrumaStructs.h"

namespace esphome {
namespace truma_inetbox {

class TrumaiNetBoxAppAirconManual
    : public TrumaStausFrameResponseStorage<StatusFrameAirconManual, StatusFrameAirconManualResponse> {
 public:
  StatusFrameAirconManualResponse *update_prepare() override;
  void create_update_data(StatusFrame *response, uint8_t *response_len, uint8_t command_counter) override;
  void dump_data() const override;
  bool can_update() override;

  bool action_set_temp(uint8_t temperature);
  bool action_set_mode(AirconMode mode);
  bool action_set_vent_mode(AirconVentMode vent_mode);
  bool action_aircon_manual(uint8_t temperature, AirconMode mode, AirconVentMode vent_mode);
  bool action_set_light(uint8_t level);
};

}  // namespace truma_inetbox
}  // namespace esphome