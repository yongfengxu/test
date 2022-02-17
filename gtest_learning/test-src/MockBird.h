#include "../src/IBird.h"
#include <iostream>
#include "gmock/gmock.h"

class MockBird : public IBird {
public:
  MOCK_METHOD(int, fly, (int), (override));
};
