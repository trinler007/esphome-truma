// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) Fabian Schmidt and original contributors
// Copyright (c) RZ (@havanti) and contributors
// Imported from havanti/esphome-truma 1.0.43; attribution added 2026-10-14.
// See NOTICE and LICENSES/ESPHome-LICENSE for provenance and license notices.

#pragma once

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/truma_inetbox/TrumaiNetBoxApp.h"
#include "enum.h"

namespace esphome {
namespace truma_inetbox {

class TrumaTimerBinarySensor : public Component, public binary_sensor::BinarySensor, public Parented<TrumaiNetBoxApp> {
 public:
  void setup() override;
  void dump_config() override;

  void set_type(TRUMA_BINARY_SENSOR_TYPE val) { this->type_ = val; }

 protected:
  TRUMA_BINARY_SENSOR_TYPE type_;

 private:
};
}  // namespace truma_inetbox
}  // namespace esphome