#include "Hello.h"
#include "fmt/core.h"
#include "common/logger.h"

void Hello::DoSomething() {
  fmt::print("Hello, {}!\n", "fmt");
  LOG_INFO("Hello, {}!\n", "spdlog");
}
