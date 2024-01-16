#include <iostream>
#include <filesystem>
#include <string>

int main()
{
    srand((unsigned int)time(NULL));

    std::string theDir;
    std::cout << "Enter the desired path to rename in (no quotes, just the path directory: ";
    std::getline(std::cin, theDir);
    std::cout << "***WARNING: Program assumes renaming for ALL files in current directory!\n***Please look to your right to confirm this is the right one: ";
    std::cout << theDir << "\n";
    std::cout << "Press type 'y' to continue. Enter anything else to exit...";
    char terminalInput;
    std::cin.get(terminalInput);
    if (terminalInput != 'y') {
        return EXIT_FAILURE;
    }
    std::filesystem::path mydir = theDir;
    if (mydir.empty()) {
        std::cout << "This directory is empty!";
        return EXIT_FAILURE;
    }

    std::vector<std::filesystem::path> unproccessed;
    for (auto currentFile : std::filesystem::directory_iterator(mydir)) {
        if (currentFile.is_regular_file()) {
            unproccessed.push_back(currentFile.path());
        }
    }
    
    for (size_t i = 0; i < unproccessed.size(); i++) {
        std::string temp = std::to_string(std::rand() % 900 + 100) + " ";
        temp += unproccessed.at(i).filename().string();
        std::filesystem::path newPath = mydir / temp;
        std::cout << newPath.string() << "\n";

        try
        {
            std::filesystem::rename(unproccessed.at(i), newPath);
        }
        catch (const std::exception& theError)
        {
            std::cout << theError.what() << "\n";
            return 1;
        }
    }

    std::cout << "File Renaming Success\n";

    return EXIT_SUCCESS;
}
