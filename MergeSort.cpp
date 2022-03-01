#include "MergeSort.h"
#include <chrono>
#include <thread>
#include <cassert>
#include <random>
#include <omp.h>

using namespace std;

void MergeSort::mMerge(std::vector<int>& a, uint64_t beg, uint64_t m, uint64_t end)
{
	vector<int> b(end - beg, 0);
	uint64_t i = 0, j = beg, k = m;
	while (j < m && k < end)
		if (a[j] <= a[k])
			b[i++] = a[j++];
		else
			b[i++] = a[k++];
	
	while (j < m)
		b[i++] = a[j++];

	while(i>0) {
		--i;
		a[beg + i] = b[i];
	}
}

void MergeSort::mSort(std::vector<int>& a, uint64_t beg, uint64_t end)
{
	if (end - beg > 1) {
		uint64_t m = (beg + end) >> 1;
		mSort(a, beg, m);
		mSort(a, m, end);
		mMerge(a, beg, m, end);
	}
}

void MergeSort::seqMSort(std::vector<int>& a)
{
	mSort(a, 0, a.size());
}

void MergeSort::parMSort(std::vector<int>& a)
{
	assert(a.size() % NO_OF_THREADS == 0);
	
	// TODO implement parallel merge sort
}

double MergeSort::meassuredSort(std::vector<int>& a, void(MergeSort::*sortFunc)(std::vector<int>& a))
{
	auto start = chrono::high_resolution_clock::now();

	(this->*sortFunc)(a);

	auto stop = chrono::high_resolution_clock::now();

	return (double)(stop - start).count();
}


double MergeSort::seqMergeSort(std::vector<int>& a)
{
	return meassuredSort(a, &MergeSort::seqMSort);
}

double MergeSort::parMergeSort(std::vector<int>& a)
{
	return meassuredSort(a, &MergeSort::parMSort);
}

bool MergeSort::proove(std::vector<int>& a)
{
	for (uint64_t i = 0; i < a.size() - 1; ++i) {
		if (a[i] > a[i + 1])
			return false;
	}

	return true;
}

std::vector<int> MergeSort::createRandomData(uint64_t size) {

	vector<int> data(size, 0);

	// random gen
	default_random_engine generator;
	uniform_int_distribution<int> distribution(0, (int)size);
	generator.seed(chrono::system_clock::now().time_since_epoch().count());

	for (int i = 0; i < size; ++i) {
		data[i] = distribution(generator);
	}

	return data;
}
