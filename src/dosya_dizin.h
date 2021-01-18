#ifndef GET_DIRECTORIES_H
#define GET_DIRECTORIES_H

// Kodlar, asagidaki linklerden alinip degistirilmistir.
// https://stackoverflow.com/questions/5043403/listing-only-folders-in-directory
// https://stackoverflow.com/questions/11140483/how-to-get-list-of-files-with-a-specific-extension-in-a-given-folder

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

std::vector<std::string> get_dizinler(const std::string& s);
std::vector<std::string> get_csvler(const std::string& s);

#endif

