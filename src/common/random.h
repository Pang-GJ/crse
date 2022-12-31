#pragma once

#include <cstdint>
#include <random>
#include <unordered_set>
#include <vector>

class RandomGenerator {
 public:
  explicit RandomGenerator(std::int64_t seed) : engine_(seed) {}

  // UniformVector makes a vec filled with uniform random floats,
  std::vector<double> UniformVector(int size, double low, double high);

  // NewNormalVector makes a vec filled with normal random floats.
  std::vector<double> NewNormalVector(int size, double mean, double stddev);

  // NormalMatrix makes a matrix filled with normal random floats.
  std::vector<std::vector<double>> NormalMatrix(int row, int col, double mean,
                                                double stddev);

  // UniformMatrix makes a matrix filled with uniform random floats.
  std::vector<std::vector<double>> UniformMatrix(int row, int col, double low,
                                                 double high);

  // Sample n values between low and high, but not in exclude.
  std::vector<int> Sample(int low, int high, int n,
                          std::unordered_set<int> exclude_set);

 private:
  std::mt19937 engine_;
};
