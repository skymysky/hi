#pragma once

#include <string>
#include <cstdlib>
#include <unordered_map>

namespace hi
{

    class response
    {
    public:
        response()
            : status(404), content("<p style='text-align:center;margin:100px;'>404 Not Found</p>"), headers()
        {
            this->headers.insert(std::move(std::make_pair(std::move("Content-Type"), std::move("text/html;charset=UTF-8"))));
        }
        virtual ~response() = default;
        void set_header(const std::string &key, const std::string &value)
        {
            if (key == "Content-Type")
            {
                this->headers.find(key)->second = value;
            }
            else
            {
                this->headers.insert(std::move(std::make_pair(key, value)));
            }
        }
        void set_cookie(const std::string &k, const std::string &v, const std::string &str)
        {
            char buffer[100];
            int ret = snprintf(buffer, 100, "%s=%s; %s", k.c_str(), v.c_str(), str.c_str());
            this->set_header("Set-Cookie", std::string(buffer, ret));
        }
        void set_cookie_safe(const std::string &k, const std::string &v, size_t sec, bool safe = true)
        {
            char buffer[100];
            int ret;
            if (safe)
            {
                ret = snprintf(buffer, 100, "%s=%s; HttpOnly; Path=/; Secure; Max-Age=%s", k.c_str(), v.c_str(), std::to_string(sec).c_str());
            }
            else
            {
                int ret = snprintf(buffer, 100, "%s=%s; HttpOnly; Path=/; Max-Age=%s", k.c_str(), v.c_str(), std::to_string(sec).c_str());
            }

            this->set_header("Set-Cookie", std::string(buffer, ret));
        }
        int status;
        std::string content;
        std::unordered_multimap<std::string, std::string> headers;
    };
} // namespace hi
