#include "param.hpp"

#include <string>
#include <regex>
#include <unordered_map>

namespace hi
{

    std::string trim(const std::string &s)
    {
        auto it = s.begin();
        while (it != s.end() && isspace(*it))
        {
            it++;
        }
        auto rit = s.rbegin();
        while (rit.base() != it && isspace(*rit))
        {
            rit++;
        }
        return std::string(it, rit.base());
    }

    void parser_param(const std::string &data, std::unordered_map<std::string, std::string> &result)
    {
        if (data.empty())
            return;
        std::string str = data;
        std::regex re(R"(([^;&?:\s\/\\]+)=([^;&?]{0,}))");
        for (std::smatch sm; std::regex_search(str, sm, re);)
        {
            result[std::move(trim(sm[1]))] = std::move(trim(sm[2]));
            str = sm.suffix();
        }
    }
} // namespace hi
