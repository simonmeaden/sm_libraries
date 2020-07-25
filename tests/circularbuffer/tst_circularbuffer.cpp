#include "gtest/gtest.h"
//#include "gmock/gmock.h"

#include <string>
#include "private/circularbuffer.h"

TEST(circularbufferTestInt, ConstructorTest)
{
  // Pretty standard construct a buffer with no data.
  circular_buffer<int> int_buffer(5);
  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(int_buffer.empty(), true);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_GT(int_buffer.max_size(), 0);

  // use assignment to copy empty buffer
  circular_buffer<int> int_buffer2 = int_buffer;
  EXPECT_EQ(int_buffer2.size(), 0);
  EXPECT_EQ(int_buffer2.empty(), true);
  EXPECT_EQ(int_buffer2.capacity(), 5);
  EXPECT_GT(int_buffer.max_size(), 0);
}

TEST(circularbufferTestStr, ConstructorTest)
{

  circular_buffer<std::string> str_buffer(5);
  EXPECT_EQ(str_buffer.size(), 0);
  EXPECT_EQ(str_buffer.empty(), true);
  EXPECT_EQ(str_buffer.capacity(), 5);

  // use assignment to copy empty buffer
  circular_buffer<std::string> str_buffer2 = str_buffer;
  EXPECT_EQ(str_buffer2.size(), 0);
  EXPECT_EQ(str_buffer2.empty(), true);
  EXPECT_EQ(str_buffer2.capacity(), 5);
  EXPECT_GT(str_buffer2.max_size(), 0);
}

TEST(circularbufferTestInt, PushPopTest)
{
  circular_buffer<int> int_buffer(5);
  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(int_buffer.available(), 5);
  EXPECT_EQ(int_buffer.empty(), true);
  EXPECT_EQ(int_buffer.capacity(), 5);

  // Now add in five items to fill buffer
  int_buffer.push_back(100);
  EXPECT_EQ(int_buffer.size(), 1);
  EXPECT_EQ(int_buffer.available(), 4);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 100);
  EXPECT_EQ(int_buffer.back(), 100);

  int_buffer.push_back(200);
  EXPECT_EQ(int_buffer.size(), 2);
  EXPECT_EQ(int_buffer.available(), 3);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 100);
  EXPECT_EQ(int_buffer.back(), 200);

  int_buffer.push_back(300);
  EXPECT_EQ(int_buffer.size(), 3);
  EXPECT_EQ(int_buffer.available(), 2);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 100);
  EXPECT_EQ(int_buffer.back(), 300);

  int_buffer.push_back(400);
  EXPECT_EQ(int_buffer.size(), 4);
  EXPECT_EQ(int_buffer.available(), 1);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 100);
  EXPECT_EQ(int_buffer.back(), 400);

  int_buffer.push_back(500);
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 100);
  EXPECT_EQ(int_buffer.back(), 500);


  // add in another, this should drop the first loaded.
  int_buffer.push_back(600);
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 200);
  EXPECT_EQ(int_buffer.back(), 600);

  int_buffer.pop_front();
  EXPECT_EQ(int_buffer.size(), 4);
  EXPECT_EQ(int_buffer.available(), 1);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 300);
  EXPECT_EQ(int_buffer.back(), 600);

  int_buffer.pop_front();
  EXPECT_EQ(int_buffer.size(), 3);
  EXPECT_EQ(int_buffer.available(), 2);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 400);
  EXPECT_EQ(int_buffer.back(), 600);

  int_buffer.pop_front();
  EXPECT_EQ(int_buffer.size(), 2);
  EXPECT_EQ(int_buffer.available(), 3);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 500);
  EXPECT_EQ(int_buffer.back(), 600);

  int_buffer.pop_front();
  EXPECT_EQ(int_buffer.size(), 1);
  EXPECT_EQ(int_buffer.available(), 4);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 600);
  EXPECT_EQ(int_buffer.back(), 600);

  int_buffer.pop_front();
  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(int_buffer.available(), 5);
  EXPECT_EQ(int_buffer.empty(), true);
  EXPECT_EQ(int_buffer.capacity(), 5);
  // The following will fail as the buffer is empty
  //  EXPECT_EQ(circular_buffer.front(), 600);
  //  EXPECT_EQ(circular_buffer.back(), 600);

  int_buffer.push_back(100);
  int_buffer.push_back(200);
  int_buffer.push_back(300);
  int_buffer.push_back(400);
  int_buffer.push_back(500);
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 100);
  EXPECT_EQ(int_buffer.back(), 500);
  int_buffer.clear();
  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(int_buffer.available(), 5);
  EXPECT_EQ(int_buffer.empty(), true);
  EXPECT_EQ(int_buffer.capacity(), 5);
  // The following will be anomalous as the buffer is empty
  //  EXPECT_EQ(circular_buffer.front(), 100);
  //  EXPECT_EQ(circular_buffer.back(), 500);

}

TEST(circularbufferTestInt, AtOpTest)
{
  circular_buffer<int> int_buffer(5);

  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(int_buffer.available(), 5);
  EXPECT_EQ(int_buffer.empty(), true);
  EXPECT_EQ(int_buffer.capacity(), 5);

  int_buffer.push_back(100);
  int_buffer.push_back(200);
  int_buffer.push_back(300);
  int_buffer.push_back(400);
  int_buffer.push_back(500);
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 100);
  EXPECT_EQ(int_buffer.back(), 500);
  // [] does not check bounds
  EXPECT_EQ(int_buffer[0], 100);
  EXPECT_EQ(int_buffer[1], 200);
  EXPECT_EQ(int_buffer[2], 300);
  EXPECT_EQ(int_buffer[3], 400);
  EXPECT_EQ(int_buffer[4], 500);
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer.at(0), 100);
  EXPECT_EQ(int_buffer.at(1), 200);
  EXPECT_EQ(int_buffer.at(2), 300);
  EXPECT_EQ(int_buffer.at(3), 400);
  EXPECT_EQ(int_buffer.at(4), 500);
  // size_type == size_t == unsigned long so no < 0 check needed.
  EXPECT_THROW(int_buffer.at(5), std::out_of_range);

  // test iterators.
  // Messy syntax but should work.
  auto it = int_buffer.begin();
  int i = 0;

  while (it != int_buffer.end()) {
    EXPECT_EQ(*it, int_buffer[i]);
    ++it;
    ++i;
  }

  auto rit = int_buffer.rbegin();
  i = 4;

  while (rit != int_buffer.rend()) {
    EXPECT_EQ(*rit, int_buffer[i]);
    ++rit;
    --i;
  }

}

TEST(circularbufferTestStr, PushPopTest)
{
  std::string data[6] = {
    "first",
    "second",
    "third",
    "fourth",
    "fifth",
    "sixth"
  };
  circular_buffer<std::string> circular_buffer(5);

  // Now add in five items to fill buffer
  circular_buffer.push_back(data[0]);
  EXPECT_EQ(circular_buffer.size(), 1);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[0]);
  EXPECT_EQ(circular_buffer.back(), data[0]);

  circular_buffer.push_back(data[1]);
  EXPECT_EQ(circular_buffer.size(), 2);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[0]);
  EXPECT_EQ(circular_buffer.back(), data[1]);

  circular_buffer.push_back(data[2]);
  EXPECT_EQ(circular_buffer.size(), 3);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[0]);
  EXPECT_EQ(circular_buffer.back(), data[2]);

  circular_buffer.push_back(data[3]);
  EXPECT_EQ(circular_buffer.size(), 4);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[0]);
  EXPECT_EQ(circular_buffer.back(), data[3]);

  circular_buffer.push_back(data[4]);
  EXPECT_EQ(circular_buffer.size(), 5);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[0]);
  EXPECT_EQ(circular_buffer.back(), data[4]);

  // add in another, this should drop the first loaded.
  circular_buffer.push_back(data[5]);
  EXPECT_EQ(circular_buffer.size(), 5);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[1]);
  EXPECT_EQ(circular_buffer.back(), data[5]);

  circular_buffer.pop_front();
  EXPECT_EQ(circular_buffer.size(), 4);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[2]);
  EXPECT_EQ(circular_buffer.back(), data[5]);

  circular_buffer.pop_front();
  EXPECT_EQ(circular_buffer.size(), 3);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[3]);
  EXPECT_EQ(circular_buffer.back(), data[5]);

  circular_buffer.pop_front();
  EXPECT_EQ(circular_buffer.size(), 2);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[4]);
  EXPECT_EQ(circular_buffer.back(), data[5]);

  circular_buffer.pop_front();
  EXPECT_EQ(circular_buffer.size(), 1);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[5]);
  EXPECT_EQ(circular_buffer.back(), data[5]);

  circular_buffer.pop_front();
  EXPECT_EQ(circular_buffer.size(), 0);
  EXPECT_EQ(circular_buffer.empty(), true);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  // The following will fail as the buffer is empty
  //  EXPECT_EQ(circular_buffer.front(), data[5]);
  //  EXPECT_EQ(circular_buffer.back(), data[5]);

}


int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
