// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) 2026 trinler007
#pragma once

#include "esphome/core/component.h"
#include "esphome/components/text_sensor/text_sensor.h"
#include "esphome/components/truma_inetbox/TrumaiNetBoxApp.h"
#include "esphome/components/truma_inetbox/heater_error.h"

namespace esphome {
namespace truma_inetbox {

class TrumaHeaterErrorTextSensor : public Component, public text_sensor::TextSensor, public Parented<TrumaiNetBoxApp> {
 public:
  void setup() override {
    this->parent_->get_heater()->add_on_message_callback([this](const StatusFrameHeater *status) {
      this->publish_state(heater_error_display_text(status->error_code_low, status->error_code_high));
    });
  }
};

}  // namespace truma_inetbox
}  // namespace esphome
