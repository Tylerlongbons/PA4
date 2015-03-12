//Tyler Longbons

#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <math.h>

#include "image.h"


int height;
int width;
int MAX_PIXEL_VAL;
int total_Num_Pixels;
int min;
int max;
double average;
char* imgFileName;

//Where we are storing the file
std::vector < std::vector < std::string > > origFileData;
//std::vector <std::string> pixels;
std::vector <int> scaledPixels;
std::vector <int> pixels;
std::vector <int> binaryPixels;

std::string image::getFileType(std::istream& inFile)
{
	if(!inFile)
	{
		return "invalid";
	}
	
	std::string line;
	getline(inFile, line);

	for(unsigned int i = 0; i < 3; i++)
	{
		char c = line[i];
		if(i == 0)
		{
			if(c != 'P')
			{
				return "invalid";
			}
		}
		else if(i == 1)
		{
			if(c != '2' && c != '5')
			{
				return "invalid";
			}
			if(c == '5')
			{
				return "binary";
			}
		}else
		{
			if(!isspace(c) && c != '\0' && c != '#')
			{
				return "invalid";
			}
		}
	}
		return "ascii";
}


//Use for Debugging
void image::printOrigFinalData()
{
		for(unsigned int i = 0; i < 10;i++)
		{
			std::cout<<"Line: " << i << std::endl;
				for(unsigned int j = 0; j < origFileData[i].size();j++)
				{

					std::cout<<"MyData: " << origFileData[i][j] <<std::endl;
				}
		}
}

//Use for debugging
void image::printPixels()
{
		for(unsigned int i = 0;i < 15;i++)
		{
			std::cout<<"Pixels"<< i <<": " << pixels[i] << std::endl;
		}
}


int image::getWidth()
{
	width = this->pixels[0];
	if(width <= 0)
	{
		return -1;
	}
	return 0;
}

int image::getHeight()
{
	height = this->pixels[1];
	if(height <= 0)
	{
		return -1;
	}
	return 0;
}
int image::getMaxPixelVal()
{
	MAX_PIXEL_VAL = this->pixels[2];
	if(MAX_PIXEL_VAL < 0  || MAX_PIXEL_VAL > 256)
	{
		return -1;
	}
	return 0;
}

int image::processHeaderData()
{
	if(getWidth() == -1)
	{
		//std::cout << "BAD WIDTH: "<< this->width << std::endl;
		return -1;
	}
	if(getHeight() == -1)
	{
		//std::cout << "BAD height: "<<this->height << std::endl;
		return -1;
	}
	if(getMaxPixelVal() == -1)
	{
		//std::cout << "BAD max: "<< this->MAX_PIXEL_VAL << std::endl;
		return -1;
	}


	return 0;
}



bool image::isTokenNumber(std::string token)
{
	bool isNumber = true;
	unsigned int i         = 0;
	while(isNumber && i < token.length())
	{
		char c 	  = token[i];
		if(isdigit(c) == 0)
		{
			isNumber = false;
		}
		i++;
	}
	return isNumber;
}

bool image::isTokenComment(std::string token)
{
	int found = token.find("#");
	if(found == -1)
	{
		return false;
	}else
	{
		return true;
	}
}

std::string getCommentNumber(std::string token)
{
		int found                = token.find("#");
		std::string commentVal   = "-1";
		if (found != -1)
		{
			if(found > 0)
			{
				commentVal       = token.substr(0, found);
			}
		}
	return commentVal;
}


int image::processAsciiFileData()
{


	for(unsigned int i = 0; i < this->origFileData.size();i++)
		{
				for(unsigned int j = 0; j < this->origFileData[i].size();j++)
				{
					if(i == 0 && j == 0)
					{	
						if(isTokenComment(this->origFileData[i][j]) == true)
						{
							if(this->origFileData.size() == 1)
							{
								return -1;
							}
								break;
						}

					}else
					{
						if(isTokenNumber(this->origFileData[i][j]) == true)
						{
							this->pixels.push_back(atoi(this->origFileData[i][j].c_str()));
						}else if(isTokenComment(this->origFileData[i][j]) == true)
						{
							std::string commentVal = getCommentNumber(this->origFileData[i][j]);
								if(commentVal != "-1")
								{
									this->pixels.push_back(atoi(commentVal.c_str()));
									break;
								}else
								{
									break;
								}
						}else
						{
							return -1;
						}
					}	
				}
		}


	return 0;
}



int image::readAsciiFile(std::istream& inFile)
{
	
	if(!inFile)
	{
		return -1;
	}
	//int lineCount = 0;
	std::string line;
	//Read each line primarily to make parsing comments easier
	
	while(getline(inFile, line))
	{
		std::vector<std::string> row;

		std::istringstream lineStream(line);
		std::string token;

		//break line into tokens to make sure we are 
		//getting valid entries 
		while(lineStream >> token)
		{
			row.push_back(token);
		}
		this->origFileData.push_back(row);
		//lineCount++;
	}
	

		return 0;
}



int image::validatePixels()
{
	total_Num_Pixels    = this->width * this->height;
	int actualNumPixels = 0;
	if(MAX_PIXEL_VAL == 256)
	{
		this->MAX_PIXEL_VAL = 255;
	}

	for(unsigned int i = 3; i < this->pixels.size(); i++)
	{
		int pixel = this->pixels[i]; 
		if(pixel <= this->MAX_PIXEL_VAL && pixel >= 0)
		{
			actualNumPixels++;
		}else
		{
			return -1;
		}
	}
		if(total_Num_Pixels != actualNumPixels)
		{
			return -1;
		}
		return 0;
}



int image::findMax()
{
	max = 0;

	for(unsigned int i = 3; i < this->pixels.size(); i++)
	{
		int pixel = this->pixels[i]; 
		if(pixel > max)
		{
			max = pixel;
		}
	}
	return 0;
}



int image::findMin()
{
	min = 255;

	for(unsigned int i = 3; i < this->pixels.size(); i++)
	{
		int pixel = this->pixels[i]; 
		if(pixel < min)
		{
			min = pixel;
		}
	}
	return 0;

}


int image::findAverage()
{
	average = 0;

	for(unsigned int i = 3; i < this->pixels.size(); i++)
	{
		int pixel = this->pixels[i]; 
		average += pixel;
	}
	average /= (total_Num_Pixels);
	return 0;
}


//Used for Debugging;
void image::printNewPixels()
{
	for(unsigned int i = 0; i < this->scaledPixels.size();i++)
	{
		std::cout<< "Pixel: " << this->scaledPixels[i] <<std::endl;
	}
}

int image::rescale()
{

for(unsigned int i = 3; i < this->pixels.size(); i++)
{
	int pixel  = this->pixels[i];
	double pix = pixel - min;
	double den = max   - min;
	if(den == 0)
	{
		return -1;
	}
	double newPix = (255.0 * pix) / den;
	int newPixel  = round(newPix);
	
	this->scaledPixels.push_back(newPixel);
}

return 0;

}

image* image::createFrame(image*& inImage, int frameNumber,int totalFrames)
{
	image *newFrame = new image();
	newFrame->width = inImage->width;
	newFrame->height = inImage->height;
	newFrame->MAX_PIXEL_VAL = 255;
	for(unsigned int i = 3; i < inImage->pixels.size();i++)
	{
		int img1Pixel = this->pixels[i];
		int img2Pixel = inImage->pixels[i];
		double newPix = img1Pixel + ((frameNumber/(totalFrames + 1.0)) * (img2Pixel - img1Pixel));

		int newPixel = round(newPix);

		newFrame->scaledPixels.push_back(newPixel);
	}
	
	return newFrame;
}

int image::writeAsciiFile(std::ostream& outFile)
{
	if(!outFile)
	{
		return -1;
	}

	outFile << "P2" <<std::endl;
	outFile << this->width << " " << this->height <<std::endl;
	outFile << "255" << std::endl;
	
	int colCount = 0;
	for(unsigned int i = 0; i < this->scaledPixels.size(); i++)
	{
		if(colCount == 19)
		{
			colCount = 0;
			outFile << this->scaledPixels[i] << std::endl;
		}else
		{
			outFile << this->scaledPixels[i] << " " ;
			colCount++;
		}
		
	}
	
	return 0;
}

int image::writeBinaryFile(std::ostream& outFile)
{
	//reverse write operation and store in array then write everything out to the file
	int newMaxVal = 255;
	
	if(!outFile)
	{
		return -1;
	}
		outFile << "P5";
		
		this->binaryPixels.push_back((this->width >> 24) & 0xff);
		this->binaryPixels.push_back((this->width >> 16) & 0xff);
		this->binaryPixels.push_back((this->width >> 8) & 0xff);
		this->binaryPixels.push_back(this->width & 0xff);

		this->binaryPixels.push_back((this->height >> 24) & 0xff);
		this->binaryPixels.push_back((this->height >> 16) & 0xff);
		this->binaryPixels.push_back((this->height >> 8) & 0xff);
		this->binaryPixels.push_back (this->height & 0xff);

		this->binaryPixels.push_back (0);
		this->binaryPixels.push_back (0);
		this->binaryPixels.push_back (0);
		this->binaryPixels.push_back (newMaxVal);

		//outFile.write((char*)&width,         sizeof(int));
		//outFile.write((char*)&height,        sizeof(int));
		//outFile.write((char*)&newMaxVal,     sizeof(int));

		for(unsigned int i = 0; i < this->scaledPixels.size(); i++)
	{
			this->binaryPixels.push_back(this->scaledPixels[i]);
			//outFile.write((char*)&scaledPixels[i], sizeof(unsigned char));
	}
	for(unsigned int i = 0; i < this->binaryPixels.size();i++)
	{
		outFile.write((char*)&this->binaryPixels[i], sizeof(unsigned char));
		//std::cout << "binaryPixels: " << binaryPixels[i] << std::endl;
	}
	
return 0;


}


std::string image::getExtension(std::string& fileName)
{
	std::string extension = fileName.substr(fileName.find("."), fileName.length());
	return extension;
}


int image::readBinaryFile(std::istream& inFile)
{

  //std::vector <int> binaryValues;
  while(!inFile.eof())
  {
    unsigned c = inFile.get();
    this->pixels.push_back(c);
  }
  this->pixels.erase(this->pixels.begin() + this->pixels.size() - 1);
  
  this->pixels.erase(this->pixels.begin(),     this->pixels.begin() + 2);
  this->pixels[0] = (this->pixels[0] & 0xff) << 24|(this->pixels[1] & 0xff) <<16|(this->pixels[2] & 0xff)<<8|(this->pixels[3] & 0xff);	
  this->pixels.erase(this->pixels.begin() + 1, this->pixels.begin() + 4);
 
  this->pixels[1] = (this->pixels[1] & 0xff) << 24|(this->pixels[2] & 0xff )<<16|(this->pixels[3] & 0xff)<<8|(this->pixels[4] & 0xff);	
  this->pixels.erase(this->pixels.begin() + 2, this->pixels.begin() + 5);
  this->pixels[2] = (this->pixels[2] & 0xff) << 24|(this->pixels[3] & 0xff )<<16|(this->pixels[4] & 0xff)<<8|(this->pixels[5] & 0xff);
  this->pixels.erase(this->pixels.begin() + 3, this->pixels.begin() + 6);

return 0;
}



