#include "KMergeSorter.h"
#include "RandomNumberGenerator.hpp"
#include "Auxiliary.h"

KMergeSorter::KMergeSorter(const std::string& srcFilename, size_t theBufferSize) : 
	fileBuffers(),
	rawInput(srcFilename, theBufferSize),
	output(srcFilename + ".sorted"),
	sourceFilename(srcFilename),
	k(0),
	bufferSize(theBufferSize),
	outputBuffer(theBufferSize),
	slicedFilenames()
{}

KMergeSorter::~KMergeSorter(){}

bool KMergeSorter::sliceBigFile()
{

	while(static_cast<uint64_t>(rawInput.getHeadData()) < static_cast<uint64_t>(INT64_INFINITY))
	{
			//std::cout << "bufferSize reached.  " << std::endl;

			this->createSliceFilesAndSave(this->filenameMangler());

			rawInput.clearBuffer();
	}

	return true;
}

void KMergeSorter::createSliceFilesAndSave(const std::string& filename)
{
	if(rawInput.bufferIsEmpty())return;

	slicedFilenames.push_back(filename);

	OutputFile tempOutput(filename);

	tempOutput.outputTheSequenceData(rawInput.getBuffer());
}

std::string KMergeSorter::filenameMangler()
{
	++k;

	char mangledName[5];

	_itoa_s(k, mangledName, 10);

	return sourceFilename + ".temp" + mangledName;
}

void KMergeSorter::prepareFileBuffers()
{
	size_t& new_size = const_cast<size_t&>(bufferSize);

	new_size = bufferSize / (k + 1);

	outputBuffer.resize(bufferSize);

	for(int i = 0; i < k; ++i)
	{
		fileBuffers.push_back(std::unique_ptr<FileBuffer>(new FileBuffer(slicedFilenames[i], bufferSize)));
	}
}

uint64_t KMergeSorter::getMinimunKeyInBuffers()
{
	std::vector<std::unique_ptr<FileBuffer>>::iterator iter = fileBuffers.begin(), end = fileBuffers.end();

	std::vector<std::unique_ptr<FileBuffer>>::iterator targetBuffer = iter;

	uint64_t target = (*iter)->getHeadData();

	while(iter != end)
	{

		if((*iter)->getHeadData() < target)
		{
			target = (*iter)->getHeadData();
			targetBuffer = iter;
		}

		++iter;
	}

	(*targetBuffer)->popHeadData();

	return target;
}

void KMergeSorter::merge()
{
	size_t index = 0;

	bool success = true;

	uint64_t record = this->getMinimunKeyInBuffers();

	while(record < INT64_INFINITY)
	{
		outputBuffer[index] = record;

		++index;

		if(index == bufferSize)
		{
			success = output.outputTheSequenceData(outputBuffer);

			if(success == false)
			{
				std::cerr << "Output failed." << std::endl;
			}

			index = 0;
		}

		record = this->getMinimunKeyInBuffers();
	}

	outputBuffer.erase(outputBuffer.begin() + index + 1, outputBuffer.end());

	output.outputTheSequenceData(outputBuffer);

	return;
}