#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../src/Trainer.h"
#include "MockBird.h"

using ::testing::AtLeast; // #1
using ::testing::Return;

TEST(TrainerTest, TestShow) {
  MockBird bird;             // #2
  EXPECT_CALL(bird, fly(10))   // #3
      .Times(AtLeast(2));

  Trainer trainer(bird); // #4
  trainer.show();
  trainer.show();
}
