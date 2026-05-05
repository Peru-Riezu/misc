#include <sys/uio.h>
#include <string.h>
#include <unistd.h>
#define PLACEHOLDER_LINE_INDEX 23
#define MAX_SOURCE_CODE_SIZE_IN_BYTES 42000
#define MAX_SOURCE_CODE_SIZE_IN_BYTES_STRINGIFIED 52, 50, 48, 48, 48

//so this is a self-replicating program, this kind of programs are called quines, for more info https://en.wikipedia.org/wiki/Quine_(computing)
//I guess this is not the best implementation of a quine but it is the one I came up with...

//just a random function to prove that this program could do anything alongside self-replicate
void f(void)
{
}

int main(void)
{
	//the magic happens here, inside this variable we copied the source code we had when this variable was still empty
	//it had just an empty new line between the opening and closing curly brackets, after copying the source code we indented it and then ran a vim macro
	//to put the correct prefix and suffix to each copied line, we set the size of the placeholder line to MAX_SOURCE_CODE_SIZE_IN_BYTES, and thus the program became a quine
	//also with this method we cannot use single or double quotes anywhere in our code... we must define string and character literals using their decimal representation
	struct iovec source_code[] =
	{
		{"#include <sys/uio.h>\n", 0},
		{"#include <string.h>\n", 0},
		{"#include <unistd.h>\n", 0},
		{"#define PLACEHOLDER_LINE_INDEX 23\n", 0},
		{"#define MAX_SOURCE_CODE_SIZE_IN_BYTES 42000\n", 0},
		{"#define MAX_SOURCE_CODE_SIZE_IN_BYTES_STRINGIFIED 52, 50, 48, 48, 48\n", 0},
		{"\n", 0},
		{"//so this is a self-replicating program, this kind of programs are called quines, for more info https://en.wikipedia.org/wiki/Quine_(computing)\n", 0},
		{"//I guess this is not the best implementation of a quine but it is the one I came up with...\n", 0},
		{"\n", 0},
		{"//just a random function to prove that this program could do anything alongside self-replicate\n", 0},
		{"void f(void)\n", 0},
		{"{\n", 0},
		{"}\n", 0},
		{"\n", 0},
		{"int main(void)\n", 0},
		{"{\n", 0},
		{"	//the magic happens here, inside this variable we copied the source code we had when this variable was still empty\n", 0},
		{"	//it had just an empty new line between the opening and closing curly brackets, after copying the source code we indented it and then ran a vim macro\n", 0},
		{"	//to put the correct prefix and suffix to each copied line, we set the size of the placeholder line to MAX_SOURCE_CODE_SIZE_IN_BYTES, and thus the program became a quine\n", 0},
		{"	//also with this method we cannot use single or double quotes anywhere in our code... we must define string and character literals using their decimal representation\n", 0},
		{"	struct iovec source_code[] =\n", 0},
		{"	{\n", 0},
		{(char [42000]){"\n"}, 0},
		{"	};\n", 0},
		{"\n", 0},
		{"	((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)[0] = 0;\n", 0},
		{"	for (size_t i = 0; i < sizeof(source_code)/sizeof(source_code[0]); i++)\n", 0},
		{"	{\n", 0},
		{"		if (i == PLACEHOLDER_LINE_INDEX)\n", 0},
		{"		{\n", 0},
		{"			//placeholder_line is nothing but a string representing the source code needed to declare the placeholder line element of source_code,\n", 0},
		{"			//it is coded as an array of decimal numbers to avoid putting characters that would need to be escaped\n", 0},
		{"			char placeholder_line[] = {9, 9, 123, 40, 99, 104, 97, 114, 32, 91, MAX_SOURCE_CODE_SIZE_IN_BYTES_STRINGIFIED, 93, 41, 123, 34, 92, 110, 34, 125, 44, 32, 48, 125, 44, 10, 0};\n", 0},
		{"\n", 0},
		{"			strcpy(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) + strlen(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)), placeholder_line);\n", 0},
		{"			continue;\n", 0},
		{"		}\n", 0},
		{"\n", 0},
		{"		char prefix[] = {9, 9, 123, 34, 0};\n", 0},
		{"\n", 0},
		{"		strcpy(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) + strlen(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)), prefix);\n", 0},
		{"		memcpy\n", 0},
		{"		(\n", 0},
		{"			((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) + strlen(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)),\n", 0},
		{"			(char *)source_code[i].iov_base, strlen((char *)source_code[i].iov_base)\n", 0},
		{"		);\n", 0},
		{"		((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)[strlen((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) - 1] = 0;\n", 0},
		{"\n", 0},
		{"		char suffix[] = {92, 110, 34, 44, 32, 48, 125, 44, 10, 0};\n", 0},
		{"		strcpy(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) + strlen(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)), suffix);\n", 0},
		{"	}\n", 0},
		{"\n", 0},
		{"	for (size_t i = 0; i < sizeof(source_code)/sizeof(source_code[0]); i++)\n", 0},
		{"	{\n", 0},
		{"		source_code[i].iov_len = strlen((char*)source_code[i].iov_base);\n", 0},
		{"	}\n", 0},
		{"\n", 0},
		{"	writev(STDOUT_FILENO, source_code, sizeof(source_code)/sizeof(source_code[0]));\n", 0},
		{"\n", 0},
		{"	f();\n", 0},
		{"}\n", 0},
		{"\n", 0},
	};

	((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)[0] = 0;
	for (size_t i = 0; i < sizeof(source_code)/sizeof(source_code[0]); i++)
	{
		if (i == PLACEHOLDER_LINE_INDEX)
		{
			//placeholder_line is nothing but a string representing the source code needed to declare the placeholder line element of source_code,
			//it is coded as an array of decimal numbers to avoid putting characters that would need to be escaped
			char placeholder_line[] = {9, 9, 123, 40, 99, 104, 97, 114, 32, 91, MAX_SOURCE_CODE_SIZE_IN_BYTES_STRINGIFIED, 93, 41, 123, 34, 92, 110, 34, 125, 44, 32, 48, 125, 44, 10, 0};

			strcpy(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) + strlen(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)), placeholder_line);
			continue;
		}

		char prefix[] = {9, 9, 123, 34, 0};

		strcpy(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) + strlen(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)), prefix);
		memcpy
		(
			((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) + strlen(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)),
			(char *)source_code[i].iov_base, strlen((char *)source_code[i].iov_base)
		);
		((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)[strlen((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) - 1] = 0;

		char suffix[] = {92, 110, 34, 44, 32, 48, 125, 44, 10, 0};
		strcpy(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base) + strlen(((char *)source_code[PLACEHOLDER_LINE_INDEX].iov_base)), suffix);
	}

	for (size_t i = 0; i < sizeof(source_code)/sizeof(source_code[0]); i++)
	{
		source_code[i].iov_len = strlen((char*)source_code[i].iov_base);
	}

	writev(STDOUT_FILENO, source_code, sizeof(source_code)/sizeof(source_code[0]));

	f();
}

