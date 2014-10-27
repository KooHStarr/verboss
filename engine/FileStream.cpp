#include "FileStream.hpp"

FileStream::FileStream(const std::string& filename) :
        m_File(nullptr)
{
    if (filename != std::string())
        open(filename);
}

FileStream::~FileStream()
{
    close();
}

bool FileStream::isOpen() const
{
    return (m_File != nullptr);
}

bool FileStream::open(const std::string& filename)
{
    close();
    m_File = PHYSFS_openRead(filename.c_str());
    return isOpen();
}

void FileStream::close()
{
    if (isOpen())
        PHYSFS_close(m_File);

    m_File = nullptr;
}

sf::Int64 FileStream::read(void* data, sf::Int64 size)
{
    if (!isOpen())
        return -1;

    return PHYSFS_read(m_File, data, 1, static_cast<PHYSFS_uint32>(size));
}

sf::Int64 FileStream::seek(sf::Int64 position)
{
    if (!isOpen())
        return -1;

    if (PHYSFS_seek(m_File, position))
        return tell();
    else
        return -1;
}

sf::Int64 FileStream::tell()
{
    if (!isOpen())
        return -1;

    return PHYSFS_tell(m_File);
}

sf::Int64 FileStream::getSize()
{
    if (!isOpen())
        return -1;

    return PHYSFS_fileLength(m_File);
}

std::string FileStream::content()
{
    auto size = getSize();
    char* buff = new char[size];
    read(buff, size);
    std::string data(buff);
    delete[] buff;
    return data;
}