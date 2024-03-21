#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>>

struct task
{
	std::string task_name = "Unknown";
	std::time_t task_begin = 0;
	std::time_t task_end = 0;
};

void print_tasks(task& current_task) {
	double task_time = current_task.task_end - current_task.task_begin;
	int hours, minutes, seconds;
	hours = task_time / 3600;				//При необходимости аналогично добавляются дни, месяцы... века
	minutes = (int)task_time % 3600 / 60;
	seconds = (int)task_time % 3600 % 60;
	if (hours > 0)
		std::cout << hours << " hours, ";
	if (minutes > 0)
		std::cout << minutes << " minutes, ";
	std::cout << seconds << " seconds were spent on task " << current_task.task_name << std::endl;
}


int main()
{
	std::cout << "***************** Implementation of the time tracking program *****************\n\n";

	std::string command;
	std::vector<task> tasks;

	while (true) {
		std::cout << "\nEnter command (begin, end, status, exit): ";
		std::cin >> command;
		if (command == "begin") {
			if ((tasks.size() > 0) && (tasks[tasks.size() - 1].task_end == 0)) {	//Завершаем последнюю текущую задачу
				tasks[tasks.size() - 1].task_end = std::time(nullptr);
			}
			//Начинаем новую задачу
			task new_task;
			std::cout << "Input name of new task: ";
			std::cin >> new_task.task_name;
			new_task.task_begin = std::time(nullptr);
			tasks.push_back(new_task);
		}
		else if (command == "end") {	//Завершаем последнюю текущую задачу, если она есть и не завершена
			if ((tasks.size() > 0) && (tasks[tasks.size() - 1].task_end == 0))
				tasks[tasks.size() - 1].task_end = std::time(nullptr);
		}
		else if (command == "status") {	//Выводим данные о задачах
			for (int i = 0; i < tasks.size() - 1; i++) {
				print_tasks(tasks[i]);	//всех, кроме последней
			}
			if (tasks[tasks.size() - 1].task_end == 0) //последнюю проверяем на завершённость
				std::cout << "Current task - " << tasks[tasks.size() - 1].task_name << std::endl;
			else
				print_tasks(tasks[tasks.size() - 1]);
		}
		else if (command == "exit") {
			std::cout << "\n\n";
			return 0;
		}
		else
			std::cout << "Invalid command\n\n";
	}
}