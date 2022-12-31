#include "model/params.h"
#include <nlohmann/json.hpp>
#include "common/logger.h"

int Params::GetInt(ParamName name, int default_value) const {
  const auto &iter = params_.find(name);
  if (iter == params_.end()) {
    return default_value;
  }

  if (iter->second.type() == typeid(int)) {
    return std::any_cast<int>(iter->second);
  }
  LOG_ERROR("type mismatch, param name: {}, actual type: {}", name,
            iter->second.type().name());
  return default_value;
}

std::int64_t Params::GetInt64(ParamName name,
                              std::int64_t default_value) const {
  const auto &iter = params_.find(name);
  if (iter == params_.end()) {
    return default_value;
  }

  const auto &type = iter->second.type();
  if (type == typeid(std::int64_t)) {
    return std::any_cast<std::int64_t>(iter->second);
  }
  if (type == typeid(int)) {
    return static_cast<std::int64_t>(std::any_cast<int>(iter->second));
  }
  LOG_ERROR("type mismatch, param name: {}, actual type: {}", name,
            iter->second.type().name());
  return default_value;
}

double Params::GetDouble(ParamName name, double default_value) const {
  const auto &iter = params_.find(name);
  if (iter == params_.end()) {
    return default_value;
  }

  const auto &type = iter->second.type();
  if (type == typeid(double)) {
    return std::any_cast<double>(iter->second);
  }
  if (type == typeid(int)) {
    return static_cast<double>(std::any_cast<int>(iter->second));
  }
  if (type == typeid(std::int64_t)) {
    return static_cast<double>(std::any_cast<std::int64_t>(iter->second));
  }
  LOG_ERROR("type mismatch, param name: {}, actual type: {}", name,
            iter->second.type().name());
  return default_value;
}

std::string Params::GetString(ParamName name,
                              std::string_view default_value) const {
  const auto &iter = params_.find(name);
  if (iter == params_.end()) {
    return default_value.data();
  }

  const auto &type = iter->second.type();
  if (type == typeid(std::string)) {
    return std::any_cast<std::string>(iter->second);
  }
  if (type == typeid(const char *)) {
    return std::any_cast<const char *>(iter->second);
  }
  if (type == typeid(std::int64_t)) {
    return std::to_string(std::any_cast<std::int64_t>(iter->second));
  }
  if (type == typeid(int)) {
    return std::to_string(std::any_cast<int>(iter->second));
  }
  if (type == typeid(double)) {
    return std::to_string(std::any_cast<double>(iter->second));
  }
  LOG_ERROR("type mismatch, param name: {}, actual type: {}", name,
            iter->second.type().name());
  return default_value.data();
}

// 合并Params
Params Params::Overwrite(const Params &params) const {
  Params over_params = *this;
  auto &hash_map = over_params.params_;
  for (const auto &[k, v] : params.params_) {
    hash_map[k] = v;
  }
  return over_params;
}

std::string Params::ToString() const {
  nlohmann::json json;
  for (const auto &[k, v] : params_) {
    json[k] = GetString(k, "null");
  }
  return json.dump();
}

int ParamsGrid::Len() { return grid_.size(); }

int ParamsGrid::NumCombinations() {
  int count = 1;
  for (const auto &[k, v] : grid_) {
    count *= v.size();
  }
  return count;
}

void ParamsGrid::Fill(const ParamsGrid &default_value) {
  for (const auto &[k, v] : default_value.grid_) {
    if (grid_.count(k) == 0) {
      grid_[k] = v;
    }
  }
}
