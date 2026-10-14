// SPDX-License-Identifier: GPL-3.0-only
// Copyright (c) Fabian Schmidt and original contributors
// Copyright (c) RZ (@havanti) and contributors
// Imported from havanti/esphome-truma 1.0.43; attribution added 2026-10-14.
// See NOTICE and LICENSES/ESPHome-LICENSE for provenance and license notices.

#pragma once

#include "enum.h"
#include "esphome/components/select/select.h"
#include "esphome/components/truma_inetbox/TrumaiNetBoxApp.h"

namespace esphome {
namespace truma_inetbox {


class TrumaHeaterSelect : public Component, public select::Select, public Parented<TrumaiNetBoxApp> {
 public:
  void setup() override;
  void dump_config() override;

  void set_type(TRUMA_SELECT_TYPE val) { this->type_ = val; }

 protected:
  TRUMA_SELECT_TYPE type_;

  void control(const std::string &value) override;

 private:
};
}  // namespace truma_inetbox
}  // namespace esphome