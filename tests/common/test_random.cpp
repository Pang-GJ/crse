#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <algorithm>
#include <cmath>
#include <numeric>
#include "common/random.h"

const double RANDOM_EPSILON = 0.1;

double Mean(const std::vector<double> &vec) {
  return std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
}

double Stddev(const std::vector<double> &vec) {
  double mean = Mean(vec);
  double sq_sum = std::inner_product(
      vec.begin(), vec.end(), vec.begin(), 0.0,
      [](double const &x, double const &y) { return x + y; },
      [mean](double const &x, double const &y) {
        return (x - mean) * (y - mean);
      });
  return std::sqrt(sq_sum / vec.size());
}

TEST_CASE("test normal matrix") {
  auto rng = RandomGenerator(0);
  auto vec = rng.NormalMatrix(1, 1000, 1, 2)[0];
  CHECK_FALSE(std::abs(Mean(vec) - 1) > RANDOM_EPSILON);
  CHECK_FALSE(std::abs(Stddev(vec) - 2) > RANDOM_EPSILON);
}

TEST_CASE("test uniform matrix") {
  auto rng = RandomGenerator(0);
  auto vec = rng.UniformMatrix(1, 1000, 1, 2)[0];
  auto max_val = *std::max_element(vec.begin(), vec.end());
  auto min_val = *std::min_element(vec.begin(), vec.end());
  CHECK_FALSE(min_val < 1);
  CHECK_FALSE(max_val > 2);
}

TEST_CASE("test sample") {
  std::unordered_set<int> exclude_set{{0, 1, 2, 3, 4}};
  auto rng = RandomGenerator(0);
  for (int i = 1; i <= 10; i++) {
    auto sample = rng.Sample(0, 10, i, exclude_set);
    for (auto j : sample) {
      CHECK_FALSE(exclude_set.count(j) != 0);
    }
  }
}
