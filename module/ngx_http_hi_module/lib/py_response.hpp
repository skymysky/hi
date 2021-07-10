#pragma once

#include "response.hpp"

namespace hi
{

    class py_response
    {
    public:
        py_response()
            : res(0)
        {
        }

        virtual ~py_response()
        {
            this->res = 0;
        }

        void init(response *res)
        {
            this->res = res;
        }

        void status(int c)
        {
            this->res->status = c;
        }

        void content(const std::string &content)
        {
            this->res->content = content;
        }

        void header(const std::string &key, const std::string &value)
        {
            if (key == "Content-Type")
            {
                this->res->headers.find(key)->second = value;
            }
            else
            {
                this->res->headers.insert(std::make_pair(key, value));
            }
        }

        void session(const std::string &key, const std::string &value)
        {
            this->res->session.insert(std::make_pair(key, value));
        }

        void cache(const std::string &key, const std::string &value)
        {
            this->res->cache.insert(std::make_pair(key, value));
        }

    private:
        response *res;
    };
} // namespace hi
