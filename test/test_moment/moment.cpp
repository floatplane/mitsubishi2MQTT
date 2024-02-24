#define DOCTEST_CONFIG_IMPLEMENT  // REQUIRED: Enable custom main()
#include "moment.hpp"

#include <doctest.h>

const unsigned long MS_PER_DAY = 24 * 60 * 60 * 1000;
const unsigned long MS_PER_HOUR = 60 * 60 * 1000;
const unsigned long MS_PER_MINUTE = 60 * 1000;

TEST_CASE("test construction and reading back values") {
  Moment::resetRolloverCount();
  const auto one = Moment(1000).get();
  CHECK(one.milliseconds == 0);
  CHECK(one.seconds == 1);
  CHECK(one.minutes == 0);
  CHECK(one.hours == 0);
  CHECK(one.days == 0);
  CHECK(one.years == 0);

  unsigned long value = 2 * MS_PER_DAY + 3 * MS_PER_HOUR + 4 * MS_PER_MINUTE + 5678;
  const auto two = Moment(2 * MS_PER_DAY + 3 * MS_PER_HOUR + 4 * MS_PER_MINUTE + 5678).get();
  CHECK(two.milliseconds == 678);
  CHECK(two.seconds == 5);
  CHECK(two.minutes == 4);
  CHECK(two.hours == 3);
  CHECK(two.days == 2);
  CHECK(two.years == 0);

  uint32_t maxValue = 0xFFFFFFFF;
  const auto three = Moment(maxValue).get();
  CHECK(three.milliseconds == 295);
  CHECK(three.seconds == 47);
  CHECK(three.minutes == 2);
  CHECK(three.hours == 17);
  CHECK(three.days == 49);
  CHECK(three.years == 0);
}

TEST_CASE("handling rollover") {
  Moment::resetRolloverCount();
  const auto before = Moment(2000).get();
  const auto after = Moment(1000).get();

  CHECK(before.milliseconds == 0);
  CHECK(before.seconds == 2);
  CHECK(before.minutes == 0);
  CHECK(before.hours == 0);
  CHECK(before.days == 0);
  CHECK(before.years == 0);

  CHECK(after.milliseconds == 295);
  CHECK(after.seconds == 47 + 1);
  CHECK(after.minutes == 2);
  CHECK(after.hours == 17);
  CHECK(after.days == 49);
  CHECK(after.years == 0);
}

int main(int argc, char **argv) {
  doctest::Context context;

  // BEGIN:: PLATFORMIO REQUIRED OPTIONS
  context.setOption("success", true);      // Report successful tests
  context.setOption("no-exitcode", true);  // Do not return non-zero code on failed test case
  // END:: PLATFORMIO REQUIRED OPTIONS

  // YOUR CUSTOM DOCTEST OPTIONS

  context.applyCommandLine(argc, argv);
  return context.run();
}