#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define FileName "Cat.bmp" 
#define red "red.bmp"
#define green "green.bmp"
#define blue "blue.bmp"
#define gray "grayscale.bmp"
#define black_white "black&white.bmp"
#define blur "blur.bmp"
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	struct rgb_data {
		float r, g, b;
	};
	int originalImage();
	int rgbchannelImage();
	int grayscaleImage();
	int bwImage();
	int blurred();

	if (rgbchannelImage() == 0) {
		return 0;
	}
	if (grayscaleImage() == 0) {
		return 0;
	}
	if (bwImage() == 0) {
		return 0;
	}
	if (blurred() == 0) {
		return 0;
	}
}

int rgbchannelImage() {

	FILE *FileInput = fopen(FileName, "rb");
	FILE *FileOutput1 = fopen(red, "wb"); 
	FILE *FileOutput2 = fopen(green, "wb");
	FILE *FileOutput3 = fopen(blue, "wb");
	if (!FileInput || !FileOutput1)
	{
		printf("File error.\n");
		return 0;
	}

	unsigned char header[122];
	fread(&header, sizeof(unsigned char), 122, FileInput);
	fwrite(&header, sizeof(unsigned char), 122, FileOutput1);
	fwrite(&header, sizeof(unsigned char), 122, FileOutput2);
	fwrite(&header, sizeof(unsigned char), 122, FileOutput3);


	int width = *(int*)&header[18];
	int height = abs(*(int*)&header[22]);
	int padding = (width*3) % 4;
	if (padding != 0) {
		padding = 4 - padding;
	}
	unsigned char pad;


	unsigned char pixel[3];
	unsigned char pixelWrite[3];
	fseek(FileInput, 122, SEEK_SET);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			fread(&pixel, sizeof(unsigned char), 3, FileInput); 
			// red
			pixelWrite[0] = 0;
			pixelWrite[1] = 0;
			pixelWrite[2] = pixel[2];
			fwrite(&pixelWrite, (sizeof(unsigned char)), 3, FileOutput1);
			// green
			pixelWrite[0] = 0;
			pixelWrite[1] = pixel[1];
			pixelWrite[2] = 0;
			fwrite(&pixelWrite, (sizeof(unsigned char)), 3, FileOutput2);
			// blue
			pixelWrite[0] = pixel[0];
			pixelWrite[1] = 0;
			pixelWrite[2] = 0;
			fwrite(&pixelWrite, (sizeof(unsigned char)), 3, FileOutput3);
		}
		for (int i = 0; i < padding; i++) {
			fread(&pad, sizeof(unsigned char), 1, FileInput);
			fwrite(&pad, sizeof(unsigned char), 1, FileOutput1);
			fwrite(&pad, sizeof(unsigned char), 1, FileOutput2);
			fwrite(&pad, sizeof(unsigned char), 1, FileOutput3);
		}
		
	}


	int size;
	while (1) {
		size = fread(&pad, 1, 1, FileInput);
		if (size == 0) {
			break;
		}
		else {
			fwrite(&pad, 1, 1, FileOutput1);
			fwrite(&pad, 1, 1, FileOutput2);
			fwrite(&pad, 1, 1, FileOutput3);

		}
	}
	fclose(FileOutput1);
	fclose(FileOutput2);
	fclose(FileOutput3);
	fclose(FileInput);
	return 1;
}

int grayscaleImage() {

	FILE *FileInput = fopen(FileName, "rb");
	FILE *FileOutput = fopen(gray, "wb"); 

	if (!FileInput || !FileOutput)
	{
		printf("File error.\n");
		return 0;
	}

	unsigned char header[54];
	fread(&header, sizeof(unsigned char), 54, FileInput);
	fwrite(&header, sizeof(unsigned char), 54, FileOutput);

	int width = *(int*)&header[18];
	int height = abs(*(int*)&header[22]);
	int stride = (width * 3 + 3) & ~3;
	int padding = stride - (width * 3);
	unsigned char pad;


	unsigned char pixel[3];
	unsigned char pixelWrite[3];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			fread(&pixel, sizeof(unsigned char), 3, FileInput); 
			// red
			pixelWrite[0] = pixelWrite[1] = pixelWrite[2] = ((pixel[0] + pixel[1] + pixel[2]) / 3);
			fwrite(&pixelWrite, (sizeof(unsigned char)), 3, FileOutput);


		}
		for (int i = 0; i < padding; i++) {
			fread(&pad, 1, 1, FileInput);
			fwrite(&pad, 1, 1, FileOutput);

		}
		
	}


	int size;
	while (1) {
		size = fread(&pad, 1, 1, FileInput);
	
		if (size == 0) {
			break;
		}
		else {
			fwrite(&pad, 1, 1, FileOutput);


		}
	}
	fclose(FileOutput);
	fclose(FileInput);
	return 1;
}

int bwImage() {

	FILE *FileInput = fopen(FileName, "rb");
	FILE *FileOutput = fopen(black_white, "wb"); 
	
	if (!FileInput || !FileOutput)
	{
		printf("File error.\n");
		return 0;
	}

	unsigned char header[54];
	fread(&header, sizeof(unsigned char), 54, FileInput);
	fwrite(&header, sizeof(unsigned char), 54, FileOutput);

	int width = *(int*)&header[18];
	int height = abs(*(int*)&header[22]);
	int stride = (width * 3 + 3) & ~3;
	int padding = stride - (width * 3);
	unsigned char pad;

	
	unsigned char pixel[3];
	unsigned char pixelWrite[3];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			fread(&pixel, sizeof(unsigned char), 3, FileInput); 
	
			if (((pixel[0] + pixel[1] + pixel[2]) / 3) > 127) {
				pixelWrite[0] = pixelWrite[1] = pixelWrite[2] = 255;
			}
			else {
				pixelWrite[0] = pixelWrite[1] = pixelWrite[2] = 0;
			}




			fwrite(&pixelWrite, (sizeof(unsigned char)), 3, FileOutput);


		}
		for (int i = 0; i < padding; i++) {
			fread(&pad, 1, 1, FileInput);
			fwrite(&pad, 1, 1, FileOutput);

		}
	
	}


	int size;
	while (1) {
		size = fread(&pad, 1, 1, FileInput);
	
		if (size == 0) {
			break;
		}
		else {
			fwrite(&pad, 1, 1, FileOutput);


		}
	}
	fclose(FileOutput);
	fclose(FileInput);
	return 1;
}
int blurred() {
	FILE *fName;
	fName = fopen(FileName, "rb");
	FILE *output;
	output = fopen(blur, "wb");
	for (int i = 0; i < 14; i++)
	{
		int store;
		store = fgetc(fName);
		fputc(store, output);
	}
	int Dibsize = fgetc(fName);
	fputc(Dibsize, output);
	for (int i = 0; i < Dibsize - 1; i++)
	{
		int store;
		store = fgetc(fName);
		fputc(store, output);
	}
	fseek(fName, 18, SEEK_SET);
	unsigned short width = fgetc(fName);
	width += fgetc(fName) << 8;
	fseek(fName, 22, SEEK_SET);
	unsigned short height = fgetc(fName);
	height += fgetc(fName) << 8;
	unsigned short padding = (width * 3) % 4;
	if (padding != 0)
	{
		padding = 4 - padding;
	}

	unsigned char map[height][width * 3 + padding];
	unsigned i = 0;
	unsigned j = 0;
	int save;
	fseek(fName, Dibsize + 14, SEEK_SET);
	while (!feof(fName))
	{
		if (i != width * 3 + padding)
		{
			save = fgetc(fName);
			map[j][i] = save;
			i++;
		}
		else
		{
			i = 0;
			j++;
		}
	}
	i = 0;
	j = 0;
	int maxrowvalue;
	int maxcolumnvalue;
	for (; j < height; j++)
	{
		i = 0;
		for (; i < width * 3 + padding; i += 3)
		{
			int areacounter = 0;
			int red0 = 0;
			int green0 = 0;
			int blue0 = 0;
			int columnindexsave;
			int columnindex = i - 9;
			int rowindex = j - 3;
			columnindexsave = columnindex;

			maxrowvalue = j + 4;
			maxcolumnvalue = (i + 12);
		
			if (rowindex < 0)
			{
				rowindex = 0;
			}
			if (columnindex < 0)
			{
				columnindex = 0;
				columnindexsave = 0;
			}

			if (rowindex > height - 7)
			{
				maxrowvalue = height;
			}
			if (columnindex > (width - 7) * 3 + padding)
			{
				maxcolumnvalue = (width) * 3 + padding;
			}
			if (i >= width * 3 - 1)
			{
				for (int i = 0; i < padding; i++)
				{
					fputc(0, output);
				}
				break;
			}
			for (; rowindex < maxrowvalue; rowindex++)
			{
				columnindex = columnindexsave;
				for (; columnindex < maxcolumnvalue;)
				{
					red0 += map[rowindex][columnindex];
					columnindex++;
					green0 += map[rowindex][columnindex];
					columnindex++;
					blue0 += map[rowindex][columnindex];
					columnindex++;
					areacounter++;
				}
			}
			red0 /= areacounter;
			green0 /= areacounter;
			blue0 /= areacounter;
			fputc(red0, output);
			fputc(green0, output);
			fputc(blue0, output);
		}
	}
	fclose(fName);
	fclose(output);
	return 0; 
}
