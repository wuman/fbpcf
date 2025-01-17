/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include "fbpcf/mpc_framework/mpc_std_lib/shuffler/IShuffler.h"

namespace fbpcf::mpc_framework::mpc_std_lib::shuffler {

template <typename T>
class IShufflerFactory {
 public:
  virtual ~IShufflerFactory() = default;
  virtual std::unique_ptr<IShuffler<T>> create() = 0;
};

} // namespace fbpcf::mpc_framework::mpc_std_lib::shuffler
