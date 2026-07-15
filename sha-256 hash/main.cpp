#include <openssl/evp.h>
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
struct EVP_MD_CTX_DELETER {
	void operator()(EVP_MD_CTX* ctx) const {
		if (ctx) EVP_MD_CTX_free(ctx);
	}
};
using UniqueEVP_MD_CTX = std::unique_ptr<EVP_MD_CTX, EVP_MD_CTX_DELETER>;
std::string sha_256(const std::string& input) {
	UniqueEVP_MD_CTX ctx(EVP_MD_CTX_new());
	if (!ctx) throw std::runtime_error("Error create ctx");
	if (EVP_DigestInit_ex(ctx.get(), EVP_sha256(), nullptr) != 1) throw std::runtime_error("Error DigestInit");
	if (EVP_DigestUpdate(ctx.get(), input.c_str(), input.length()) != 1) throw std::runtime_error("Error DigestUpdate");
	unsigned char hash[EVP_MAX_MD_SIZE];
	unsigned int hash_len = 0;
	if (EVP_DigestFinal(ctx.get(), hash, &hash_len) != 1) throw std::runtime_error("Error DigestFinal");
	std::stringstream ss;
	for (unsigned int i = 0; i < hash_len; i++) {
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
	}
	return ss.str();
}
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