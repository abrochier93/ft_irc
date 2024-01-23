#ifndef __MESSAGES_H_
# define __MESSAGES_H_

#include "Libs.hpp"

std::string errorMessage(int key, std::string param1, std::string param2, std::string param3);
std::string replyMessage(int key, std::string param1, std::string param2, std::string param3);

#endif