/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>

#include "fbpcf/mpc_framework/engine/communication/IPartyCommunicationAgent.h"
#include "fbpcf/mpc_framework/engine/tuple_generator/oblivious_transfer/ferret/IRcotExtender.h"

namespace fbpcf::mpc_framework::engine::tuple_generator::oblivious_transfer::
    ferret {

class IRcotExtenderFactory {
 public:
  virtual ~IRcotExtenderFactory() = default;
  virtual std::unique_ptr<IRcotExtender> create() = 0;
};

} // namespace
  // fbpcf::mpc_framework::engine::tuple_generator::oblivious_transfer::ferret
