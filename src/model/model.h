#pragma once

#include <cstdint>
#include "common/random.h"
#include "model/params.h"

// Model is the interface for all models
class Model {
 public:
  Model() = default;

  // Set parameters
  virtual void SetParams(Params params) = 0;

  // Get parameters
  virtual Params GetParams() = 0;

  // Get parameters grid
  virtual ParamsGrid GetParamsGrid() = 0;

  // Clear model weights
  virtual void Clear() = 0;
};

// BaseModel model must be included by every recommendation model.
// Hyper-parameters, ID sets, random generator and fitting options are managed
// the BaseModel model.
// 模型并不是继承自BaseModel，而是组合关系，模型应该继承Model类
class BaseModel {
 public:
  explicit BaseModel(Params params)
      : params_(std::move(params)),
        rand_state_(params.GetInt64(RANDOM_STATE, 0)),
        rng_(rand_state_) {}

  void SetParams(Params params) {
    params_ = std::move(params);
    rand_state_ = params_.GetInt64(RANDOM_STATE, 0);
    rng_ = RandomGenerator(rand_state_);
  }

  Params GetParams() { return params_; }

  RandomGenerator &GetRandomGenerator() { return rng_; }

  Params params_;  // Hyper-parameters

 private:
  std::int64_t rand_state_;  // random seed
  RandomGenerator rng_;      // random generator
};
