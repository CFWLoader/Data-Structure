#ifndef KMERGESORTER_H_
#define KMERGESORTER_H_

#include <vector>
#include <string>
#include <memory>
#include "FileBuffer.h"

class KMergeSorter
{
public:

	explicit KMergeSorter(const std::string&, size_t);

	~KMergeSorter();

	bool sliceBigFile();

	void createSliceFilesAndSave(const std::string&);

	std::string filenameMangler();

	void prepareFileBuffers();

	uint64_t getMinimunKeyInBuffers();

	void merge();

private:

	std::vector<std::unique_ptr<FileBuffer> > fileBuffers;

	FileBuffer rawInput;

	OutputFile output;

	std::string sourceFilename;

	size_t k;

	const size_t bufferSize;

	std::vector<uint64_t> outputBuffer;

	std::vector<std::string> slicedFilenames;
};

#endif