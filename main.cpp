#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Header
{
	Header();
	void PrintValues();
	short width, height;
	unsigned int size;

	char idLength, colorMapType, dataTypeCode, colorMapDepth, bitsPerPixel, imageDescriptor;
	short colorMapOrigin, colorMapLength, xOrigin, yOrigin;
};

struct Pixel
{
	Pixel();
	unsigned char blue, green, red;
};

void LoadData(string filename, Header& image, vector<Pixel>& pixels);
void Write(string filename, const Header& header, const vector<Pixel>& pixels);
void EqualityTest(const vector<Pixel>& image1, const vector<Pixel>& image2);
void Multiply(const vector<Pixel>& topLayer, const vector<Pixel>& bottomLayer, vector<Pixel>& newImage);
void Subtract(const vector<Pixel>& topLayer, const vector<Pixel>& bottomLayer, vector<Pixel>& newImage);
void Screen(const vector<Pixel>& topLayer, const vector<Pixel>& bottomLayer, vector<Pixel>& newImage);
void Overlay(const vector<Pixel>& topLayer, const vector<Pixel>& bottomLayer, vector<Pixel>& newImage);

int main()
{
	/*
	Header header1 = Header();
	vector<Pixel> image1;
	LoadData("input/layer1.tga", header1, image1);
	Write("output/test.tga", header1, image1);

	Header header2 = Header();
	vector<Pixel> image2;
	LoadData("output/test.tga", header2, image2);
	EqualityTest(image1, image2);
	*/
	

	//															TASK ONE
	//Loading
	Header layer1Header = Header();
	vector<Pixel> layer1Image;
	LoadData("input/layer1.tga", layer1Header, layer1Image);
	Header pattern1Header = Header();
	vector<Pixel> pattern1Image;
	LoadData("input/pattern1.tga", pattern1Header, pattern1Image);

	//Action
	vector<Pixel> test1Image;
	test1Image.reserve(layer1Image.size());
	Multiply(layer1Image, pattern1Image, test1Image);

	Write("output/part1.tga", layer1Header, test1Image);

	//Test
	Header* exampleHeader = new Header();
	vector<Pixel> exampleImage;
	LoadData("examples/EXAMPLE_part1.tga", *exampleHeader, exampleImage);
	Header* partHeader = new Header();
	vector<Pixel> partImage;
	LoadData("output/part1.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();
	
	
	//															TASK TWO
	//Loading
	Header layer2Header = Header();
	vector<Pixel> layer2Image;
	LoadData("input/layer2.tga", layer2Header, layer2Image);
	Header carHeader = Header();
	vector<Pixel> carImage;
	LoadData("input/car.tga", carHeader, carImage);

	//Action
	vector<Pixel> test2Image;
	test2Image.reserve(layer2Image.size());
	Subtract(layer2Image, carImage, test2Image);

	Write("output/part2.tga", layer2Header, test2Image);

	//Test
	exampleHeader = new Header();
	LoadData("examples/EXAMPLE_part2.tga", *exampleHeader, exampleImage);
	partHeader = new Header();
	LoadData("output/part2.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();
	
	

	//															TASK THREE
	//Loading
	Header pattern2Header = Header();
	vector<Pixel> pattern2Image;
	LoadData("input/pattern2.tga", pattern2Header, pattern2Image);
	Header textHeader = Header();
	vector<Pixel> textImage;
	LoadData("input/text.tga", textHeader, textImage);

	//First action
	vector<Pixel> median1Image;
	median1Image.reserve(layer1Image.size());
	Multiply(layer1Image, pattern2Image, median1Image);

	//Second action
	vector<Pixel> test3Image;
	test3Image.reserve(layer1Image.size());
	Screen(textImage, median1Image, test3Image);

	Write("output/part3.tga", pattern2Header, test3Image);

	//Test
	exampleHeader = new Header();
	LoadData("examples/EXAMPLE_part3.tga", *exampleHeader, exampleImage);
	partHeader = new Header();
	LoadData("output/part3.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();


	//															TASK FOUR
	// Loading
	Header circlesHeader = Header();
	vector<Pixel> circlesImage;
	LoadData("input/circles.tga", circlesHeader, circlesImage);

	//First action
	vector<Pixel> median2Image;
	median2Image.reserve(layer2Image.size());
	Multiply(layer2Image, circlesImage, median2Image);

	//Second action
	vector<Pixel> test4Image;
	test4Image.reserve(median2Image.size());
	Subtract(pattern2Image, median2Image, test4Image);

	Write("output/part4.tga", circlesHeader, test4Image);

	//Test
	exampleHeader = new Header();
	LoadData("examples/EXAMPLE_part4.tga", *exampleHeader, exampleImage);
	partHeader = new Header();
	LoadData("output/part4.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();


	//															TASK FIVE
	//Action
	vector<Pixel> test5Image;
	test5Image.reserve(layer1Image.size());
	Overlay(layer1Image, pattern1Image, test5Image);

	Write("output/part5.tga", layer1Header, test5Image);

	//Test
	exampleHeader = new Header();
	LoadData("examples/EXAMPLE_part5.tga", *exampleHeader, exampleImage);
	partHeader = new Header();
	LoadData("output/part5.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();

	
	//															TASK SIX
	//Action
	vector<Pixel> test6Image;
	test6Image.reserve(carImage.size());
	for (unsigned int i = 0; i < carImage.size(); i++)
	{
		Pixel pixel = Pixel();
		pixel.blue = carImage[i].blue;
		pixel.red = carImage[i].red;
		if ((short)carImage[i].green + 200 < 255)
			pixel.green = carImage[i].green + 200;
		else
			pixel.green = 255;

		test6Image.push_back(pixel);
	}
	Write("output/part6.tga", carHeader, test6Image);

	//Test
	exampleHeader = new Header();
	LoadData("examples/EXAMPLE_part6.tga", *exampleHeader, exampleImage);
	partHeader = new Header();
	LoadData("output/part6.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();


	//															TASK SEVEN
	//Action
	vector<Pixel> test7Image;
	test7Image.reserve(carImage.size());
	for (unsigned int i = 0; i < carImage.size(); i++)
	{
		Pixel pixel = Pixel();
		pixel.green = carImage[i].green;
		if ((short)carImage[i].red * 4 < 255)
			pixel.red = carImage[i].red * 4;
		else
			pixel.red = 255;
		test7Image.push_back(pixel);
	}
	Write("output/part7.tga", carHeader, test7Image);

	//Test
	exampleHeader = new Header();
	LoadData("examples/EXAMPLE_part7.tga", *exampleHeader, exampleImage);
	partHeader = new Header();
	LoadData("output/part7.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();


	//															TASK EIGHT
	//Action
	vector<Pixel> test8Blue, test8Green, test8Red;
	test8Blue.reserve(carImage.size()), test8Green.reserve(carImage.size()), test8Red.reserve(carImage.size());
	for (unsigned int i = 0; i < carImage.size(); i++)
	{
		Pixel bluePixel, greenPixel, redPixel = Pixel();
		bluePixel.blue = carImage[i].blue, bluePixel.green = carImage[i].blue, bluePixel.red = carImage[i].blue;
		greenPixel.blue = carImage[i].green, greenPixel.green = carImage[i].green, greenPixel.red = carImage[i].green;
		redPixel.blue = carImage[i].red, redPixel.green = carImage[i].red, redPixel.red = carImage[i].red;

		test8Blue.push_back(bluePixel), test8Green.push_back(greenPixel), test8Red.push_back(redPixel);
	}
	Write("output/part8_b.tga", carHeader, test8Blue), Write("output/part8_g.tga", carHeader, test8Green), Write("output/part8_r.tga", carHeader, test8Red);

	//Test
	Header* exampleHeader_b = new Header(); 
	Header* exampleHeader_g = new Header(); 
	Header* exampleHeader_r = new Header();
	vector<Pixel> exampleImage_b, exampleImage_g, exampleImage_r;
	LoadData("examples/EXAMPLE_part8_b.tga", *exampleHeader_b, exampleImage_b), LoadData("examples/EXAMPLE_part8_g.tga", *exampleHeader_g, exampleImage_g), LoadData("examples/EXAMPLE_part8_r.tga", *exampleHeader_r, exampleImage_r);
	Header* partHeader_b = new Header();
	Header* partHeader_g = new Header();
	Header* partHeader_r = new Header();
	vector<Pixel> partImage_b, partImage_g, partImage_r;
	LoadData("output/part8_b.tga", *partHeader_b, partImage_b), LoadData("output/part8_g.tga", *partHeader_g, partImage_g), LoadData("output/part8_r.tga", *partHeader_r, partImage_r);
	EqualityTest(exampleImage_b, partImage_b), EqualityTest(exampleImage_g, partImage_g), EqualityTest(exampleImage_r, partImage_r);

	delete exampleHeader_b, partHeader_b, exampleHeader_g, partHeader_g, exampleHeader_r, partHeader_r;
	exampleImage_b.clear(), partImage_b.clear(), exampleImage_g.clear(), partImage_g.clear(), exampleImage_r.clear(), partImage_r.clear();


	//																TASK NINE
	//Loading
	Header layer_redHeader, layer_greenHeader, layer_blueHeader = Header();
	vector<Pixel> layer_redImage, layer_greenImage, layer_blueImage;
	LoadData("input/layer_red.tga", layer_redHeader, layer_redImage), LoadData("input/layer_green.tga", layer_greenHeader, layer_greenImage), LoadData("input/layer_blue.tga", layer_blueHeader, layer_blueImage);

	//Action
	vector<Pixel> test9Image;
	test9Image.reserve(layer_redImage.size());
	for (unsigned int i = 0; i < layer_redImage.size(); i++)
	{
		Pixel pixel = Pixel();
		pixel.blue = layer_blueImage[i].blue;
		pixel.green = layer_greenImage[i].green;
		pixel.red = layer_redImage[i].red;

		test9Image.push_back(pixel);
	}
	Write("output/part9.tga", layer_redHeader, test9Image);

	//Test
	exampleHeader = new Header();
	LoadData("examples/EXAMPLE_part9.tga", *exampleHeader, exampleImage);
	partHeader = new Header();
	LoadData("output/part9.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();


	//																TASK TEN
	//Loading
	Header text2Header = Header();
	vector<Pixel> text2Image;
	LoadData("input/text2.tga", text2Header, text2Image);

	//Action
	vector<Pixel> test10Image;
	test10Image.reserve(text2Image.size());
	for (int i = (text2Image.size()-1); i >= 0; i--)
	{
		Pixel pixel = Pixel();
		pixel.blue = text2Image[i].blue;
		pixel.green = text2Image[i].green;
		pixel.red = text2Image[i].red;

		test10Image.push_back(pixel);
	}
	Write("output/part10.tga", text2Header, test10Image);

	//Test
	exampleHeader = new Header();
	LoadData("examples/EXAMPLE_part10.tga", *exampleHeader, exampleImage);
	partHeader = new Header();
	LoadData("output/part10.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();

	
	//																EXTRA CREDIT
	Header extraCreditHeader = Header();
	extraCreditHeader.height = 1024, extraCreditHeader.width = 1024, extraCreditHeader.size = 1024 * 1024;
	vector<Pixel> extraCreditImage;
	extraCreditImage.reserve(extraCreditHeader.size);
	
	for (unsigned int i = 0; i < extraCreditHeader.size; i++)
	{
		Pixel pixel = Pixel();
		extraCreditImage.push_back(pixel);
	}

	unsigned int k = 0;
	for (unsigned int i = 0; i < 512; i++)
	{
		for (unsigned int j = 512 * i; j < (512 * i) + 512; j++)
		{
			Pixel pixel = Pixel();
			pixel.blue = textImage[k].blue;
			pixel.green = textImage[k].green;
			pixel.red = textImage[k].red;

			extraCreditImage[(512 * i) + j] = pixel;
			k++;
		}
	}
	k = 0;

	for (unsigned int i = 0; i < 512; i++)
	{
		for (unsigned int j = (512 * i) + 512; j < (512 * i) + 1024; j++)
		{
			Pixel pixel = Pixel();
			pixel.blue = pattern1Image[k].blue;
			pixel.green = pattern1Image[k].green;
			pixel.red = pattern1Image[k].red;

			extraCreditImage[(512 * i) + j] = pixel;
			k++;
		}
	}
	k = 0;

	for (unsigned int i = 512; i < 1024; i++)
	{
		for (unsigned int j = 512 * i; j < (512 * i) + 512; j++)
		{
			Pixel pixel = Pixel();
			pixel.blue = carImage[k].blue;
			pixel.green = carImage[k].green;
			pixel.red = carImage[k].red;

			extraCreditImage[(512 * i) + j] = pixel;
			k++;
		}
	}
	k = 0;

	for (unsigned int i = 512; i < 1024; i++)
	{
		for (unsigned int j = (512 * i) + 512; j < (512 * i) + 1024; j++)
		{
			Pixel pixel = Pixel();
			pixel.blue = circlesImage[k].blue;
			pixel.green = circlesImage[k].green;
			pixel.red = circlesImage[k].red;

			extraCreditImage[(512 * i) + j] = pixel;
			k++;
		}
	}
	Write("output/extracredit.tga", extraCreditHeader, extraCreditImage);

	//Test
	exampleHeader = new Header();
	LoadData("examples/EXAMPLE_extracredit.tga", *exampleHeader, exampleImage);
	partHeader = new Header();
	LoadData("output/extracredit.tga", *partHeader, partImage);
	EqualityTest(exampleImage, partImage);

	delete exampleHeader, partHeader;
	exampleImage.clear(), partImage.clear();

	return 0;
}	

void Multiply(const vector<Pixel>& topLayer, const vector<Pixel>& bottomLayer, vector<Pixel>& newImage)
{
	for (unsigned int i = 0; i < topLayer.size(); i++)
	{
		Pixel pixel = Pixel();
		float blue = (((float)topLayer[i].blue / 255) * ((float)bottomLayer[i].blue / 255)) * 255;
		pixel.blue = blue + .5f;
		float green = (((float)topLayer[i].green / 255) * ((float)bottomLayer[i].green / 255)) * 255;
		pixel.green = green + .5f;
		float red = (((float)topLayer[i].red / 255) * ((float)bottomLayer[i].red / 255)) * 255;
		pixel.red = red + .5f;

		newImage.push_back(pixel);
	}
}

void Subtract(const vector<Pixel>& topLayer, const vector<Pixel>& bottomLayer, vector<Pixel>& newImage)
{
	for (unsigned int i = 0; i < bottomLayer.size(); i++)
	{
		Pixel pixel = Pixel();
		if ((int)bottomLayer[i].blue - (int)topLayer[i].blue > 0)
			pixel.blue = bottomLayer[i].blue - topLayer[i].blue;
		else
			pixel.blue = 0;

		if ((int)bottomLayer[i].green - (int)topLayer[i].green > 0)
			pixel.green = bottomLayer[i].green - topLayer[i].green;
		else
			pixel.green = 0;

		if ((int)bottomLayer[i].red - (int)topLayer[i].red > 0)
			pixel.red = bottomLayer[i].red - topLayer[i].red;
		else
			pixel.red = 0;

		newImage.push_back(pixel);
	}
}

void Screen(const vector<Pixel>& topLayer, const vector<Pixel>& bottomLayer, vector<Pixel>& newImage)
{
	for (unsigned int i = 0; i < topLayer.size(); i++)
	{
		Pixel pixel = Pixel();
		float blue = (1 - ((1 - ((float)topLayer[i].blue / 255)) * (1 - (((float)bottomLayer[i].blue) / 255)))) * 255;
		pixel.blue = blue + .5f;
		float green = (1 - ((1 - ((float)topLayer[i].green / 255)) * (1 - (((float)bottomLayer[i].green) / 255)))) * 255;
		pixel.green = green + .5f;
		float red = (1 - ((1 - ((float)topLayer[i].red / 255)) * (1 - (((float)bottomLayer[i].red) / 255)))) * 255;
		pixel.red = red + .5f;

		newImage.push_back(pixel);
	}
}

void Overlay(const vector<Pixel>& topLayer, const vector<Pixel>& bottomLayer, vector<Pixel>& newImage)
{
	for (unsigned int i = 0; i < topLayer.size(); i++)
	{
		Pixel pixel = Pixel();

		//blue
		if ((float)bottomLayer[i].blue < 127.5f)
		{
			float blue = (2 * (((float)topLayer[i].blue / 255) * ((float)bottomLayer[i].blue / 255))) * 255;
			if (blue < 255)
				pixel.blue = blue + .5f;
			else
				pixel.blue = 255;
		}
		else
		{
			float blue = (1 - (2 * ((1 - ((float)topLayer[i].blue / 255)) * (1 - (((float)bottomLayer[i].blue) / 255))))) * 255;
			if (blue < 255)
				pixel.blue = blue + .5f;
			else
				pixel.blue = 255;
		}

		//green
		if ((float)bottomLayer[i].green < 127.5f)
		{
			float green = (2 * (((float)topLayer[i].green / 255) * ((float)bottomLayer[i].green / 255))) * 255;
			if (green < 255)
				pixel.green = green + .5f;
			else
				pixel.green = 255;
		}
		else
		{
			float green = (1 - (2 * ((1 - ((float)topLayer[i].green / 255)) * (1 - (((float)bottomLayer[i].green) / 255))))) * 255;
			if (green < 255)
				pixel.green = green + .5f;
			else
				pixel.green = 255;
		}

		//red
		if ((float)bottomLayer[i].red < 127.5f)
		{
			float red = (2 * (((float)topLayer[i].red / 255) * ((float)bottomLayer[i].red / 255))) * 255;
			if (red < 255)
				pixel.red = red + .5f;
			else
				pixel.red = 255;
		}
		else
		{
			float red = (1 - (2 * ((1 - ((float)topLayer[i].red / 255)) * (1 - (((float)bottomLayer[i].red) / 255))))) * 255;
			if (red < 255)
				pixel.red = red + .5f;
			else
				pixel.red = 255;
		}
		
		newImage.push_back(pixel);
	}
}

void LoadData(string filename, Header& image, vector<Pixel>& pixels)
{
	ifstream file(filename, ios_base::binary);
	if (file.is_open())
		cout << "File \"" << filename << "\" opened.\n" << endl;
	else
		cout << "File \"" << filename << "\"  failed to open.\n" << endl;
	
	file.seekg(12);
	file.read((char*)&image.width, 2);
	file.read((char*)&image.height, 2);
	image.size = image.width * image.height;
	pixels.reserve(image.size);

	file.seekg(18);
	for (unsigned int i = 0; i < image.size; i++)
	{
		Pixel pixel = Pixel();

		file.read((char*)&pixel.blue, 1);
		file.read((char*)&pixel.green, 1);
		file.read((char*)&pixel.red, 1);

		pixels.push_back(pixel);
	}

	file.close();
}

void Write(string filename, const Header& header, const vector<Pixel>& pixels)
{
	ofstream file(filename, ios_base::binary);
	if (file.is_open())
	{
		file.write(&header.idLength, 1);
		file.write(&header.colorMapType, 1);
		file.write(&header.dataTypeCode, 1);
		file.write((char*)&header.colorMapOrigin, 2);
		file.write((char*)&header.colorMapLength, 2);
		file.write(&header.colorMapDepth, 1);
		file.write((char*)&header.xOrigin, 2);
		file.write((char*)&header.yOrigin, 2);
		file.write((char*)&header.width, 2);
		file.write((char*)&header.height, 2);
		file.write(&header.bitsPerPixel, 1);
		file.write(&header.imageDescriptor, 1);
		for (unsigned int i = 0; i < pixels.size(); i++)
		{
			file.write((char*)&pixels[i].blue, 1);
			file.write((char*)&pixels[i].green, 1);
			file.write((char*)&pixels[i].red, 1);
		}
	}
	file.close();
}

void EqualityTest(const vector<Pixel>& image1, const vector<Pixel>& image2)
{
	bool testPassed = true;
	for (unsigned int i = 0; i < image1.size(); i++)
	{
		if (image1[i].blue != image2[i].blue ||
			image1[i].green != image2[i].green ||
			image1[i].red != image2[i].red)
		{
			testPassed = false;
			cout << "Pixels not equal at " << i << endl;
			cout << "---------------------" << endl;
			cout << "Original blue: " << (int)image1[i].blue << endl;
			cout << "Original green: " << (int)image1[i].green << endl;
			cout << "Original red: " << (int)image1[i].red << endl;
			cout << "Test blue: " << (int)image2[i].blue << endl;
			cout << "Test green: " << (int)image2[i].green << endl;
			cout << "Test red: " << (int)image2[i].red << endl;
		}
	}
	
	if (testPassed)
		cout << "IMAGES ARE EQUAL!\n" << endl;
	else
		cout << "IMAGES ARE NOT EQUAL.\n" << endl;
}

Header::Header()
{
	width = 0;
	height = 0;
	colorMapOrigin = 0;
	colorMapLength = 0;
	xOrigin = 0;
	yOrigin = 0;
	idLength = 0;
	colorMapType = 0;
	dataTypeCode = 0;
	colorMapDepth = 0;
	bitsPerPixel = 0;
	imageDescriptor = 0;
	size = 0;
}

void Header::PrintValues()
{
	cout << "Width: " << width << endl;
	cout << "Height: " << height << endl;
	cout << "Size: " << size << endl;
}

Pixel::Pixel()
{
	blue = 0;
	green = 0;
	red = 0;
}
