#ifndef IMAGE_H
#define IMAGE_H
//Tyler Longbons

class image
{
std::vector < std::vector < std::string > > origFileData;
std::vector <int> scaledPixels;
std::vector <int> pixels;
std::vector <int> binaryPixels;
int MAX_PIXEL_VAL;
int total_Num_Pixels;
int min;
int max;
double average;

public:
	char* imgFileName;
	int height;
	int width;
	int readAsciiFile(std::istream& inFile);
	int findMax();
	int findMin();
	int findAverage();
	int writeAsciiFile(std::ostream& outFile);
	void resize();
	void printOrigFinalData();
	void printPixels();
	bool isTokenNumber(std::string token);
	bool isTokenComment(std::string token);
	int processHeaderData();
	int processAsciiFileData();
	std::string getFileType(std::istream& inFile);
	int getMaxPixelVal();
	int getWidth();
	int getHeight();
	int validatePixels();
	int rescale();
	void printNewPixels();
	int writeBinaryFile(std::ostream& outFile);
	std::string getExtension(std::string& fileName);
	int readBinaryFile(std::istream& inFile);
	image* createFrame(image*& inImage, int frameNumber,int totalFrames);

};



#endif
