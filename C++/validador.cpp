#include "validador.h"
#include <regex>

bool es_valida(const std::string& password) {
    if (password.length() < 8) return false;
    return std::regex_search(password, std::regex("\\d")) &&
           std::regex_search(password, std::regex("[A-Z]"));
}
