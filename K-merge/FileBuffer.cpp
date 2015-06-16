#include "FileBuffer.h"
#include "RandomNumberGenerator.hpp"

OutputFile::OutputFile(const std::string& filename) : out(filename, std::ios_base::trunc){}

OutputFile::OutputFile(const std::string& filename, std::ios_base::openmode flags) : out(filename, std::ios_base::trunc | flags){}

OutputFile::~OutputFile()
{
	out.close();
}

bool OutputFile::outputTheSequenceData(const std::vector<uint64_t>& intVector)
{
	//std::ofstream out(filename);

	if(!out.is_open())
	{
		std::cerr << "Output data failed." << std::endl;

		return false;
	}

	std::vector<uint64_t>::const_iterator iter = intVector.begin(), end = intVector.end();

	for(size_t i = 1; iter != end; ++iter, ++i)
	{
		out << *iter;

		if(i % 11 == 0)out << std::endl;
		else out << " ";
	}

	return true;
}

FileBuffer::FileBuffer(const std::string& filename, size_t size) : in(filename), maxSize(size), currentIndex(-1), availableSize(0), buffer(size), keyLess(){}

FileBuffer::~FileBuffer()
{
	in.close();
}

bool FileBuffer::bufferIsEmpty()
{
	return availableSize == 0;
}

void FileBuffer::loadData()
{
	//std::cout << "Loading." << std::endl;

	if(!in.is_open())
	{
		std::cerr << "File haven't been accessed normally." << std::endl;
		return;
	}

	while(availableSize < maxSize && !in.eof())
	{
		in >> buffer[availableSize];

		++availableSize;
	}

	currentIndex = -1;
}

uint64_t FileBuffer::getHeadData()
{
	if(this->bufferIsEmpty()){
		this->loadData();

		if(availableSize > 0)this->sortBuffer(keyLess);

		//std::cout << "Sort Complete." << std::endl;
	}

	if(availableSize == 0)
	{
		return static_cast<uint64_t>(INT64_INFINITY);
	}

	//std::cout << availableSize << std::endl;

	//++currentIndex;

	//std::cout << " In buffer:   " << buffer[currentIndex] << std::endl;

	//--availableSize;

	return buffer[currentIndex + 1];
}

void FileBuffer::popHeadData()
{
	++currentIndex;

	--availableSize;
}

std::vector<uint64_t>& FileBuffer::getBuffer()
{
	return buffer;
}

std::ifstream& FileBuffer::getRawInputStream()
{
	return in;
}

void FileBuffer::clearBuffer()
{
	availableSize = 0;
}