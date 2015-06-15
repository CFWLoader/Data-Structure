#include <iostream>
#include <vector>

#include "RandomNumberGenerator.hpp"
#include "FileBuffer.h"

using namespace std;

int main(int argc, char* argv[])
{
	FileBuffer fileBuffer("./datas/originBig.dat", 20);
	//FileBuffer fileBuffer("./datas/testSmall.dat", 20);

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

	int count = 1;

	uint64_t temp;

	while((temp = fileBuffer.getHeadData()) < static_cast<uint64_t>(INT64_INFINITY))
	{
		cout << temp << endl;

		if(count > 200)break;

		++count;
	}

	cout << endl;
	
	/*
	RandomNumberGenerator generator;

	OutputFile output("./datas/originBig.dat");

	vector<uint64_t>&& result = generator.generateNSequenceOfInt64(10000);

	bool writeResult = true;

	for(int i = 0; i < 500; ++i)
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