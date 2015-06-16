#ifndef FILEBUFFER_H_
#define FILEBUFFER_H_

#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>

class KeyLess
{
public:
	bool operator()(uint64_t a, uint64_t b)
	{
		return a <= b;
	}
};

class FileBuffer
{
public:

	explicit FileBuffer(const std::string&, size_t);

	~FileBuffer();

	bool bufferIsEmpty();

	void loadData();

	template<typename Compare = KeyLess>
	void sortBuffer(Compare method)
	{
		std::sort(buffer.begin(), buffer.begin() + availableSize, method);
	}

	uint64_t getHeadData();

	void popHeadData();

	std::vector<uint64_t>& getBuffer();

	std::ifstream& getRawInputStream();

	void clearBuffer();

private:

	std::ifstream in;

	const size_t maxSize;

	int currentIndex;

	size_t availableSize;

	std::vector<uint64_t> buffer;

	KeyLess keyLess;
};

class OutputFile
{
public:

	OutputFile(const std::string&);

	OutputFile(const std::string&, std::ios_base::openmode);

	~OutputFile();

	bool outputTheSequenceData(const std::vector<uint64_t>&);

private:

	std::ofstream out;

};

#endif