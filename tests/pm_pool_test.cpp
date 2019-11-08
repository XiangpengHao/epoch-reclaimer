#include "../pm_pool.h"

#include <glog/logging.h>
#include <gtest/gtest.h>
#include <fstream>

static const constexpr char* allocator_pool = "allocator0";
static const constexpr uint64_t pool_size = 1024 * 1024 * 1024;
static const constexpr uint64_t kCacheLineMask = 0x3F;

namespace very_pm {

GTEST_TEST(PMPoolTest, CreatePool) {
  PMPool::CreatePool(allocator_pool, pool_size);
  ASSERT_EQ(PMPool::pm_pool_->pool_addr_, VERY_PM_POOL_ADDR);

  std::ifstream in(allocator_pool, std::ifstream::ate | std::ifstream::binary);
  ASSERT_EQ(pool_size, in.tellg());
}

}  // namespace very_pm

int main(int argc, char** argv) {
  FLAGS_logtostderr = 1;
  google::InitGoogleLogging(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
