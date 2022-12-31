#include <cstdint>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <fmt/core.h>
#include "model/params.h"

TEST_CASE("test params init and ToString") {
  Params params({{N_FACTORS, 1}, {LR, 0.1}, {RANDOM_STATE, 0}});
  fmt::print("params: {}\n", params.ToString());
}

TEST_CASE("test params GetInt") {
  Params params{};
  // empty case
  CHECK(-1 == params.GetInt(N_FACTORS, -1));
  // Normal case
  params[N_FACTORS] = 0;
  CHECK(0 == params.GetInt(N_FACTORS, -1));
  // Wrong type case
  params[N_FACTORS] = "hello";
  CHECK(-1 == params.GetInt(N_FACTORS, -1));
}

TEST_CASE("test params GetDouble") {
  Params params{};
  // empty case
  CHECK(0.1 == params.GetDouble(LR, 0.1));
  // Normal case
  params[LR] = 1.0;
  CHECK(1.0 == params.GetDouble(LR, 0.1));
  // Convertible case
  params[LR] = 2;
  CHECK(2.0 == params.GetDouble(LR, 0.1));
  params[LR] = static_cast<std::int64_t>(3);
  CHECK(3.0 == params.GetDouble(LR, 0.1));
  // Wrong type case
  params[LR] = "hello";
  CHECK(0.1 == params.GetDouble(LR, 0.1));
}

TEST_CASE("test params GetString") {
  Params params;
  // empty case
  CHECK("" == params.GetString(SIMILARITY));
  CHECK("no thing" == params.GetString(SIMILARITY, "no thing"));
  // Normal case
  params[SIMILARITY] = "cosine";
  CHECK("cosine" == params.GetString(SIMILARITY));
  params[SIMILARITY] = std::string("dot");
  CHECK("dot" == params.GetString(SIMILARITY));
  params[SIMILARITY] = 2;
  CHECK("2" == params.GetString(SIMILARITY));
  params[SIMILARITY] = 3.0;
  CHECK("3.000000" == params.GetString(SIMILARITY));
}

TEST_CASE("test param grid") {
  ParamsGrid grid{};
  grid["a"] = {0, 1};

  ParamsGrid default_grid{};
  default_grid["a"] = {2, 3};
  default_grid["b"] = {4, 5};

  CHECK(1 == grid.Len());

  grid.Fill(default_grid);
  CHECK(0 == std::any_cast<int>(grid["a"][0]));
  CHECK(1 == std::any_cast<int>(grid["a"][1]));
  CHECK(4 == std::any_cast<int>(grid["b"][0]));
  CHECK(5 == std::any_cast<int>(grid["b"][1]));
}
