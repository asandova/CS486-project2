#ifndef TEST_HPP
#define TEST_HPP

#include <vector>
#include <string>


using namespace std;

extern void test_and_print_message(const string & seq, const string & seq_truth,
	size_t k, const string & message);

void test_1(const string & method);

void test_2(const string & method);

void test_3(const string & method);

void test_seq_assembly();

#endif // !TEST_HPP
