#include "Application.h"
#include "opencv2/opencv.hpp"
#include "filters.h"

namespace ngp {


	std::string WRONG_ARG_COUNT = "Wrong argument count given, see manual for correct command use";

	const char* MANUAL =
		"Available functions:\n"
		"man : shows this manual\n"
		"exit : closes the application\n"
		"erode <distance> <erosion type [0-2]> : erodes the image\n"
		"dilate <distance> <dilate type [0-2]> : dilates the image\n"
		"resize <new width> <new height> <interpolation type [0-4]> : resize the image\n"
		"canny <minimum threshold value [0-100]>: detects edges of the image\n"
		"\n";

	Application::Application() {
		cv::Mat s_Mat;
		//TODO Init event handlers
	}

	void Application::Run() {
		while (ReadFile());
		std::cout << MANUAL << std::endl;
		cv::imshow("notGimp", s_Mat);
		cv::waitKey(25);
		while (askForFunction()) {
			cv::imshow("notGimp", s_Mat);
			cv::waitKey(25);
		};
	}


	int Application::ReadFile() {
		std::cout << "Please provide an absolute link to an image" << std::endl;
		std::string input;
		std::getline(std::cin, input);

		try {
			std::string image_path = cv::samples::findFile(input);
			s_Mat = cv::imread(image_path, cv::IMREAD_COLOR);
			std::cout << "Image opened at : " << image_path << std::endl;
		}
		catch (cv::Exception) {
			std::cout << "Could not read the image with path: " << input << " please provide valid link" << std::endl;
			return 1;
		}
		return 0;
	}


	int Application::parseCommand(std::vector<std::string> args) {
		if (!args.size()) {
			std::cout << "No arguments were provided" << std::endl;
			return 1;
		}
		std::string func_name = args[0];


		// 
		// 
		// This is where you will implement the calls to the functions
		// check Erode & dialate for examples
		// 

		//Erode
		if (func_name == "erode") {
			if (args.size() == 3) {
				filters::erode(s_Mat, parseInt(args[1]), parseInt(args[2]));
				return 1;
			}
			std::cout << WRONG_ARG_COUNT << std::endl;
			return 1;
		}
		//Dilate
		if (func_name == "dilate") {
			if (args.size() == 3) {
				filters::dilate(s_Mat, parseInt(args[1]), parseInt(args[2]));
				return 1;
			}
			std::cout << WRONG_ARG_COUNT << std::endl;
			return 1;
		}
		//Resize
		if (func_name == "resize") {
			if (args.size() == 4) {
				filters::resize(s_Mat, parseInt(args[1]), parseInt(args[2]), parseInt(args[3]));
				return 1;
			}
			std::cout << WRONG_ARG_COUNT << std::endl;
			return 1;
		}

		//Canny
        if (func_name == "canny") {
        	if (args.size() == 2) {
        		filters::canny(s_Mat, parseInt(args[1]));
        		return 1;
        	}
        	std::cout << WRONG_ARG_COUNT << std::endl;
        	return 1;
        }

		//Manual
		if (func_name == "man") {
			std::cout << MANUAL << std::endl;
			return 1;
		}
		//Exit
		if (func_name == "exit") {
			return 0;
		}
	}

	int Application::parseInt(std::string toBeParsed) {
		try {
			return stoi(toBeParsed);
		}
		catch (std::exception & err) {
			std::cout << "Wrong parameter type provided" << std::endl;
		}
		return 0;
	}



	int Application::askForFunction() {
		std::cout << "Awaiting for function (type 'man' for help)"<< std::endl;
		std::string input;
		std::getline(std::cin, input);

		std::string delimiter = " ";
		std::vector<std::string> args = split(input, delimiter);
		return parseCommand(args);

	}

	std::vector<std::string> Application::split(std::string s, std::string delimiter) {
		size_t pos_start = 0, pos_end, delim_len = delimiter.length();
		std::string token;
		std::vector<std::string> res;

		while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
			token = s.substr(pos_start, pos_end - pos_start);
			pos_start = pos_end + delim_len;
			res.push_back(token);
		}

		res.push_back(s.substr(pos_start));
		return res;
	}


}
