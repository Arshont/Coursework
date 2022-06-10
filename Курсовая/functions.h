#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "FrequencyTableElement.h"
#include "CodeTree.h"

#include <fstream>

void interfaceCustom();

void encode();
void decode();
void compare();

std::ostream& operator<<(std::ostream& out, FrequencyTableElement& elem);
std::ifstream& operator>>(std::ifstream& in, FrequencyTableElement& elem);
#endif // !FUNCTIONS_H