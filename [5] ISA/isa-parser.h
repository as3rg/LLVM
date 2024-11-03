#include "isa.h"

class ParsingContext {
private:
  isa::REG_t regs[isa::REG_CNT];
public:
  std::array<isa::Reg<isa::W8_t>*, isa::REG_CNT> LI;
  std::array<isa::Reg<isa::W16_t>*, isa::REG_CNT> XI;
  std::array<isa::Reg<isa::W32_t>*, isa::REG_CNT> EXI;
  std::array<isa::Reg<isa::W64_t>*, isa::REG_CNT> RXI;
  std::vector<std::unique_ptr<isa::ISAObject>> allocated;
  std::unordered_map<std::string, isa::Function*> functions;
  std::unordered_map<std::string, isa::Function*> external_functions;
  std::unordered_map<std::string, std::map<std::string, isa::Label*>> labels;

  ParsingContext() {
    for (size_t i = 0; i < isa::REG_CNT; ++i) {
        LI[i] = allocate(isa::Reg<isa::W8_t>(i));
        XI[i] = allocate(isa::Reg<isa::W16_t>(i));
        EXI[i] = allocate(isa::Reg<isa::W32_t>(i));
        RXI[i] = allocate(isa::Reg<isa::W64_t>(i));
    }
  }

  template <typename T, typename T2 = std::remove_reference_t<T>>
  T2* allocate(T&& t) {
    std::unique_ptr<T2> ptr = std::make_unique<T2>(std::forward<T&&>(t));
    T2* res = ptr.get();
    allocated.emplace_back(std::move(ptr));
    return res;
  }
};

int parse(ParsingContext& pcxt, const std::vector<std::string>& lines);