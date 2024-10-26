#include "isa-parser.h"
#include <iostream>

int main() {
  std::vector<std::string> lines;
  for (size_t line_num = 0; ; ++line_num) {
    std::string line;
    std::getline(std::cin, line);
    if (!std::cin) {
      break;
    }
    lines.emplace_back(line); 
  }

  isa::CPU cpu;
  int code = parse(cpu, lines);
  if (code) return 1;

  for (auto&& [name, func] : cpu.functions) {
    std::cout << func->str() << "\n";
    isa::Runnable* next = func->next;
    while (next != nullptr) {
      std::cout << "  " << next->str() << "\n";
      next = next->next;
    }
    std::cout << "\n";
  }

  if (cpu.functions.contains("#main(0)")) {
    isa::run(cpu, cpu.functions["#main(0)"]);
  }
  return 0;
}