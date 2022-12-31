#include "common/random.h"

// UniformVector makes a vec filled with uniform random floats,
std::vector<double> RandomGenerator::UniformVector(int size, double low,
                                                   double high) {
  std::vector<double> vec(size);
  std::uniform_real_distribution<> dist(low, high);
  for (int i = 0; i < size; ++i) {
    vec[i] = dist(engine_);
  }
  return vec;
}

// NewNormalVector makes a vec filled with normal random floats.
std::vector<double> RandomGenerator::NewNormalVector(int size, double mean,
                                                     double stddev) {
  std::vector<double> vec(size);
  std::normal_distribution<double> dist(mean, stddev);
  for (int i = 0; i < size; ++i) {
    vec[i] = dist(engine_);
  }
  return vec;
}

// NormalMatrix makes a matrix filled with normal random floats.
std::vector<std::vector<double>> RandomGenerator::NormalMatrix(int row, int col,
                                                               double mean,
                                                               double stddev) {
  std::vector<std::vector<double>> matrix(row, std::vector<double>(col));
  std::normal_distribution<double> dist(mean, stddev);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      matrix[i][j] = dist(engine_);
    }
  }
  return matrix;
}

// UniformMatrix makes a matrix filled with uniform random floats.
std::vector<std::vector<double>> RandomGenerator::UniformMatrix(int row,
                                                                int col,
                                                                double low,
                                                                double high) {
  std::vector<std::vector<double>> matrix(row, std::vector<double>(col));
  std::uniform_real_distribution<> dist(low, high);
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      matrix[i][j] = dist(engine_);
    }
  }
  return matrix;
}

// Sample n values between low and high, but not in exclude.
std::vector<int> RandomGenerator::Sample(int low, int high, int n,
                                         std::unordered_set<int> exclude_set) {
  int internal_length = high - low;
  std::vector<int> sample;

  if (n >= internal_length - exclude_set.size()) {
    for (int i = low; i < high; ++i) {
      if (exclude_set.count(i) == 0) {
        sample.emplace_back(i);
        exclude_set.insert(i);
      }
    }
  } else {
    std::uniform_int_distribution<> dist(low, high);
    while (sample.size() < n) {
      auto random_num = dist(engine_);
      if (exclude_set.count(random_num) == 0) {
        sample.emplace_back(random_num);
        exclude_set.insert(random_num);
      }
    }
  }
  return sample;
}
