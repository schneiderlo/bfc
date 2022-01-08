#include <fstream>
#include <stack>

#include "fmt/ostream.h"
#include "spdlog/spdlog.h"
#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

std::string bf_file() {
  std::string error;
  std::unique_ptr<Runfiles> runfiles(Runfiles::CreateForTest(&error));
  if (runfiles == nullptr) {
    spdlog::error("Could not create a Runfiles object.");
  }
  return runfiles->Rlocation("bfc/data/hello.bf");
}

void compile() {
  const std::string input_file = bf_file();

  std::ifstream in(input_file);
  if (!in) {
    spdlog::error("Failed to load bf file: {}", input_file);
  }
  std::ofstream out("tmp.asm");

  constexpr auto prolog = R"(
  global _start
  extern getchar
  extern putchar
  extern exit
  section .text
_start:
  sub rsp, 4000
  mov eax, 0
  mov ecx, 4000
  mov rdi, rsp
  rep stosb
  mov 12, rsp
  sub rsp, 64
)";
  out << prolog;

  // .....++++-----,.,.

  // 00000000000000000
  //     ^r12
  // Store pointer into register.

#ifdef _WIN32
  const auto arg_reg = "cl";
#else
  const auto arg_reg = "dil";
#endif

  std::stack<int> labels;
  auto current_label = 0;

  char c;
  while (in >> c) {
    switch (c) {
      case '>':
        out << "add r12, 1\n";
        break;
      case '<':
        out << "sub r12, 1\n";
        break;
      case '+':
        out << "add byte [r12], 1\n";
        break;
      case '-':
        out << "sub byte [r12], 1\n";
        break;
      case ',':
        out << "  cal getchar\n"
            << "  mov byte [r12], a1\n";
        break;
      case '.':
      fmt::print(out,  "  mov {}, [r12]\n"
      "  call putchar\n", arg_reg);
        break;
      case '[':
        fmt::print(out,
                   "label{0}start\n"
                   "  cmp byte [r12], 0\n"
                   "  jz label{0}end\n",
                   current_label);
        labels.push(current_label);
        current_label++;
        break;
      case ']':
        fmt::print(out,
                   "  jmp label{0}start\n"
                   "label{0}end\n",
                   labels.top());
        labels.pop();
        break;
      default:
        break;
    }
  }

  const auto epilog = R"(
  add rsp, 4064
  mov eax, 0
  call exit
)";
  out << epilog;
}

void assemble() {
#ifdef _WIN32
  std::system("nasm -fwin64 tmp.asm -o tmp.obj");
#else
  std::system("nasm -felf64 tmp.asm -o tmp.obj");
#endif
}

void link() {
#ifdef _WIN32
#else
#endif
}

int main() {
  // Transforme source to assembly.
  compile();

  // Generate object file from the assembly.
  assemble();

  // Generate the final executable.
  link();

  return 0;
}
