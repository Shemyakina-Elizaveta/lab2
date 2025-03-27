#include "base32_file.h"

int Base32File::encoded32_size( int raw_size )
{
  if (raw_size <= 0)
    return 0;
  return (raw_size * 8 + 4) / 5;
}

int Base32File::decoded32_size( int encode_size )
{
  if (encode_size <= 0)
    return 0;
  return (encode_size * 5) / 8;
}


int Base32File::write( const void *buf, int n_bytes )
{
  if (!can_write())
    return 0;

  int bits = 0, bs = 0, ds = 0, dst_len = encoded32_size(n_bytes);

  const char *raw_data = static_cast<const char *>(buf);
  char *dst = new char[dst_len] {};

  for (int i = 0; i < n_bytes; i++)
  {
    bits = (bits << 8) | (unsigned char)raw_data[i];
    bs += 8;

    while (bs >= 5)
    {
      dst[ds++] = table[(bits >> (bs - 5)) & 0x1f];
      bs -= 5;
    }
  }

  if (bs > 0)
    dst[ds++] = table[(bits << (5 - bs)) & 0x1f];

  int res = write_raw(dst, dst_len);
  delete[] dst;

  return res;
}

int Base32File::read( void *buf, int max_bytes )
{
  if (!can_read())
    return 0;

  int bits = 0, bs = 0, ds = 0;

  int raw_len = encoded32_size(max_bytes);
  char *raw_data = new char[raw_len] {};
  int res = read_raw(raw_data, raw_len);

  char *dst = static_cast<char *>(buf);

  for (int i = 0; i < res; i++)
  {
    const char *ptr = strchr(table, raw_data[i]);

    if (ptr == nullptr)
      return 2;

    int index = (int)(ptr - table);

    bits = (bits << 5) | index;
    bs += 5;

    if (bs >= 8)
    {
      dst[ds++] = (bits >> (bs - 8)) & 0xFF;
      bs -= 8;
    }
  }

  delete[] raw_data;

  return res;
}



bool Base32File2::can_read( void )
{
  return file->can_read();
}

bool Base32File2::can_write( void )
{
  return file->can_write();
}


int Base32File2::encoded32_size( int raw_size )
{
  if (raw_size <= 0)
    return 0;
  return (raw_size * 8 + 4) / 5;
}

int Base32File2::decoded32_size( int encode_size )
{
  if (encode_size <= 0)
    return 0;
  return (encode_size * 5) / 8;
}


int Base32File2::write( const void *buf, int n_bytes )
{
  if (!can_write())
    return 0;

  int bits = 0, bs = 0, ds = 0, dst_len = encoded32_size(n_bytes);

  const char *raw_data = static_cast<const char *>(buf);
  char *dst = new char[dst_len] {};

  for (int i = 0; i < n_bytes; i++)
  {
    bits = (bits << 8) | (unsigned char)raw_data[i];
    bs += 8;

    while (bs >= 5)
    {
      dst[ds++] = table[(bits >> (bs - 5)) & 0x1f];
      bs -= 5;
    }
  }

  if (bs > 0)
    dst[ds++] = table[(bits << (5 - bs)) & 0x1f];

  int res = file->write(dst, dst_len);
  delete[] dst;

  return res;
}

int Base32File2::read( void *buf, int max_bytes )
{
  if (!can_read())
    return 0;

  int bits = 0, bs = 0, ds = 0;

  int raw_len = encoded32_size(max_bytes);
  char *raw_data = new char[raw_len] {};
  int res = file->read(raw_data, raw_len);

  char *dst = static_cast<char *>(buf);

  for (int i = 0; i < res; i++)
  {
    const char *ptr = strchr(table, raw_data[i]);

    if (ptr == nullptr)
      return 2;

    int index = (int)(ptr - table);

    bits = (bits << 5) | index;
    bs += 5;

    if (bs >= 8)
    {
      dst[ds++] = (bits >> (bs - 8)) & 0xFF;
      bs -= 8;
    }
  }

  delete[] raw_data;

  return res;
}
