#pragma once

#include <any>
#include <cstdint>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

// ParamName
using ParamName = std::string_view;

// Predefined hyper-parameter names
const ParamName LR = "Lr";                     // learing rate
const ParamName REG = "Reg";                   // regularization strength
const ParamName N_EPOCHS = "NEpochs";          // number of epochs
const ParamName N_FACTORS = "NFactors";        // number of factors
const ParamName RANDOM_STATE = "RandomState";  // random state (seed)
const ParamName INIT_MEAN = "InitMean";  // mean of gaussian initial parameter
const ParamName INIT_STD_DEV =
    "InitStdDev";  // standard deviation of gaussian initial parameter
const ParamName ALPHA = "Alpha";  // weight for negative samples in ALS
const ParamName SIMILARITY = "Similarity";

// Params stores hyper-parameters for an model. It is a map between strings
// (names) and std::any (values). For example, hyper-parameters for SVD
// is given by:
//  Params{
//		LR:       0.007,
//		N_EPOCHS:  100,
//		N_FACTORS: 80,
//		REG:      0.1,
//	}
//	notes: the values type may be one of {int, int64, double, string}
struct Params {
  Params() = default;

  explicit Params(std::unordered_map<ParamName, std::any> params)
      : params_(std::move(params)) {}

  std::unordered_map<ParamName, std::any> params_;

  std::any &operator[](ParamName name) { return params_[name]; }

  std::unordered_map<ParamName, std::any>::iterator Find(ParamName name) {
    return params_.find(name);
  }

  std::unordered_map<ParamName, std::any>::iterator Begin() {
    return params_.begin();
  }
  std::unordered_map<ParamName, std::any>::const_iterator Begin() const {
    return params_.cbegin();
  }
  std::unordered_map<ParamName, std::any>::iterator End() {
    return params_.end();
  }
  std::unordered_map<ParamName, std::any>::const_iterator End() const {
    return params_.cend();
  }

  int GetInt(ParamName name, int default_value) const;

  std::int64_t GetInt64(ParamName name, std::int64_t default_value) const;

  double GetDouble(ParamName name, double default_value) const;

  std::string GetString(ParamName name,
                        std::string_view default_value = "") const;

  // 合并Params
  Params Overwrite(const Params &params) const;

  // 返回json序列化得到的string
  std::string ToString() const;
};

// ParamsGrid contains candidate for grid search.
struct ParamsGrid {
  std::unordered_map<ParamName, std::vector<std::any>> grid_;

  ParamsGrid() = default;

  explicit ParamsGrid(std::unordered_map<ParamName, std::vector<std::any>> grid)
      : grid_(std::move(grid)) {}

  std::vector<std::any> &operator[](ParamName name) {
    return grid_[name];
  }

  int Len();

  int NumCombinations();

  void Fill(const ParamsGrid &default_value);
};
