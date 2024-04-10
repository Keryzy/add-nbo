#include <fstream>
#include <stdint.h>
#include <netinet/in.h> //for htonl

long getFileSize(FILE* file){
	long currentPosition = ftell(file);
	fseek(file, 0, SEEK_END);
    	long fileSize = ftell(file);
    	fseek(file, currentPosition, SEEK_SET);
    	return fileSize;
}

int main(int argc, char* argv[]) {
	FILE *five_hundred;
	FILE *thousand;
	uint32_t num1, num2, result;

	thousand = fopen(argv[1],"r");
	five_hundred = fopen(argv[2], "r");

	if(thousand == NULL | five_hundred == NULL){
		printf("File open error");
		return 1;
	}

	long thousand_size = getFileSize(thousand);
	long five_hundred_size = getFileSize(five_hundred);
	
	if(thousand_size < 4 | five_hundred_size < 4){
		printf("File size error");
		return 1;
	}

	//Notion
	fread(&num1, sizeof(uint32_t), 1, thousand);
	fread(&num2, sizeof(uint32_t), 1, five_hundred);

	// little-endian -> big-endian 
	// num2 0xe803 -> 0x03e8
	// num1 0xf401 -> 0x01f4
	num1 = htonl(num1);
	num2 = htonl(num2);

	result = num1 + num2;

	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", num1, num1, num2, num2, result, result);

	fclose(five_hundred);
	fclose(thousand);
}
