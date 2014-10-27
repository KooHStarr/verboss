#ifndef FILESTREAM_HPP
#define FILESTREAM_HPP

#include <physfs.h>
#include <SFML/System/InputStream.hpp>
#include <string>
#include "Debug.hpp"

class FileStream : public sf::InputStream
{
public:
    FileStream(const std::string& filename = std::string());
    virtual           ~FileStream();

    bool              isOpen() const;
    bool              eof();
    std::string       content();
    bool              open(const std::string& filename);
    void              close();

    virtual sf::Int64 read(void* data, sf::Int64 size);
    virtual sf::Int64 seek(sf::Int64 position);
    virtual sf::Int64 tell();
    virtual sf::Int64 getSize();

private:
    PHYSFS_File* m_File;
};

#endif