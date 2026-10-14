// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) Fabian Schmidt and original contributors
// Copyright (c) RZ (@havanti) and contributors
// Imported from havanti/esphome-truma 1.0.43; attribution added 2026-10-14.
// See NOTICE and LICENSES/ESPHome-LICENSE for provenance and license notices.

#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/truma_inetbox/version.h"

namespace esphome {
namespace truma_inetbox {

class TrumaVersionTextSensor : public Component, public text_sensor::TextSensor {
 public:
  void setup() override { this->publish_state(TRUMA_INETBOX_VERSION); }
  void dump_config() override;
};

}  // namespace truma_inetbox
}  // namespace esphome
