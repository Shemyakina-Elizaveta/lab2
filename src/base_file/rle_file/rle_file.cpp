#include "rle_file.h"

int RleFile::write( const void *buf, int n_bytes )
{
  if (!can_write())
    return 0;

  const char *new_buf = static_cast<const char *>(buf);
  unsigned char cnt = 1;
  int dst_size = 0;
  char *dst = new char[n_bytes * 2] {};

  for (int i = 0; i < n_bytes; i++)
  {
    if (i + 1 < n_bytes && new_buf[i] == new_buf[i + 1] && cnt < 255)
      cnt++;
    else
    {
      dst[dst_size] = new_buf[i];
      dst[dst_size + 1] = cnt;
      dst_size += 2;
      cnt = 1;
    }
  }

  int res = write_raw(dst, dst_size);

  delete[] dst;

  return res;
}

int RleFile::read( void *buf, int max_bytes )
{
  if (!can_read())
    return 0;

  // char *raw_data = new char[max_bytes];
  char *dst = static_cast<char *>(buf);
  int dst_len = 0;

  // int len = read_raw(raw_data, max_bytes);
  // 
  // // TODO: поправить:
  // // 1. Не переполнять буфер buf
  // // 2. Не терять данные между вызовами функции
  // 
  // for (int i = 0; i < len;)
  // {
  //   char ch = raw_data[i++];
  //   unsigned char num = raw_data[i++];
  // 
  //   for (int j = 0; j < num && dst_len < max_bytes; j++)
  //     dst[dst_len++] = ch;
  // }

  while (dst_len < max_bytes && ost_data_num > 0)
    dst[dst_len++] = ost_data_ch, ost_data_num--;


  char raw_data[2];
  for (int i = 0; i < max_bytes / 2; i++)
  {
    int len = read_raw(raw_data, 2);

    if (len <= 1)
      return dst_len;

    char ch = raw_data[0];
    unsigned char num = raw_data[1];
    int j;
    for (j = 0; j < num && dst_len < max_bytes; j++)
      dst[dst_len++] = ch;

    if (j < num)
    {
      ost_data_ch = ch, ost_data_num = num - j;
      return dst_len;
    }
  }

  return dst_len;
}


bool RleFile2::can_read( void )
{
  return file->can_read();
}

bool RleFile2::can_write( void )
{
  return file->can_write();
}

int RleFile2::write( const void *buf, int n_bytes )
{
  if (!can_write())
    return 0;

  const char *new_buf = static_cast<const char *>(buf);
  unsigned char cnt = 1;
  int dst_size = 0;
  char *dst = new char[n_bytes * 2] {};

  for (int i = 0; i < n_bytes; i++)
  {
    if (i + 1 < n_bytes && new_buf[i] == new_buf[i + 1] && cnt < 255)
      cnt++;
    else
    {
      dst[dst_size] = new_buf[i];
      dst[dst_size + 1] = cnt;
      dst_size += 2;
      cnt = 1;
    }
  }

  int res = file->write(dst, dst_size);

  delete[] dst;

  return res;
}

int RleFile2::read( void *buf, int max_bytes )
{
  if (!can_read())
    return 0;

  char *raw_data = new char[max_bytes];
  char *dst = static_cast<char *>(buf);
  int dst_len = 0;

  int len = file->read(raw_data, max_bytes);


  for (int i = 0; i < len;)
  {
    char ch = raw_data[i++];
    unsigned char num = raw_data[i++];

    for (int j = 0; j < num; j++)
      dst[dst_len++] = ch;

  }

  delete[] raw_data;

  return dst_len;
}
