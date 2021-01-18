#include "dosya_dizin.h"

std::vector<std::string> get_dizinler(const std::string& s)
{
    std::vector<std::string> r;
    for (auto& p : std::filesystem::directory_iterator(s))
        if (p.is_directory())
            r.push_back(p.path().filename().string());
    return r;
}

std::vector<std::string> get_csvler(const std::string& s)
{
    std::vector<std::string> r;
    for (auto& p : std::filesystem::directory_iterator(s))
        if (p.path().has_extension() && !p.path().extension().compare(".csv"))
            r.push_back(p.path().filename().string());
    return r;
}