/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cstddef>
#include <memory>
#include <vector>

#include "fbpcf/io/api/IWriterCloser.h"

namespace fbpcf::io {

/*
This class is the API for buffered writer, which
provides the ability to specify a chunk size.
*/

constexpr size_t defaultChunkSize = 4096;

class BufferedWriter : public IWriterCloser {
 public:
  explicit BufferedWriter(
      IWriterCloser& baseWriter,
      const size_t chunkSize = defaultChunkSize)
      : buffer_{std::vector<char>(chunkSize)},
        currentPosition_{0},
        baseWriter_{baseWriter} {}

  int close() override;
  size_t write(std::vector<char>& buf) override;
  ~BufferedWriter() override;

  void flush();

 private:
  std::vector<char> buffer_;
  size_t currentPosition_;
  IWriterCloser& baseWriter_;
};

} // namespace fbpcf::io