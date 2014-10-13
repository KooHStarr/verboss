#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <sstream>
#include <string>

class Exception
{
public:
    Exception(const std::string& info,
              const std::string& file = std::string(), int line = 0) :
              m_info(info),
              m_file(file)
    {
        /*
          REPLACE THIS BY std::to_string
        */
        std::stringstream ss;
        ss << line;
        m_line = ss.str();
    }

    const std::string& info() const
    {
        return m_info;
    }

    const std::string& file() const
    {
        return m_file;
    }

    const std::string& line() const
    {
        return m_line;
    }

private:
    std::string m_info;
    std::string m_file;
    std::string m_line;
};

#endif // EXCEPTION_HPP
