#include "MDFile.h"

int main(int argc, char const *argv[])
{
	MDFile{}.Header("This is a test for MDFile").Body("Test of the body section of the Markdown file. We can add **Bold** and *Italic* text as well")
	.Separator().Header("Subsection", 2).Body("We can add SubSections too!")
	.BeginTable(3)
	.Row({"HEADING 1", "Second Heading That is very long", " s "})
	.Row({"Item 11", "Item 12", ""})
	.Row({"Item 21", "Item 22", "Item 23"})
	.Row({"Item 31", "Item 32", "Item 33"})
	.Row({"Item 41", "Item 42", "Item 43"})
	.Row({0, 10, 31.412})
	.Row({31.31, "DATA", 'C'})
	.Row({31e2f, 31.3, "float data as well"})
	.EndTable().Write("Output.md");
	return 0;
}
