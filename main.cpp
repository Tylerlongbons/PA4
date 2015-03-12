//Tyler Longbons
//Assignment: PA4


#include <cctype>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#include "image.h"	



	int main(int argc, char* argv[]){
		if(argc != 4)
		{
		return -1;	
		}

		/*Revisit to dynamically allocate images*/
		/////////////////////////////////////////
		std::vector <image*> imagesArray;
		imagesArray.push_back(new image());
		imagesArray[0]->imgFileName = argv[1];
		imagesArray.push_back(new image());
		imagesArray[1]->imgFileName = argv[2];




	for(unsigned int i = 0; i < imagesArray.size(); i++)
	{

		

		//if(strcmp(argv[1],argv[3]) == 0)
		//{
			//std::cout<< "Args are the same"<<std::endl;
		//	return -1;
		//}

		std::ifstream inFile;//(argv[1]);
		inFile.open(imagesArray[i]->imgFileName);
		std::string fileType = imagesArray[i]->getFileType(inFile);
		inFile.close();
		//std::ifstream inFile2(argv[1]);
		inFile.open(imagesArray[i]->imgFileName);


		if(fileType == "ascii")
		{
			
			if(imagesArray[i]->readAsciiFile(inFile) == -1)
			{
				//std::cout<< "Read File Failed"<<std::endl;
				return -1;
			}
			inFile.close();
			if(imagesArray[i]->processAsciiFileData() == -1)
			{
				//std::cout<< "Process file failed: "<< i<<std::endl;
				return -1;
			}

			
			

		}else if(fileType == "binary")
		{
			
			std::ifstream binFile(imagesArray[i]->imgFileName);
			if(imagesArray[i]->readBinaryFile(binFile) == -1)
			{
				//std::cout<<"BIN ERROR";
					return -1;
			}
			binFile.close();
		}else
		{
			return -1;
		}


		if(imagesArray[i]->processHeaderData() == -1)
			{
				//std::cout << "Process Header Failed" << std::endl;
				return -1;
			}

		if(imagesArray[i]->validatePixels() == -1)
			{
				//std::cout << "Bad Pixels" << std::endl;
				return -1;
			}
			imagesArray[i]->findMin();
			imagesArray[i]->findAverage();
			imagesArray[i]->findMax();
		
			//if(imagesArray[i].rescale() == -1)
			//{
				//std::cout << "Failed to rescale" << std::endl;
			//	return -1;
			//}
		}//end for
		
		//Compare image Sizes
		if(imagesArray[0]->width != imagesArray[1]->width)
		{
			//std::cout<<"Widths dont match" << std::endl;
			return -1;
		}
		if(imagesArray[0]->height != imagesArray[1]->height)
		{
			//std::cout<<"Widths dont match" << std::endl;
			return -1;
		}


		//start processing frames
		int numFrames = atoi(argv[3]);
		if(numFrames < 0)
		{
			//std::cout << "invalid number of frames" << std::endl;
			return -1;
		}

		std::string fullOutFileName = argv[1];
		std::string extension = imagesArray[0]->getExtension(fullOutFileName);


		for(int i = 0; i <= numFrames + 1; i++)
		{
			imagesArray.push_back(imagesArray[0]->createFrame(imagesArray[1], i, numFrames));
		}

		std::ifstream inFile;//(argv[1]);
		inFile.open(imagesArray[0]->imgFileName);
		std::string fileType = imagesArray[0]->getFileType(inFile);
		inFile.close();

	for(unsigned int i = 2; i < imagesArray.size(); i++)
	{
		std::ostringstream convert;
		convert << i - 2;
		std::string outputFileName = convert.str();
		//strcat(outputFileName, extension);
		outputFileName = outputFileName + ".pgm";
		if(fileType == "ascii")
			{
				std::ofstream outFile;
				outFile.open(outputFileName.c_str());
					if(imagesArray[i]->writeAsciiFile(outFile) == -1)
					{
						//std::cout<<"outFile ascii failed" <<std::endl;
						return -1;
					}
					outFile.close();
			}else
			{
				std::ofstream outFile(outputFileName.c_str(), std::ios::binary | std::ios::out);
				if(imagesArray[i]->writeBinaryFile(outFile) == -1)
				{
					//std::cout <<"outfile binary failed" << std::endl;
					return -1;
				}
				outFile.close();
			}
		}	

		

		//Clean up memory
		for(unsigned int i = 0; i < imagesArray.size(); i++)
		{
			delete(imagesArray[i]);
		}
		
	
	
	return 0;


	}
