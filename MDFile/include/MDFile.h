#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <iomanip>
#include <vector>

class MDFile
{
	struct RowData
	{
		std::vector<std::string> rowData;
	};
public:
	MDFile() = default;
	MDFile& Header(const char* header, uint32_t level = 1);
	MDFile& Body(const char* text);
	MDFile& Separator();
	MDFile& BeginTable(size_t cols);
	MDFile& EndTable();
	MDFile& Row(std::initializer_list<std::string> rowData);
	MDFile& Image(const char* imageName, const char* altText = nullptr);

	void Write(const char* fileName);
private:
	std::stringstream fileOutput;
	std::vector<RowData> rows;
	size_t numOfCols;
};