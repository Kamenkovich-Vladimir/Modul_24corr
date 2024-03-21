#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <thread>

int main()
{
	std::cout << "***************** Implementation of the timer program *****************\n\n";

	std::cout << "Enter the number of minutes and seconds (mm:ss) to be timed on the timer and press Enter: \n";
	std::string time_str;
	std::cin >> time_str;
	if (time_str.length() != 5) {
		std::cerr << "Invalid time format!" << std::endl;
		return -1;
	}

	std::time_t tt = std::time(nullptr);
	std::tm local = *std::localtime(&tt);
	std::istringstream time_stream(time_str);

	//Проверим валидность введённых данных 
	time_stream >> std::get_time(&local, "%M:%S");

	if (time_stream.fail()) {
		std::cerr << "Invalid time format!" << std::endl;
	}
	else {
		std::time_t timer_begin = std::time(nullptr);
		std::time_t timer_end = timer_begin + (60 * local.tm_min) + local.tm_sec;
		double time_diff = difftime(timer_end, timer_begin);

		for (int i = time_diff-1; i >= 0; --i) {
			double sec_diff = 0;
			std::time_t timer_begin = std::time(nullptr);
			while (sec_diff < 1) {
				std::time_t timer_end = std::time(nullptr);
				sec_diff = difftime(timer_end, timer_begin);
			}
			int min = i / 60;
			int sec = i % 60;
	
			std::cout << min << ":" << sec << std::endl;
		}
		std::cout << "Ding-Dong" << std::endl;	//Одновременно с 0:0
	}

}