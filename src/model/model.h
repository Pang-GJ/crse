#pragma once

#include "model/params.h"

// Model is interface for all models
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
