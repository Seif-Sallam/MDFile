#include "include/MDFile.h"

#include <fstream>
#include <math.h>
#include <assert.h>

MDFile& MDFile::Header(const char* header, uint32_t level)
{
	for (int i = 0; i < level; i++)
		fileOutput << "#";
	fileOutput << " " << header << "\n\n";

	return *this;
}

MDFile& MDFile::Body(const char* text)
{
	fileOutput << text << "\n\n";
	return *this;
}

MDFile& MDFile::Separator()
{
	fileOutput << "---\n\n";
	return *this;
}

MDFile& MDFile::BeginTable(size_t cols)
{
	assert(cols > 0);
	numOfCols = cols;
	return *this;
}

std::string centerWithSpaces(const std::string& str, size_t desiredSize)
{
	size_t diff = (desiredSize - str.size());
	size_t eachSide =  diff / 2;
	return std::string(eachSide + diff % 2, ' ') + str + std::string(eachSide, ' ');
}

MDFile& MDFile::EndTable()
{
	size_t* largestSizes = new size_t[numOfCols];
	size_t lineWidth = 0;
	memset(largestSizes, 0, sizeof(*largestSizes) * numOfCols);
	// Finding the largest String size:
	for(size_t i = 0; i < rows.size(); i++)
	{
		const auto& data = rows[i].rowData;
		auto finalIndex = std::min(numOfCols, data.size());
		for(size_t j = 0; j < finalIndex; j++)
		{
			if(data[j].data.size() > largestSizes[j])
				largestSizes[j] = data[j].data.size();
		}
	}

	// Adding two spaces
	for(size_t i = 0; i < numOfCols; i++)
	{
		largestSizes[i] += 2;
		lineWidth += largestSizes[i];
	}

	// Helpers
	auto addRowWithBars = [&](){
		std::stringstream ss;
		ss << '|';
		for(size_t i = 0; i < this->numOfCols; i++)
		{
			size_t num = largestSizes[i];
			while(num != 0)
			{
				ss << '-';
				num--;
			}
			ss << '|';
		}
		return ss.str();
	};
	auto addRowWithData = [&](const std::vector<RowItem>& data)
	{
		std::stringstream ss;
		ss << '|';
		size_t finalIndex = std::min(data.size(), this->numOfCols);
		for (size_t i = 0; i < finalIndex; i++)
			ss << centerWithSpaces(data[i].data, largestSizes[i]) << '|';
		return ss.str();
	};
	// Header
	fileOutput << addRowWithData(rows[0].rowData) << '\n';
	fileOutput << addRowWithBars() << '\n';

	// Commit it to the file
	for(int i = 1; i < rows.size(); i++)
		fileOutput << addRowWithData(rows[i].rowData) << '\n';

	delete[] largestSizes;
	rows.clear();
	return *this;
}

MDFile& MDFile::Row(std::initializer_list<RowItem> rowData)
{
	rows.emplace_back(RowData{rowData});
	return *this;
}

MDFile& MDFile::Image(const char* imageName, const char* altText)
{
	if (altText == nullptr)
		fileOutput << "[" << imageName << "](" << imageName << ")\n";
	else
		fileOutput << "[" << altText << "](" << imageName << ")\n";

	return *this;
}

void MDFile::Write(const char* fileName)
{
	std::string output = fileOutput.str();
	uint32_t i = output.size() - 1;
	// Removing trailing spaces
	while(i >= 0)
	{
		if (output[i] != '\n')
			break;
		i--;
	}
	std::ofstream outputFile(fileName);
	if (outputFile.fail())
		return;
	outputFile.write(output.data(), i + 1);
	outputFile << "\n";
	outputFile.close();
}