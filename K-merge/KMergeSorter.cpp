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
			//std::cout << "bufferSize reached." << std::endl;
			this->createSliceFilesAndSave(this->filenameMangler());

			rawInput.clearBuffer();
	}

	return true;
}

void KMergeSorter::createSliceFilesAndSave(const std::string& filename)
{
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

}

uint64_t KMergeSorter::getMinimunKeyInBuffers()
{
	return 0;
}