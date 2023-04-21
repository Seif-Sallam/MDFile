#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <iomanip>
#include <vector>

class MDFile
{
	class RowItem
	{
	public:
		inline RowItem(uint32_t value) : data(std::to_string(value)) {}
		inline RowItem(int32_t value) : data(std::to_string(value)) {}
		inline RowItem(const char* value) : data(value) {}
		inline RowItem(char value) : data(std::to_string(value)) {}
		inline RowItem(float value) : data(std::to_string(value)) {}
		inline RowItem(double value) : data(std::to_string(value)) {}

	private:
		std::string data;
		friend class MDFile;
	};

	struct RowData
	{
		std::vector<RowItem> rowData;
	};
public:
	MDFile() = default;
	MDFile& Header(const char* header, uint32_t level = 1);
	MDFile& Body(const char* text);
	MDFile& Separator();
	MDFile& BeginTable(size_t cols);
	MDFile& EndTable();
	MDFile& Row(std::initializer_list<RowItem> rowData);
	MDFile& Image(const char* imageName, const char* altText = nullptr);

	void Write(const char* fileName);
private:
	std::stringstream fileOutput;
	std::vector<RowData> rows;
	size_t numOfCols;
};