#include <iostream>
#include <vector>

#include "RandomNumberGenerator.hpp"
//#include "TestClass.h"
#include "FileBuffer.h"
#include "KMergeSorter.h"

using namespace std;

int main(int argc, char* argv[])
{
	//FileBuffer fileBuffer("./datas/originBig.dat", 20);
	//FileBuffer fileBuffer("./datas/testSmall.dat", 20);
	//FileBuffer fileBuffer("./datas/originLess.dat", 20);

	KMergeSorter kMergerSorter("./datas/originLess.dat", 10000);

	kMergerSorter.sliceBigFile();

	kMergerSorter.prepareFileBuffers();

	kMergerSorter.merge();

	//fileBuffer.loadData();

	//fileBuffer.sortBuffer(KeyLess());

	/*

	vector<uint64_t>::const_iterator iter = fileBuffer.getBuffer().begin(), end = fileBuffer.getBuffer().end();

	while(iter != end)
	{
		cout << *iter << endl;

		++iter;
	}
	*/

	/*
	int count = 1;

	while(fileBuffer.getHeadData() < static_cast<uint64_t>(INT64_INFINITY))
	{
		cout << fileBuffer.getHeadData() << endl;

		fileBuffer.popHeadData();

		if(count > 200)break;

		++count;
	}

	cout << endl;
	*/

	/*
	RandomNumberGenerator generator;

	OutputFile output("./datas/originLess.dat");

	vector<uint64_t>&& result = generator.generateNSequenceOfInt64(10000);

	bool writeResult = true;

	for(int i = 0; i < 5; ++i)
	{
		writeResult = output.outputTheSequenceData(result);

		if(!writeResult){
			cerr << "Error happened in output." << endl;
			break;
		}

		generator.generateNSequenceOfInt64(result, 10000);
	}
	*/

	return 0;
}