#include <openssl/evp.h>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "sha256logic.h"
int main() {
	std::string path = "data.txt";
	std::string choice;
	std::cout << "Data in .dat or .txt?" << std::endl;
	while (true) {
		std::getline(std::cin, choice);
		if (choice == ".dat" || choice == ".txt") break;
		else std::cout << "Unknown command. Let's try again." << std::endl;
	}

	try {
		std::string data;
		std::cout << "Send anything (word recommended)" << std::endl;
		std::getline(std::cin, data);

		std::string result = sha_256(data);
		std::cout << "Result: " << result << std::endl;

		if (choice == ".dat") {
			std::ofstream datafile("data.dat", std::ios::binary);
			datafile << result;
		}
		if (choice == ".txt") {
			std::ofstream datafile("data.txt");
			datafile << result;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}