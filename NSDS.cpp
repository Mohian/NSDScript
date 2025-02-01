#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <vector>

namespace fs = std::filesystem;

void download_file(const std::string& url, const std::string& filename) {
    std::string downloads_path = fs::path(getenv("USERPROFILE")) / "Downloads";
    std::string filepath = downloads_path + "\\" + filename;

    std::string command = "curl -L --retry 3 --retry-delay 5 -o \"" + filepath + "\" " + url;
    if (std::system(command.c_str()) == 0) {
        std::cout << filename << " downloaded successfully to " << downloads_path << ".\n";
    } else {
        std::cerr << "Failed to download " << filename << ".\n";
    }
}

void process_downloads(const std::vector<std::pair<std::string, std::string>>& downloads) {
    char choice;
    for (const auto& [name, url] : downloads) {
        do {
            std::cout << "Download " << name << "? (y/n): ";
            std::cin >> choice;
            choice = std::tolower(choice);
        } while (choice != 'y' && choice != 'n');

        if (choice == 'y') {
            std::string filename = url.substr(url.find_last_of('/') + 1);
            download_file(url, filename);
        } else {
            std::cout << "Skipping " << name << ".\n";
        }
    }
    std::cout << "All tasks completed.\n";
}

int main() {
    std::string file_path = "software_list.txt";
    std::ifstream file(file_path);

    if (!file) {
        std::cerr << "Error: " << file_path << " not found!\n";
        return 1;
    }

    std::vector<std::pair<std::string, std::string>> downloads;
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find('=');
        if (pos != std::string::npos) {
            downloads.emplace_back(line.substr(0, pos), line.substr(pos + 1));
        }
    }

    if (downloads.empty()) {
        std::cerr << "No valid download entries found in " << file_path << "!\n";
        return 1;
    }

    process_downloads(downloads);
    return 0;
}
