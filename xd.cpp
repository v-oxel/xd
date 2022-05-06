#include <array>
#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#define NO_COLOR
namespace ansi {
    std::string escape(const std::string& seq)
    {
#ifdef NO_COLOR
        return "";
#else
        return "\033[" + seq;
#endif
    }

    std::string reset()
    {
        return escape("0m");
    }

    namespace colors {
        enum t { black, red, green, yellow, blue, magenta, cyan, white };
    }

    typedef colors::t color_t;

    std::string color(color_t col, bool bright = true, bool is_fg = true)
    {
        std::stringstream sstream;
        if (bright)
            sstream << "1;";
        sstream << (unsigned(col) + ((is_fg) ? 30 : 40)) << "m";
        return escape(sstream.str());
    }
}

namespace hexview {
    static void print_offset(unsigned long offset)
    {
        static const std::array<std::string, 2> colors = {
            ansi::color(ansi::colors::white),
            ansi::color(ansi::colors::red, false, false)
        };
        std::cout << colors[0] << colors[1] << std::hex << std::setw(8)
            << std::setfill('0') << offset << std::dec << std::setw(0)
            << std::setfill(' ') << ansi::reset();
    }

    static void print_hex(const std::vector <uint8_t>& bytes)
    {
        static const std::array<std::string, 2> colors = {
            ansi::color(ansi::colors::white),
            ansi::color(ansi::colors::green, false, false)
        };
        size_t i = bytes.size();
        for (const auto& byte : bytes) {
            std::cout << colors[0] << colors[1] << std::hex << std::setw(2)
                << std::setfill('0') << unsigned(byte) << ansi::reset();
            if (--i > 0)
                std::cout.put(' ');
        }
        std::cout << std::dec << std::setw(0) << std::setfill(' ');
    }

    static void print_ascii(const std::vector <uint8_t>& bytes)
    {
        static const std::array<std::string, 2> colors = {
            ansi::color(ansi::colors::white),
            ansi::color(ansi::colors::blue, false, false)
        };
        std::cout << colors[0] << colors[1];
        for (const auto& byte : bytes) {
            if (std::isprint(byte) && byte != '\n')
                std::cout.put(char(byte));
            else
                std::cout << '.';
        }
        std::cout << ansi::reset();
    }

    static const std::array<std::string, 2> error_colors = {
        ansi::color(ansi::colors::red),
        ansi::color(ansi::colors::black, false, false)
    };

    static unsigned long read_bytes(std::vector<uint8_t>& bytes,
        unsigned long count, std::ifstream& file, const std::string& path)
    {
        unsigned long i;
        uint8_t byte;
        for (i = 0; (i < count); ++i) {
            byte = (uint8_t)file.get();
            if (file.bad()) {
                std::stringstream sstream;
                sstream << error_colors[0] << error_colors[1]
                    << "Read error in file \"" << path << "\"";
                throw std::runtime_error(sstream.str().c_str());
            }
            else if (file.eof()) {
                break;
            }
            else {
                bytes[i] = byte;
            }
        }
        return i;
    }

    static int viewhex(std::ifstream& file, const std::string& path)
    {
        static const unsigned long bytes_per_line = 16;
        unsigned long offset = 0;
        while (true) {
            std::vector<uint8_t> bytes(bytes_per_line);
            print_offset(offset);
            std::cout << "  ";
            offset += read_bytes(bytes, bytes_per_line, file, path);
            print_hex(bytes);
            std::cout << "  ";
            print_ascii(bytes);
            std::cout.put('\n');
            if (file.eof())
                break;
        }
        std::cout << "Above file: " << path << std::endl;
        return 0;
    }

    static int viewhex(const std::string& path)
    {
        std::ifstream file(path.c_str());
        if (!(file.is_open())) {
            std::stringstream sstream;
            sstream << error_colors[0] << error_colors[1]
                << "Error opening file \"" << path << "\"";
            throw std::runtime_error(sstream.str().c_str());
        }
        int ret = viewhex(file, path);
        file.close();
        return ret;
    }
}

int __main(int argc, char* argv[])
{
    int i;
    if (argc < 2) {
        std::cerr << ansi::color(ansi::colors::red) << "Usage: " << argv[0]
            << " [file [file 2 [... [file n]]]]" << ansi::reset()
            << std::endl;
        std::exit(EXIT_FAILURE);
    }
    for (i = 1; i < argc; ++i)
        hexview::viewhex(argv[i]);
    return 0;
}
