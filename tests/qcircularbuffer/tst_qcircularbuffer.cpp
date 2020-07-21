#include "gtest/gtest.h"
//#include "gmock/gmock.h"

#include "CircularBuffer.h"
#include <QList>
#include <QVector>
#include <list>
#include <string>
#include <vector>

TEST(QCircularBufferTestInt, ConstructorTest)
{
  // Pretty standard construct a buffer with no data.
  CircularBuffer<int> int_buffer1(5);
  EXPECT_EQ(int_buffer1.size(), 0);
  EXPECT_EQ(int_buffer1.empty(), true);
  EXPECT_EQ(int_buffer1.capacity(), 5);

  // use assignment to copy empty buffer
  CircularBuffer<int> int_buffer2 = int_buffer1;
  EXPECT_EQ(int_buffer2.size(), 0);
  EXPECT_EQ(int_buffer2.empty(), true);
  EXPECT_EQ(int_buffer2.capacity(), 5);

  QVector<int> vec_data;
  vec_data << 100 << 200 << 300 << 400 << 500;
  QList<int> list_data;
  list_data << 1000 << 2000 << 3000 << 4000 << 5000;

  CircularBuffer<int> int_buffer3(vec_data);
  EXPECT_EQ(int_buffer3.size(), 5);
  EXPECT_EQ(int_buffer3.count(), 5);
  EXPECT_EQ(int_buffer3.length(), 5);
  EXPECT_EQ(int_buffer3.available(), 0);
  EXPECT_EQ(int_buffer3.empty(), false);
  EXPECT_EQ(int_buffer3.capacity(), 5);
  EXPECT_EQ(int_buffer3.front(), 100);
  EXPECT_EQ(int_buffer3.first(), 100);
  EXPECT_EQ(int_buffer3.constFirst(), 100);
  EXPECT_EQ(int_buffer3.back(), 500);
  EXPECT_EQ(int_buffer3.last(), 500);
  EXPECT_EQ(int_buffer3.constLast(), 500);
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer3.at(0), 100);
  EXPECT_EQ(int_buffer3.at(1), 200);
  EXPECT_EQ(int_buffer3.at(2), 300);
  EXPECT_EQ(int_buffer3.at(3), 400);
  EXPECT_EQ(int_buffer3.at(4), 500);
  // Check value() rather than at(). This will return a default value.
  EXPECT_EQ(int_buffer3.value(0), 100);
  EXPECT_EQ(int_buffer3.value(1), 200);
  EXPECT_EQ(int_buffer3.value(2), 300);
  EXPECT_EQ(int_buffer3.value(3), 400);
  EXPECT_EQ(int_buffer3.value(4), 500);
  EXPECT_EQ(int_buffer3.value(5), 0);
  EXPECT_EQ(int_buffer3.value(-1), 0);
  EXPECT_EQ(int_buffer3.value(5, 10), 10); // supply default value
  EXPECT_EQ(int_buffer3.value(-1, 10), 10);

  // create with QVector
  vec_data << 600;
  CircularBuffer<int> int_buffer4(vec_data);
  EXPECT_EQ(int_buffer4.size(), 6);
  EXPECT_EQ(int_buffer4.available(), 0);
  EXPECT_EQ(int_buffer4.empty(), false);
  EXPECT_EQ(int_buffer4.capacity(), 6);
  EXPECT_EQ(int_buffer4.front(), 100);
  EXPECT_EQ(int_buffer4.back(), 600);
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer4.at(0), 100);
  EXPECT_EQ(int_buffer4.at(1), 200);
  EXPECT_EQ(int_buffer4.at(2), 300);
  EXPECT_EQ(int_buffer4.at(3), 400);
  EXPECT_EQ(int_buffer4.at(4), 500);
  EXPECT_EQ(int_buffer4.at(5), 600);

  // Create with QVector but limit capacity.
  CircularBuffer<int> int_buffer5(vec_data, 5);
  EXPECT_EQ(int_buffer5.size(), 5);
  EXPECT_EQ(int_buffer5.available(), 0);
  EXPECT_EQ(int_buffer5.empty(), false);
  EXPECT_EQ(int_buffer5.capacity(), 5);
  EXPECT_EQ(int_buffer5.front(), 200);
  EXPECT_EQ(int_buffer5.back(), 600);
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer5.at(0), 200);
  EXPECT_EQ(int_buffer5.at(1), 300);
  EXPECT_EQ(int_buffer5.at(2), 400);
  EXPECT_EQ(int_buffer5.at(3), 500);
  EXPECT_EQ(int_buffer5.at(4), 600);

  // Create with QVector but extend capacity.
  CircularBuffer<int> int_buffer6(vec_data, 10);
  EXPECT_EQ(int_buffer6.size(), 6);
  EXPECT_EQ(int_buffer6.available(), 4);
  EXPECT_EQ(int_buffer6.empty(), false);
  EXPECT_EQ(int_buffer6.capacity(), 10);
  EXPECT_EQ(int_buffer6.front(), 100);
  EXPECT_EQ(int_buffer6.back(), 600);
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer6.at(0), 100);
  EXPECT_EQ(int_buffer6.at(1), 200);
  EXPECT_EQ(int_buffer6.at(2), 300);
  EXPECT_EQ(int_buffer6.at(3), 400);
  EXPECT_EQ(int_buffer6.at(4), 500);
  EXPECT_EQ(int_buffer6.at(5), 600);

  // Create with QList
  list_data << 6000;
  CircularBuffer<int> int_buffer7(list_data);
  EXPECT_EQ(int_buffer7.size(), 6);
  EXPECT_EQ(int_buffer7.available(), 0);
  EXPECT_EQ(int_buffer7.empty(), false);
  EXPECT_EQ(int_buffer7.capacity(), 6);
  EXPECT_EQ(int_buffer7.front(), 1000);
  EXPECT_EQ(int_buffer7.back(), 6000);
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer7.at(0), 1000);
  EXPECT_EQ(int_buffer7.at(1), 2000);
  EXPECT_EQ(int_buffer7.at(2), 3000);
  EXPECT_EQ(int_buffer7.at(3), 4000);
  EXPECT_EQ(int_buffer7.at(4), 5000);
  EXPECT_EQ(int_buffer7.at(5), 6000);

  // Create with QList but limit capacity
  CircularBuffer<int> int_buffer8(list_data, 5);
  EXPECT_EQ(int_buffer8.size(), 5);
  EXPECT_EQ(int_buffer8.available(), 0);
  EXPECT_EQ(int_buffer8.empty(), false);
  EXPECT_EQ(int_buffer8.capacity(), 5);
  EXPECT_EQ(int_buffer8.front(), 2000);
  EXPECT_EQ(int_buffer8.back(), 6000);
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer8.at(0), 2000);
  EXPECT_EQ(int_buffer8.at(1), 3000);
  EXPECT_EQ(int_buffer8.at(2), 4000);
  EXPECT_EQ(int_buffer8.at(3), 5000);
  EXPECT_EQ(int_buffer8.at(4), 6000);

  // Create with QList but extend capacity
  CircularBuffer<int> int_buffer9(list_data, 10);
  EXPECT_EQ(int_buffer9.size(), 6);
  EXPECT_EQ(int_buffer9.available(), 4);
  EXPECT_EQ(int_buffer9.empty(), false);
  EXPECT_EQ(int_buffer9.capacity(), 10);
  EXPECT_EQ(int_buffer9.front(), 1000);
  EXPECT_EQ(int_buffer9.back(), 6000);
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer9.at(0), 1000);
  EXPECT_EQ(int_buffer9.at(1), 2000);
  EXPECT_EQ(int_buffer9.at(2), 3000);
  EXPECT_EQ(int_buffer9.at(3), 4000);
  EXPECT_EQ(int_buffer9.at(4), 5000);
  EXPECT_EQ(int_buffer9.at(5), 6000);

  // Assignment operator
  CircularBuffer<int> int_buffer10 = int_buffer9;
  EXPECT_EQ(int_buffer10.size(), 6);
  EXPECT_EQ(int_buffer10.available(), 4);
  EXPECT_EQ(int_buffer10.empty(), false);
  EXPECT_EQ(int_buffer10.capacity(), 10);
  EXPECT_EQ(int_buffer10.front(), 1000);
  EXPECT_EQ(int_buffer10.back(), 6000);
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer10.at(0), 1000);
  EXPECT_EQ(int_buffer10.at(1), 2000);
  EXPECT_EQ(int_buffer10.at(2), 3000);
  EXPECT_EQ(int_buffer10.at(3), 4000);
  EXPECT_EQ(int_buffer10.at(4), 5000);
  EXPECT_EQ(int_buffer10.at(5), 6000);

  // Test reserve()
  CircularBuffer<int> int_buffer11(5);
  EXPECT_EQ(int_buffer11.capacity(), 5);
  EXPECT_EQ(int_buffer11.available(), 5);
  int_buffer11.reserve(20);
  EXPECT_EQ(int_buffer11.capacity(), 20);
  EXPECT_EQ(int_buffer11.available(), 20);

}

TEST(QCircularBufferTestStr, ConstructorTest)
{
  // Check it works with other objects.
  CircularBuffer<QString> str_buffer(5);
  EXPECT_EQ(str_buffer.size(), 0);
  EXPECT_EQ(str_buffer.empty(), true);
  EXPECT_EQ(str_buffer.capacity(), 5);
}

TEST(QCircularBufferTestInt, PushPopTest)
{
  CircularBuffer<int> int_buffer(5);
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

  int_buffer.pop();
  EXPECT_EQ(int_buffer.size(), 4);
  EXPECT_EQ(int_buffer.available(), 1);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 300);
  EXPECT_EQ(int_buffer.back(), 600);

  // Check variants (alias) of pop()
  int_buffer.popFront();
  EXPECT_EQ(int_buffer.size(), 3);
  EXPECT_EQ(int_buffer.available(), 2);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 400);
  EXPECT_EQ(int_buffer.back(), 600);

  int_buffer.popFirst();
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

  int_buffer.pop();
  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(int_buffer.available(), 5);
  EXPECT_EQ(int_buffer.empty(), true);
  EXPECT_EQ(int_buffer.capacity(), 5);
  // The following will fail as the buffer is empty
  //  EXPECT_EQ(circular_buffer.front(), 600);
  //  EXPECT_EQ(circular_buffer.back(), 600);

  // Check variants (alias) of push()
  int_buffer.push(100);
  auto value = int_buffer.takeFirst();
  EXPECT_EQ(value, 100);
  int_buffer.push(100);
  value = int_buffer.takeFront();
  EXPECT_EQ(value, 100);

  int_buffer.push(100);
  int_buffer.push(200);
  int_buffer.push_back(300);
  int_buffer.append(400);
  int_buffer.append(500);
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

TEST(QCircularBufferTestInt, OperatorTest)
{
  CircularBuffer<int> int_buffer(5);

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
  // Test at() method.
  // at() throws an exception if out of bounds
  EXPECT_EQ(int_buffer.at(0), 100);
  EXPECT_EQ(int_buffer.at(1), 200);
  EXPECT_EQ(int_buffer.at(2), 300);
  EXPECT_EQ(int_buffer.at(3), 400);
  EXPECT_EQ(int_buffer.at(4), 500);
  // the following fails with an out of bounds assertion.
  //  EXPECT_EQ(int_buffer.at(5), 1000);
  // value() returns default value if out of bounds
  EXPECT_EQ(int_buffer.value(0), 100);
  EXPECT_EQ(int_buffer.value(1), 200);
  EXPECT_EQ(int_buffer.value(2), 300);
  EXPECT_EQ(int_buffer.value(3), 400);
  EXPECT_EQ(int_buffer.value(4), 500);
  EXPECT_EQ(int_buffer.value(5), 0);
  EXPECT_EQ(int_buffer.value(-1), 0);
  EXPECT_EQ(int_buffer.value(5, 10), 10);  // supply default value
  EXPECT_EQ(int_buffer.value(-1, 10), 10); // supply default value
  // Test operator[]
  // [] does not check bounds
  EXPECT_EQ(int_buffer[0], 100);
  EXPECT_EQ(int_buffer[1], 200);
  EXPECT_EQ(int_buffer[2], 300);
  EXPECT_EQ(int_buffer[3], 400);
  EXPECT_EQ(int_buffer[4], 500);
  // size_type == size_t == unsigned long so no < 0 check needed.
  //  EXPECT_THROW(int_buffer.at(5), std::out_of_range);

  // Test << Operator item
  int_buffer.clear();
  int_buffer << 100 << 200 << 300 << 400 << 500 << 600;
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 200);
  EXPECT_EQ(int_buffer.back(), 600);
  EXPECT_EQ(int_buffer[0], 200);
  EXPECT_EQ(int_buffer[1], 300);
  EXPECT_EQ(int_buffer[2], 400);
  EXPECT_EQ(int_buffer[3], 500);
  EXPECT_EQ(int_buffer[4], 600);

  // Check operator<< QVector
  QVector<int> vec_data;
  vec_data << 100 << 200 << 300 << 400 << 500 << 600;
  int_buffer.clear();
  int_buffer << vec_data;
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 200);
  EXPECT_EQ(int_buffer.back(), 600);
  EXPECT_EQ(int_buffer[0], 200);
  EXPECT_EQ(int_buffer[1], 300);
  EXPECT_EQ(int_buffer[2], 400);
  EXPECT_EQ(int_buffer[3], 500);
  EXPECT_EQ(int_buffer[4], 600);

  // Check operator<< QList
  QList<int> list_data;
  list_data << 1000 << 2000 << 3000 << 4000 << 5000 << 6000;
  int_buffer.clear();
  int_buffer << list_data;
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 2000);
  EXPECT_EQ(int_buffer.back(), 6000);
  EXPECT_EQ(int_buffer[0], 2000);
  EXPECT_EQ(int_buffer[1], 3000);
  EXPECT_EQ(int_buffer[2], 4000);
  EXPECT_EQ(int_buffer[3], 5000);
  EXPECT_EQ(int_buffer[4], 6000);
}

TEST(QCircularBufferTestInt, IteratorTest)
{
  CircularBuffer<int> int_buffer(5);

  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(int_buffer.available(), 5);
  EXPECT_EQ(int_buffer.empty(), true);
  EXPECT_EQ(int_buffer.capacity(), 5);

  int_buffer.push_back(100);
  int_buffer.push_back(200);
  int_buffer.push_back(300);
  int_buffer.push_back(400);
  int_buffer.push_back(500);

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

TEST(QCircularBufferTestInt, PushPopVectorList)
{
  CircularBuffer<int> int_buffer(5);

  QVector<int> vec_data;
  vec_data << 100 << 200 << 300 << 400 << 500 << 600;
  int_buffer.clear();
  int_buffer.push(vec_data);
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 200);
  EXPECT_EQ(int_buffer.back(), 600);
  EXPECT_EQ(int_buffer[0], 200);
  EXPECT_EQ(int_buffer[1], 300);
  EXPECT_EQ(int_buffer[2], 400);
  EXPECT_EQ(int_buffer[3], 500);
  EXPECT_EQ(int_buffer[4], 600);

  // These next tests don't clear the buffer
  // Test conversion to QVector
  QVector<int> vector = int_buffer.toVector();
  EXPECT_EQ(vector.size(), int_buffer.size());
  EXPECT_EQ(vector[0], int_buffer[0]);
  EXPECT_EQ(vector[1], int_buffer[1]);
  EXPECT_EQ(vector[2], int_buffer[2]);
  EXPECT_EQ(vector[3], int_buffer[3]);
  EXPECT_EQ(vector[4], int_buffer[4]);

  // Test conversion to std::vector
  std::vector<int> std_vector = int_buffer.toStdVector();
  EXPECT_EQ(std_vector.size(), int_buffer.size());
  EXPECT_EQ(std_vector[0], int_buffer[0]);
  EXPECT_EQ(std_vector[1], int_buffer[1]);
  EXPECT_EQ(std_vector[2], int_buffer[2]);
  EXPECT_EQ(std_vector[3], int_buffer[3]);
  EXPECT_EQ(std_vector[4], int_buffer[4]);

  // Test conversion to QList
  QList<int> list = int_buffer.toList();
  EXPECT_EQ(list.size(), int_buffer.size());
  EXPECT_EQ(list[0], int_buffer[0]);
  EXPECT_EQ(list[1], int_buffer[1]);
  EXPECT_EQ(list[2], int_buffer[2]);
  EXPECT_EQ(list[3], int_buffer[3]);
  EXPECT_EQ(list[4], int_buffer[4]);

  // Test conversion to std::list
  std::list<int> std_list = int_buffer.toStdList();
  EXPECT_EQ(std_list.size(), int_buffer.size());
  EXPECT_EQ(std_list.front(), int_buffer[0]);
  std_list.pop_front();
  EXPECT_EQ(std_list.front(), int_buffer[1]);
  std_list.pop_front();
  EXPECT_EQ(std_list.front(), int_buffer[2]);
  std_list.pop_front();
  EXPECT_EQ(std_list.front(), int_buffer[3]);
  std_list.pop_front();
  EXPECT_EQ(std_list.front(), int_buffer[4]);
  //  std_list.pop_front();

  // Check operator<< QList
  QList<int> list_data;
  list_data << 1000 << 2000 << 3000 << 4000 << 5000 << 6000;
  int_buffer.clear();
  int_buffer.push(list_data);
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 2000);
  EXPECT_EQ(int_buffer.back(), 6000);
  EXPECT_EQ(int_buffer[0], 2000);
  EXPECT_EQ(int_buffer[1], 3000);
  EXPECT_EQ(int_buffer[2], 4000);
  EXPECT_EQ(int_buffer[3], 5000);
  EXPECT_EQ(int_buffer[4], 6000);

  // These next tests DO clear the buffer
  // Test pull conversion to QVector
  vector = int_buffer.pullVector();
  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(vector[0], 2000);
  EXPECT_EQ(vector[1], 3000);
  EXPECT_EQ(vector[2], 4000);
  EXPECT_EQ(vector[3], 5000);
  EXPECT_EQ(vector[4], 6000);

  // Test pull conversion to std::vector
  int_buffer.push(list_data);
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 2000);
  EXPECT_EQ(int_buffer.back(), 6000);
  std_vector = int_buffer.pullStdVector();
  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(std_vector[0], 2000);
  EXPECT_EQ(std_vector[1], 3000);
  EXPECT_EQ(std_vector[2], 4000);
  EXPECT_EQ(std_vector[3], 5000);
  EXPECT_EQ(std_vector[4], 6000);

  // Test pull conversion to QList
  int_buffer.push(list_data);
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 2000);
  EXPECT_EQ(int_buffer.back(), 6000);
  list = int_buffer.pullList();
  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(list[0], 2000);
  EXPECT_EQ(list[1], 3000);
  EXPECT_EQ(list[2], 4000);
  EXPECT_EQ(list[3], 5000);
  EXPECT_EQ(list[4], 6000);

  // Test pull conversion to std::list
  int_buffer.push(list_data);
  EXPECT_EQ(int_buffer.size(), 5);
  EXPECT_EQ(int_buffer.available(), 0);
  EXPECT_EQ(int_buffer.empty(), false);
  EXPECT_EQ(int_buffer.capacity(), 5);
  EXPECT_EQ(int_buffer.front(), 2000);
  EXPECT_EQ(int_buffer.back(), 6000);
  std_list = int_buffer.pullStdList();
  EXPECT_EQ(int_buffer.size(), 0);
  EXPECT_EQ(std_list.front(), 2000);
  std_list.pop_front();
  EXPECT_EQ(std_list.front(), 3000);
  std_list.pop_front();
  EXPECT_EQ(std_list.front(), 4000);
  std_list.pop_front();
  EXPECT_EQ(std_list.front(), 5000);
  std_list.pop_front();
  EXPECT_EQ(std_list.front(), 6000);
  //  std_list.pop_front();

}

TEST(QCircularBufferTestStr, PushPopTest)
{
  QString data[6] = { "first", "second", "third", "fourth", "fifth", "sixth" };
  CircularBuffer<QString> circular_buffer(5);

  // Now add in five items to fill buffer
  circular_buffer.push_back(data[0]);
  EXPECT_EQ(circular_buffer.size(), 1);
  EXPECT_EQ(circular_buffer.empty(), false);
  EXPECT_EQ(circular_buffer.capacity(), 5);
  EXPECT_EQ(circular_buffer.front(), data[0]);
  EXPECT_EQ(circular_buffer.back(), data[0]);
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

// int main(int argc, char** argv)
//{
//  ::testing::InitGoogleTest(&argc, argv);
//  return RUN_ALL_TESTS();
//}
