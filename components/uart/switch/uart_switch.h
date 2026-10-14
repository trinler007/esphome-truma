// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) 2019 ESPHome
// Copyright (c) RZ (@havanti) and contributors
// Imported from havanti/esphome-truma 1.0.43; attribution added 2026-10-14.
// See NOTICE and LICENSES/ESPHome-LICENSE for provenance and license notices.

#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/switch/switch.h"

#include <vector>

namespace esphome {
namespace uart {

class UARTSwitch : public switch_::Switch, public UARTDevice, public Component {
 public:
  void loop() override;

  void set_data(const std::vector<uint8_t> &data) { data_ = data; }
  void set_send_every(uint32_t send_every) { this->send_every_ = send_every; }

  void dump_config() override;

 protected:
  void write_command_();
  void write_state(bool state) override;
  std::vector<uint8_t> data_;
  uint32_t send_every_;
  uint32_t last_transmission_;
};

}  // namespace uart
}  // namespace esphome
