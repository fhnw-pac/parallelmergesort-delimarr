#include <iostream>
#include "MergeSort.h"
#include <random>
#include <chrono>

using namespace std;

int main() {

	MergeSort m;
	const uint64_t size = ((32 * 1024 * 1024) / NO_OF_THREADS) * NO_OF_THREADS;

	auto seqData = m.createRandomData(size);
	vector<int> parData(seqData);

	double seqTime = m.seqMergeSort(seqData);
	if (!m.proove(seqData)) {
		cout << "seq sort did not sort..." << endl;
		exit(-42);
	}

	double parTime = m.parMergeSort(parData);
	if (!m.proove(parData)) {
		cout << "par sort did not sort..." << endl;
		exit(-42);
	}

	cout << "sorted seq in " << seqTime / 1000 << "ms" << endl;
	cout << "sorted par in " << parTime / 1000 << "ms" << endl;
	cout << "speedup is " << seqTime / parTime << endl;
}
