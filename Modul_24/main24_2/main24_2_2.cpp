#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>>
#include <sstream>

struct my_friends
{
	std::string name = "Unknown";
	std::tm birthday;
};

void reminder(std::vector<my_friends>& vec) {
	std::time_t tt = std::time(nullptr);
	std::tm today = *std::localtime(&tt);
	//При наличии сегодня именинников выведем соответствующее сообщение
	std::vector<std::string> bd_today;
	for (int i = 0; i < vec.size(); i++) {
		if ((vec[i].birthday.tm_mon == today.tm_mon) && (vec[i].birthday.tm_mday == today.tm_mday))
			bd_today.push_back(vec[i].name);
	}
	std::cout << "Today is a birthday party: ";
	for (int i = 0; i < bd_today.size(); i++) {
		std::cout << bd_today[i] << " ";
	}
	std::cout << std::endl << std::endl;

	//Найдем ближайший день рождения и выведем напоминалку
	std::vector<my_friends> bd_near;
	my_friends near;
	int k = 0;
	//Сначала поищем первый день рождения после сегодня и вставим его в вектор
	for (int j = 0; j < vec.size(); j++) {
		k = j;
		if (((vec[j].birthday.tm_mon == today.tm_mon) && (vec[j].birthday.tm_mday > today.tm_mday)) ||
			(vec[j].birthday.tm_mon > today.tm_mon)) {
			near = vec[j];
			bd_near.push_back(near);
			k++; //Будем отталкиваться от k в следующем цикле
			break;
		}
	}
	//С этим днем будем сравнивать все остальные
	if (bd_near.size() > 0) {
		for (int i = k; i < vec.size(); i++) {
			if ((vec[i].birthday.tm_mon == near.birthday.tm_mon) && (vec[i].birthday.tm_mday == near.birthday.tm_mday))
				bd_near.push_back(vec[i]);
			else if ((((vec[i].birthday.tm_mon == today.tm_mon) && (vec[i].birthday.tm_mday > today.tm_mday)) ||
				(vec[i].birthday.tm_mon > today.tm_mon)) && (((vec[i].birthday.tm_mon == near.birthday.tm_mon) &&
					(vec[i].birthday.tm_mday < near.birthday.tm_mday)) || (vec[i].birthday.tm_mon < near.birthday.tm_mon))) {
				near = vec[i];
				bd_near.clear();
				bd_near.push_back(near);
			}
		}
		//Вывод
		std::cout << "The next birthday " << bd_near[0].birthday.tm_mday << '.' << bd_near[0].birthday.tm_mon + 1 <<
			" will be celebrated : ";
		for (int i = 0; i < bd_near.size(); i++) {
			std::cout << bd_near[i].name << " ";
		}
		std::cout << std::endl << std::endl;
	}
}

int main()
{
	std::cout << "***************** Implementation of the time tracking program *****************\n\n";

	std::vector<my_friends> vec_friends;

	while (true) {
		std::cout << "\nEnter your friend's name.\n";
		std::cout << "When finished, enter the 'end' command:\n";
		my_friends new_friend;

		std::cin >> new_friend.name;
		if (new_friend.name == "end") {
			reminder(vec_friends);
			return 0;
		}

		std::cout << "\nEnter your friend's date of birth in the year/month/day format.\n";
		std::string timeStr;
		std::cin >> timeStr;
		std::tm local = {};
		std::istringstream timeStream(timeStr);

		//Проверим валидность введённых данных по дню рождения
		timeStream >> std::get_time(&local, "%Y/%m/%d");

		if (timeStream.fail()) {
			std::cerr << "Invalid birthday format!" << std::endl;
		}
		else {
			new_friend.birthday = local;
			vec_friends.push_back(new_friend);
		}
	}
}