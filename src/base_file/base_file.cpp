#include "base_file.h"

void BaseFile::close( void )
{
  if (file != nullptr)
    fclose(file);

  file = nullptr;
}

bool BaseFile::is_open( void )
{
  return file != nullptr;
}

bool BaseFile::can_read( void )
{
  return is_open() && mode[0] == 'r';
}

bool BaseFile::can_write( void )
{
  return is_open() && mode[0] == 'w';
}

int BaseFile::write_raw( const void *buf, int n_bytes )
{
  if (!can_write())
    return 0;

  int res = (int)fwrite(buf, 1, n_bytes, file);

  return std::min(res, n_bytes);
}

int BaseFile::read_raw( void *buf, int max_bytes )
{
  if (!can_read() || buf == nullptr)
    return 0;

  int res = (int)fread(buf, 1, max_bytes, file);

  return std::min(res, max_bytes);
}

int BaseFile::write( const void *buf, int n_bytes )
{
  if (!can_write())
    return 0;

  int res = (int)fwrite(buf, 1, n_bytes, file);

  return std::min(res, n_bytes);
}

int BaseFile::read( void *buf, int max_bytes )
{
  if (!can_read() || buf == nullptr)
    return 0;

  int res = (int)fread(buf, 1, max_bytes, file);

  return std::min(res, max_bytes);
}


long BaseFile::tell( void )
{
  if (file == nullptr)
    return -1;

  return ftell(file);
}

bool BaseFile::seek( long offset )
{
  if (file == nullptr)
    return false;

  return !fseek(file, offset, SEEK_SET);
}

void write_size_t(IFile &file, int n)
{
  char buf[20] {};
  int len = 0;

  if (n < 0)
  {
    file.write("-", 1);
    n = -n;
  }

  while (n > 0)
    buf[len++] = n % 10 + '0', n = n / 10;

  for (int i = len - 1; i >= 0; i--)
    file.write(&buf[i], 1);
}