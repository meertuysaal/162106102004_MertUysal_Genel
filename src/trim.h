#ifndef TRIM_H
#define TRIM_H

// Bastaki ve sondaki beyaz karakterleri siler, asagidaki linkten alinmadir
// https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/

#include <string>
#include <regex>
#include "trim.h"

std::string trim(const std::string& s);

#endif