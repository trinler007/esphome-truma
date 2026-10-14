// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) 2019 ESPHome
// Copyright (c) RZ (@havanti) and contributors
// Imported from havanti/esphome-truma 1.0.43; attribution added 2026-10-14.
// See NOTICE and LICENSES/ESPHome-LICENSE for provenance and license notices.

#pragma once

#ifdef USE_ESP32_FRAMEWORK_ESP_IDF

#include "uart_component_esp_idf.h"

namespace esphome {
namespace uart {

class truma_IDFUARTComponent : public IDFUARTComponent {
 public:
  // `uart_event_queue_` is always available in IDFUARTComponent (not conditional).
  volatile QueueHandle_t *get_uart_event_queue() { return &this->uart_event_queue_; }
};

}  // namespace uart
}  // namespace esphome

#endif  // USE_ESP32_FRAMEWORK_ESP_IDF
