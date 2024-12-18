#include "isa-parser.h"

#include <array>
#include <format>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

const std::regex func_regex("^\\s*#(\\w+)\\s*\\(\\s*(\\d+)\\s*\\)\\s*:?\\s*$");
const std::regex label_regex("^\\s*%(\\w+)\\s*:?\\s*$");
const std::regex comment_regex("^\\s*;(.+)$");
const std::regex instruction_regex("^\\s*(\\w+)\\s*(\\s.*)?$");
const std::regex register_regex("^\\s*(l|x|ex|rx)(\\d+)\\s*$");
const std::regex constant_regex("^\\s*\\((w8|w16|w32|w64)\\)\\s+([+-]?\\d+)\\s*$");
const std::regex ptr_regex("^\\s*\\((w8|w16|w32|w64)\\)\\s+\\*rx(\\d+)\\s*$");
const std::regex empty_regex("^\\s*$");

std::smatch matches;

enum class ArgType {
  W8,
  W16,
  W32,
  W64,
  LABEL,
  FUNC,
  NONE
};

ArgType get_type(const std::string& line) {
  std::stringstream ss(line);
  std::string pref;
  ss >> pref;
  if (pref.starts_with("l")) {
    return ArgType::W8;
  }
  if (pref.starts_with("x")) {
    return ArgType::W16;
  }
  if (pref.starts_with("ex")) {
    return ArgType::W32;
  }
  if (pref.starts_with("rx")) {
    return ArgType::W64;
  }
  if (pref.starts_with("(w8)")) {
    return ArgType::W8;
  }
  if (pref.starts_with("(w16)")) {
    return ArgType::W16;
  }
  if (pref.starts_with("(w32)")) {
    return ArgType::W32;
  }
  if (pref.starts_with("(w64)")) {
    return ArgType::W64;
  }
  if (pref.starts_with("%")) {
    return ArgType::LABEL;
  }
  if (pref.starts_with("#")) {
    return ArgType::FUNC;
  }
  return ArgType::NONE;
}

template <typename T>
T* parse_op(ParsingContext& pcxt, const std::string& line, std::string current_function, std::string current_label) {
  if (std::regex_search(line, matches, register_regex)) {
    std::string type = matches[1];
    size_t num = std::stoull(matches[2]);
    if constexpr (std::is_base_of_v<T, isa::Reg<isa::W8_t>>) {
      if (type == "l") {
        return pcxt.LI[num];
      } else {
        return nullptr;
      }
    }
    if constexpr (std::is_base_of_v<T, isa::Reg<isa::W16_t>>) {
      if (type == "x") {
        return pcxt.XI[num];
      } else {
        return nullptr;
      }
    }
    if constexpr (std::is_base_of_v<T, isa::Reg<isa::W32_t>>) {
      if (type == "ex") {
        return pcxt.EXI[num];
      } else {
        return nullptr;
      }
    }
    if constexpr (std::is_base_of_v<T, isa::Reg<isa::W64_t>>) {
      if (type == "rx") {
        return pcxt.RXI[num];
      } else {
        return nullptr;
      }
    }
  }
  if (std::regex_search(line, matches, constant_regex)) {
    std::string type = matches[1];
    unsigned long long num = std::stoull(matches[2]);
    if constexpr (std::is_base_of_v<T, isa::Const<isa::W8_t>>) {
      if (type == "w8") {
        return pcxt.allocate(isa::Const<isa::W8_t>(num));
      } else {
        return nullptr;
      }
    }
    if constexpr (std::is_base_of_v<T, isa::Const<isa::W16_t>>) {
      if (type == "w16") {
        return pcxt.allocate(isa::Const<isa::W16_t>(num));
      } else {
        return nullptr;
      }
    }
    if constexpr (std::is_base_of_v<T, isa::Const<isa::W32_t>>) {
      if (type == "w32") {
        return pcxt.allocate(isa::Const<isa::W32_t>(num));
      } else {
        return nullptr;
      }
    }
    if constexpr (std::is_base_of_v<T, isa::Const<isa::W64_t>>) {
      if (type == "w64") {
        return pcxt.allocate(isa::Const<isa::W64_t>(num));
      } else {
        return nullptr;
      }
    }
  }
  if (std::regex_search(line, matches, ptr_regex)) {
    std::string type = matches[1];
    auto* value = pcxt.RXI[std::stoull(matches[2])];
    if (value == nullptr) {
      return nullptr;
    }

    if constexpr (std::is_base_of_v<T, isa::Ptr<isa::W8_t>>) {
      if (type == "w8") {
        return pcxt.allocate(isa::Ptr<isa::W8_t>(value));
      } else {
        return nullptr;
      }
    }
    if constexpr (std::is_base_of_v<T, isa::Ptr<isa::W16_t>>) {
      if (type == "w16") {
        return pcxt.allocate(isa::Ptr<isa::W16_t>(value));
      } else {
        return nullptr;
      }
    }
    if constexpr (std::is_base_of_v<T, isa::Ptr<isa::W32_t>>) {
      if (type == "w32") {
        return pcxt.allocate(isa::Ptr<isa::W32_t>(value));
      } else {
        return nullptr;
      }
    }
    if constexpr (std::is_base_of_v<T, isa::Ptr<isa::W64_t>>) {
      if (type == "w64") {
        return pcxt.allocate(isa::Ptr<isa::W64_t>(value));
      } else {
        return nullptr;
      }
    }
  }
  if (std::regex_search(line, matches, label_regex)) {
    if constexpr (std::is_base_of_v<T, isa::Label>) {
      std::string name = matches[1];
      return pcxt.labels[current_function][isa::Label(name).str()];
    } else {
      return nullptr;
    }
  }
  if (std::regex_search(line, matches, func_regex)) {
    if constexpr (std::is_base_of_v<T, isa::Function>) {
      std::string name = matches[1];
      size_t args_cnt = std::stoull(matches[2]);
      auto f = isa::Function(name, args_cnt);
      name = f.str();
      if (pcxt.functions.contains(name)) {
        return pcxt.functions[name];
      } else {
        auto& exfunc = pcxt.external_functions[name];
        if (!exfunc) {
          exfunc = pcxt.allocate(std::move(f));
        }
        return exfunc;
      }
    } else {
      return nullptr;
    }
  }
  return nullptr;
}

template <typename... Types>
struct Pack {};

template <size_t arg_cnt, typename Res, typename... TS>
Res run(const auto& func, const std::array<ArgType, arg_cnt>& arg_types, Pack<TS...> pack = {}) {
  if constexpr (arg_cnt == sizeof...(TS)) {
    return func(pack);
  } else {
    switch (arg_types[sizeof...(TS)]) {
    case ArgType::W8:
      return run<arg_cnt, Res>(func, arg_types, Pack<TS..., isa::W8_t>{});
    case ArgType::W16:
      return run<arg_cnt, Res>(func, arg_types, Pack<TS..., isa::W16_t>{});
    case ArgType::W32:
      return run<arg_cnt, Res>(func, arg_types, Pack<TS..., isa::W32_t>{});
    case ArgType::W64:
      return run<arg_cnt, Res>(func, arg_types, Pack<TS..., isa::W64_t>{});
    case ArgType::LABEL:
      return run<arg_cnt, Res>(func, arg_types, Pack<TS..., isa::Label>{});
    case ArgType::FUNC:
      return run<arg_cnt, Res>(func, arg_types, Pack<TS..., isa::W64_t>{});
    case ArgType::NONE:
      return nullptr;
    }
  }
}

template <template <typename> typename Instruction>
isa::Runnable* parse_binary_op(ParsingContext& pcxt, const std::vector<std::string>& args, std::string current_function,
                               std::string current_label) {
  return run<1, isa::Runnable*>(([&]<typename T>(Pack<T>) -> isa::Runnable* {
                                  if constexpr (isa::is_word_v<T>) {
                                    if (args.size() != 3) {
                                      return nullptr;
                                    }
                                    auto* res = parse_op<isa::Dest<T>>(pcxt, args[0], current_function, current_label);
                                    auto* op1 = parse_op<isa::Value<T>>(pcxt, args[1], current_function, current_label);
                                    auto* op2 = parse_op<isa::Value<T>>(pcxt, args[2], current_function, current_label);
                                    if (!res || !op1 || !op2) {
                                      return nullptr;
                                    }
                                    return pcxt.allocate(Instruction<T>(res, op1, op2));
                                  }
                                  return nullptr;
                                }),
                                {get_type(args[0])});
}

template <template <typename, typename> typename Instruction>
isa::Runnable* parse_shift(ParsingContext& pcxt, const std::vector<std::string>& args, std::string current_function,
                           std::string current_label) {
  return run<2, isa::Runnable*>(([&]<typename T, typename ST>(Pack<T, ST>) -> isa::Runnable* {
                                  if constexpr (isa::is_word_v<T> && isa::is_word_v<ST>) {
                                    if (args.size() != 3) {
                                      return nullptr;
                                    }
                                    auto* res = parse_op<isa::Dest<T>>(pcxt, args[0], current_function, current_label);
                                    auto* op1 = parse_op<isa::Value<T>>(pcxt, args[1], current_function, current_label);
                                    auto* op2 =
                                        parse_op<isa::Value<ST>>(pcxt, args[2], current_function, current_label);
                                    if (!res || !op1 || !op2) {
                                      return nullptr;
                                    }
                                    return pcxt.allocate(Instruction<T, ST>(res, op1, op2));
                                  }
                                  return nullptr;
                                }),
                                {get_type(args[0]), get_type(args[2])});
}

template <template <typename> typename Instruction>
isa::Runnable* parse_unary_op(ParsingContext& pcxt, const std::vector<std::string>& args, std::string current_function,
                              std::string current_label) {
  return run<1, isa::Runnable*>(([&]<typename T>(Pack<T>) -> isa::Runnable* {
                                  if constexpr (isa::is_word_v<T>) {
                                    if (args.size() != 2) {
                                      return nullptr;
                                    }
                                    auto* res = parse_op<isa::Dest<T>>(pcxt, args[0], current_function, current_label);
                                    auto* op = parse_op<isa::Value<T>>(pcxt, args[1], current_function, current_label);
                                    if (!res || !op) {
                                      return nullptr;
                                    }
                                    return pcxt.allocate(Instruction<T>(res, op));
                                  }
                                  return nullptr;
                                }),
                                {get_type(args[0])});
}

template <template <typename, typename> typename Instruction>
isa::Runnable* parse_logical(ParsingContext& pcxt, const std::vector<std::string>& args, std::string current_function,
                             std::string current_label) {
  return run<2, isa::Runnable*>(([&]<typename CT, typename T>(Pack<CT, T>) -> isa::Runnable* {
                                  if constexpr (isa::is_word_v<CT> && isa::is_word_v<T>) {
                                    if (args.size() != 3) {
                                      return nullptr;
                                    }
                                    auto* res = parse_op<isa::Dest<CT>>(pcxt, args[0], current_function, current_label);
                                    auto* op1 = parse_op<isa::Value<T>>(pcxt, args[1], current_function, current_label);
                                    auto* op2 = parse_op<isa::Value<T>>(pcxt, args[2], current_function, current_label);
                                    if (!res || !op1 || !op2) {
                                      return nullptr;
                                    }
                                    return pcxt.allocate(Instruction<CT, T>(res, op1, op2));
                                  }
                                  return nullptr;
                                }),
                                {get_type(args[0]), get_type(args[1])});
}

const char* ws = " \t\n\r\f\v";

std::string& rtrim(std::string& s, const char* t = ws) {
  s.erase(s.find_last_not_of(t) + 1);
  return s;
}

std::string& ltrim(std::string& s, const char* t = ws) {
  s.erase(0, s.find_first_not_of(t));
  return s;
}

std::string& trim(std::string& s, const char* t = ws) {
  return ltrim(rtrim(s, t), t);
}

std::vector<std::string> split_args(const std::string& str) {
  std::vector<std::string> res;
  std::stringstream ss(str);
  std::string buf;
  while (getline(ss, buf, ',')) {
    res.push_back(trim(buf));
  }
  return res;
}

#define ASSERT_FALSE(state, error)                                                                                     \
  {                                                                                                                    \
    if (state) {                                                                                                       \
      std::cerr << (error) << std::endl;                                                                               \
      return 1;                                                                                                        \
    }                                                                                                                  \
  }

int parse(ParsingContext& pcxt, const std::vector<std::string>& lines) {
  std::string current_function;
  std::string current_label;

  for (size_t line_num = 0; line_num < lines.size(); ++line_num) {
    std::string line = lines[line_num];
    if (std::regex_search(line, matches, func_regex)) {
      std::string name = matches[1];
      size_t args_cnt = std::stoull(matches[2]);

      isa::Function* f = pcxt.allocate(isa::Function(name, args_cnt));
      name = f->str();

      ASSERT_FALSE(pcxt.functions.contains(name), std::format("{}: function {} already exists", line_num, name));
      pcxt.functions[name] = f;
      current_function = name;

      pcxt.labels[current_function] = {};
    } else if (std::regex_search(line, matches, label_regex)) {
      ASSERT_FALSE(current_function.empty(),
                   std::format("{}: function declaration expected before the instruction", line_num));
      std::string name = matches[1];
      isa::Label* label = pcxt.allocate(isa::Label(name));
      name = label->str();

      ASSERT_FALSE(pcxt.labels[current_function].contains(name),
                   std::format("{}: label {} already exists in function {}", line_num, name, current_function));
      pcxt.labels[current_function][name] = label;
    }
  }

  isa::Runnable* next = nullptr;

  for (size_t line_num = 0; line_num < lines.size(); ++line_num) {
    std::string line = lines[line_num];
    if (std::regex_search(line, matches, func_regex)) {
      std::string name = matches[1];
      size_t args_cnt = std::stoull(matches[2]);

      name = isa::Function(name, args_cnt).str();
      current_function = name;
      current_label = "";

      isa::Runnable* nop = pcxt.allocate(isa::Nop());
      pcxt.functions[current_function]->next = nop;
      next = nop;
    } else if (std::regex_search(line, matches, comment_regex)) {
    } else if (std::regex_search(line, matches, label_regex)) {
      ASSERT_FALSE(next == nullptr, std::format("{}: function declaration expected before the instruction", line_num));

      std::string name = matches[1];
      current_label = isa::Label(name).str();

      next = next->next = pcxt.labels[current_function][current_label];
    } else if (std::regex_search(line, matches, instruction_regex)) {
      ASSERT_FALSE(next == nullptr, std::format("{}: function declaration expected before the instruction", line_num));

      std::string name = matches[1];
      std::vector<std::string> args = split_args(matches[2].str());

      if (name == "add") {
        next = next->next = parse_binary_op<isa::Add>(pcxt, args, current_function, current_label);
      } else if (name == "sub") {
        next = next->next = parse_binary_op<isa::Sub>(pcxt, args, current_function, current_label);
      } else if (name == "mul") {
        next = next->next = parse_binary_op<isa::Mul>(pcxt, args, current_function, current_label);
      } else if (name == "div") {
        next = next->next = run<1, isa::Runnable*>(
            ([&]<typename T>(Pack<T>) -> isa::Runnable* {
              if constexpr (isa::is_word_v<T>) {
                if (args.size() != 4) {
                  return nullptr;
                }
                auto* div = parse_op<isa::Dest<T>>(pcxt, args[0], current_function, current_label);
                auto* rem = parse_op<isa::Dest<T>>(pcxt, args[1], current_function, current_label);
                auto* op1 = parse_op<isa::Value<T>>(pcxt, args[2], current_function, current_label);
                auto* op2 = parse_op<isa::Value<T>>(pcxt, args[3], current_function, current_label);
                if (!div || !rem || !op1 || !op2) {
                  return nullptr;
                }
                return pcxt.allocate(isa::Div<T>(div, rem, op1, op2));
              }
              return nullptr;
            }),
            {get_type(args[0])});
      } else if (name == "udiv") {
        next = next->next = run<1, isa::Runnable*>(
            ([&]<typename T>(Pack<T>) -> isa::Runnable* {
              if (args.size() != 4) {
                return nullptr;
              }
              if constexpr (isa::is_word_v<T>) {
                auto* div = parse_op<isa::Dest<T>>(pcxt, args[0], current_function, current_label);
                auto* rem = parse_op<isa::Dest<T>>(pcxt, args[1], current_function, current_label);
                auto* op1 = parse_op<isa::Value<T>>(pcxt, args[2], current_function, current_label);
                auto* op2 = parse_op<isa::Value<T>>(pcxt, args[3], current_function, current_label);
                if (!div || !rem || !op1 || !op2) {
                  return nullptr;
                }
                return pcxt.allocate(isa::UDiv<T>(div, rem, op1, op2));
              }
              return nullptr;
            }),
            {get_type(args[0])});
      } else if (name == "and") {
        next = next->next = parse_binary_op<isa::And>(pcxt, args, current_function, current_label);
      } else if (name == "or") {
        next = next->next = parse_binary_op<isa::Or>(pcxt, args, current_function, current_label);
      } else if (name == "xor") {
        next = next->next = parse_binary_op<isa::Xor>(pcxt, args, current_function, current_label);
      } else if (name == "lsh") {
        next = next->next = parse_shift<isa::LSh>(pcxt, args, current_function, current_label);
      } else if (name == "rshl") {
        next = next->next = parse_shift<isa::RShL>(pcxt, args, current_function, current_label);
      } else if (name == "rsha") {
        next = next->next = parse_shift<isa::RShA>(pcxt, args, current_function, current_label);
      } else if (name == "eq") {
        next = next->next = parse_logical<isa::Eq>(pcxt, args, current_function, current_label);
      } else if (name == "neq") {
        next = next->next = parse_logical<isa::Neq>(pcxt, args, current_function, current_label);
      } else if (name == "lt") {
        next = next->next = parse_logical<isa::Lt>(pcxt, args, current_function, current_label);
      } else if (name == "le") {
        next = next->next = parse_logical<isa::Le>(pcxt, args, current_function, current_label);
      } else if (name == "ult") {
        next = next->next = parse_logical<isa::ULt>(pcxt, args, current_function, current_label);
      } else if (name == "ule") {
        next = next->next = parse_logical<isa::ULe>(pcxt, args, current_function, current_label);
      } else if (name == "mv") {
        next = next->next = parse_unary_op<isa::Mv>(pcxt, args, current_function, current_label);
      } else if (name == "mvc") {
        next = next->next = run<2, isa::Runnable*>(
            ([&]<typename CT, typename T>(Pack<CT, T>) -> isa::Runnable* {
              if constexpr (isa::is_word_v<CT> && isa::is_word_v<T>) {
                if (args.size() != 3) {
                  return nullptr;
                }
                auto* cond = parse_op<isa::Value<CT>>(pcxt, args[0], current_function, current_label);
                auto* res = parse_op<isa::DestValue<T>>(pcxt, args[1], current_function, current_label);
                auto* op = parse_op<isa::Value<T>>(pcxt, args[2], current_function, current_label);
                if (!cond || !res || !op) {
                  return nullptr;
                }
                return pcxt.allocate(isa::MvC<CT, T>(cond, res, op));
              }
              return nullptr;
            }),
            {get_type(args[0]), get_type(args[1])});
      } else if (name == "swp") {
        next = next->next = run<1, isa::Runnable*>(
            ([&]<typename T>(Pack<T>) -> isa::Runnable* {
              if constexpr (isa::is_word_v<T>) {
                if (args.size() != 2) {
                  return nullptr;
                }
                auto* op1 = parse_op<isa::DestValue<T>>(pcxt, args[0], current_function, current_label);
                auto* op2 = parse_op<isa::DestValue<T>>(pcxt, args[1], current_function, current_label);
                if (!op1 || !op2) {
                  return nullptr;
                }
                return pcxt.allocate(isa::Swp<T>(op1, op2));
              }
              return nullptr;
            }),
            {get_type(args[0])});

      } else if (name == "drw") {
        auto* x = parse_op<isa::Value<isa::COORD_t>>(pcxt, args[0], current_function, current_label);
        auto* y = parse_op<isa::Value<isa::COORD_t>>(pcxt, args[1], current_function, current_label);
        auto* color = parse_op<isa::Value<isa::COLOR_t>>(pcxt, args[2], current_function, current_label);
        next = next->next = x && y && color ? pcxt.allocate(isa::Drw(x, y, color)) : nullptr;
      } else if (name == "flsh") {
        next = next->next = pcxt.allocate(isa::Flsh());
      } else if (name == "free") {
        auto* op = parse_op<isa::Value<isa::PTR_t>>(pcxt, args[0], current_function, current_label);
        next = next->next = pcxt.allocate(isa::Free(op));
      } else if (name == "alloc") {
        next = next->next = run<1, isa::Runnable*>(
            ([&]<typename T>(Pack<T>) -> isa::Runnable* {
              if constexpr (isa::is_word_v<T>) {
                if (args.size() != 2) {
                  return nullptr;
                }
                auto* dest = parse_op<isa::Dest<isa::PTR_t>>(pcxt, args[0], current_function, current_label);
                auto* n = parse_op<isa::Value<T>>(pcxt, args[1], current_function, current_label);
                if (!n || !dest) {
                  return nullptr;
                }
                return pcxt.allocate(isa::Alloc<T>(dest, n));
              }
              return nullptr;
            }),
            {get_type(args[1])});
      } else if (name == "call") {
        auto* func = parse_op<isa::Function>(pcxt, args[0], current_function, current_label);
        next = next->next = func ? pcxt.allocate(isa::Call(func)) : nullptr;
      } else if (name == "ret") {
        next = next->next = pcxt.allocate(isa::Ret());
      } else if (name == "jp") {
        auto* lbl = parse_op<isa::Label>(pcxt, args[0], current_function, current_label);
        next = next->next = lbl ? pcxt.allocate(isa::Jp(lbl)) : nullptr;
      } else if (name == "jpc") {
        next = next->next =
            run<1, isa::Runnable*>(([&]<typename T>(Pack<T>) -> isa::Runnable* {
                                     if constexpr (isa::is_word_v<T>) {
                                       if (args.size() != 2) {
                                         return nullptr;
                                       }
                                       auto* cond =
                                           parse_op<isa::Value<T>>(pcxt, args[0], current_function, current_label);
                                       auto* lbl = parse_op<isa::Label>(pcxt, args[1], current_function, current_label);
                                       if (!cond || !lbl) {
                                         return nullptr;
                                       }
                                       return pcxt.allocate(isa::JpC<T>(cond, lbl));
                                     }
                                     return nullptr;
                                   }),
                                   {get_type(args[0])});
      } else if (name == "nop") {
        next = next->next = pcxt.allocate(isa::Nop());
      } else {
        std::cerr << line_num << ": unknown instruction " << name << " in function " << current_function << std::endl;
        return 1;
      }
      ASSERT_FALSE(next == nullptr, std::format("{}: error parsing line", line_num))
    } else if (std::regex_search(line, matches, empty_regex)) {
    } else {
      ASSERT_FALSE(true, std::format("{}: unexpected line", line_num))
    }
  }
  return 0;
}