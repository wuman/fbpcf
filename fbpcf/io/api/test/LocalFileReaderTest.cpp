/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include "folly/logging/xlog.h"

#include "fbpcf/io/api/LocalFileReader.h"
#include "fbpcf/io/api/test/utils/IOTestHelper.h"

namespace fbpcf::io {

TEST(LocalFileReaderTest, testReadingFromFile) {
  auto reader = std::make_unique<fbpcf::io::LocalFileReader>(
      IOTestHelper::getBaseDirFromPath(__FILE__) +
      "data/local_file_reader_test_file.txt");

  /*
    CASE 1A
    Buffer of size 20, read 20 bytes
  */
  auto buf = std::vector<char>(20);
  auto nBytes = reader->read(buf);

  EXPECT_EQ(nBytes, 20);
  IOTestHelper::expectBufferToEqualString(buf, "this is a test file\n", 20);

  /*
      CASE 1B
      Buffer of size 25, read 25 bytes
  */
  auto buf2 = std::vector<char>(25);
  nBytes = reader->read(buf2);
  EXPECT_EQ(nBytes, 25);
  IOTestHelper::expectBufferToEqualString(
      buf2, "it has many lines in it\n\n", 25);

  /*
      CASE 2
      Buffer of size 500, but file only has 45 bytes
      Expect to read 45 bytes
  */
  auto buf3 = std::vector<char>(500);

  nBytes = reader->read(buf3);

  EXPECT_EQ(nBytes, 45);
  IOTestHelper::expectBufferToEqualString(
      buf3, "the quick brown fox jumped over the lazy dog\n", 45);

  EXPECT_THROW(reader->read(buf3), std::runtime_error);
}

} // namespace fbpcf::io