/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "fbpcf/mpc_framework/engine/util/test/aesTestHelper.h"
#include <cstdint>

namespace fbpcf::mpc_framework::engine::util {

void AesTestHelper::switchToDecrypt() {
  // convert the encryption key to the decryption key
  int8_t j = 0;
  int8_t i = kRound;
  std::array<__m128i, 11> decryptionKey;
  decryptionKey[i--] = roundKey_[j++];
  while (i > 0) {
    decryptionKey[i--] = _mm_aesimc_si128(roundKey_[j++]);
  }
  decryptionKey[i] = roundKey_[j];

  roundKey_ = decryptionKey;
}

void AesTestHelper::decryptInPlace(std::vector<__m128i>& ciphertext) const {
  // Using naked pointer for best performance. This is very hot code.
  uint32_t size = ciphertext.size();
  auto dataPointer = ciphertext.data();
  for (unsigned int i = 0; i < size; ++i) {
    dataPointer[i] = _mm_xor_si128(dataPointer[i], roundKey_.at(0));
  }
  for (unsigned int j = 1; j < kRound; ++j) {
    for (unsigned int i = 0; i < size; ++i) {
      dataPointer[i] = _mm_aesdec_si128(dataPointer[i], roundKey_.at(j));
    }
  }
  for (unsigned int i = 0; i < size; ++i)
    dataPointer[i] = _mm_aesdeclast_si128(dataPointer[i], roundKey_.at(kRound));
}

} // namespace fbpcf::mpc_framework::engine::util
