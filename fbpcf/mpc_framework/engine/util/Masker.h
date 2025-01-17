/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <emmintrin.h>
#include <vector>
#include "fbpcf/mpc_framework/engine/util/util.h"

namespace fbpcf::mpc_framework::engine::util {

template <class T>
class Masker {
 public:
  static T mask(T src, __m128i key);
  static T unmask(__m128i key, bool choice, T correction0, T correction1);
};

} // namespace fbpcf::mpc_framework::engine::util

#include "fbpcf/mpc_framework/engine/util/Masker_impl.h"
