/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <folly/Benchmark.h>
#include <vector>
#include "common/init/Init.h"

#include "fbpcf/mpc_framework/engine/tuple_generator/oblivious_transfer/ferret/DummyMatrixMultiplierFactory.h"
#include "fbpcf/mpc_framework/engine/tuple_generator/oblivious_transfer/ferret/RegularErrorMultiPointCot.h"
#include "fbpcf/mpc_framework/engine/tuple_generator/oblivious_transfer/ferret/TenLocalLinearMatrixMultiplierFactory.h"
#include "fbpcf/mpc_framework/engine/tuple_generator/oblivious_transfer/ferret/test/benchmarks/MatrixMultiplierBenchmark.h"

using namespace folly;
using namespace fbpcf::mpc_framework::engine::tuple_generator::
    oblivious_transfer;

inline void benchmarkMatrixMultiplier(
    std::unique_ptr<ferret::IMatrixMultiplierFactory> factory,
    uint64_t n) {
  ferret::MatrixMultiplierBenchmark matrixMultiplierBenchmark;
  BENCHMARK_SUSPEND {
    matrixMultiplierBenchmark.setup(
        std::move(factory), ferret::kExtendedSize, ferret::kBaseSize);
  }

  std::vector<__m128i> rst;
  while (n--) {
    rst = matrixMultiplierBenchmark.benchmark();
  }
  doNotOptimizeAway(rst);
}

BENCHMARK(DummyMatrixMultiplier, n) {
  benchmarkMatrixMultiplier(
      std::make_unique<ferret::insecure::DummyMatrixMultiplierFactory>(), n);
}

BENCHMARK(TenLocalLinearMatrixMultiplier, n) {
  benchmarkMatrixMultiplier(
      std::make_unique<ferret::TenLocalLinearMatrixMultiplierFactory>(), n);
}

int main(int argc, char* argv[]) {
  facebook::initFacebook(&argc, &argv);
  runBenchmarks();
  return 0;
}
