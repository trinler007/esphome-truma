// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) Fabian Schmidt and original contributors
// Copyright (c) RZ (@havanti) and contributors
// Imported from havanti/esphome-truma 1.0.43; attribution added 2026-10-14.
// See NOTICE and LICENSES/ESPHome-LICENSE for provenance and license notices.

#pragma once

#include "esphome/components/time/real_time_clock.h"
#include "esphome/components/truma_inetbox/TrumaiNetBoxApp.h"

namespace esphome {
namespace truma_inetbox {

class TrumaTime : public time::RealTimeClock, public Parented<TrumaiNetBoxApp> {
 public:
  void setup() override;
  void update() override;
  void dump_config() override;

  bool read_time();

  void set_auto_disable(bool val) { this->auto_disable_ = val; }

 protected:
  bool auto_disable_ = false;
  uint8_t auto_disable_count_ = 3;

 private:
};
}  // namespace truma_inetbox
}  // namespace esphome