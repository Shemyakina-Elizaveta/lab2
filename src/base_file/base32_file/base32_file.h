#ifndef __base32_file_h__
#define __base32_file_h__

#include "../../lab2.h"
#include "../base_file.h"

class Base32File : public BaseFile
{
  char table[32] {};

  int encoded32_size( int raw_size );  
  int decoded32_size( int encode_size );

public:

  Base32File( void ) : BaseFile()
  {
    std::cout << "Base 32 file constructor\n";
  }

  Base32File( const char *file_path, const char *mode, const char *new_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456"  ) : 
    BaseFile(file_path, mode) 
  {
    std::cout << "Base 32 file constructor\n";

    strncpy(table, new_table, 32);
  }

  Base32File( FILE *file, const char *mode, const char *new_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456" ) : 
    BaseFile(file, mode)
  {
    std::cout << "Base 32 file constructor\n";
    strncpy(table, new_table, 32);
  }

  ~Base32File( void ) override
  {
    std::cout << "Base 32 file destructor\n";
  }

  int write( const void *buf, int n_bytes );
  int read( void *buf, int max_bytes );
};


class Base32File2 : public IFile
{
  IFile *file;
  char table[32] {};

  int encoded32_size( int raw_size );  
  int decoded32_size( int encode_size );

public:

  //Base32File2( void ) : file(nullptr) {}

  Base32File2( IFile *file, const char *new_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456" ) : file(file)
  {
    strncpy(table, new_table, 32);
  }

  Base32File2(const Base32File2& other) = delete;

  ~Base32File2( void ) 
  {
    std::cout << "b32f2 des\n";

    if (file != nullptr)
      delete file;
    file = nullptr;
  }

  bool can_read( void );
  bool can_write( void );
  int write( const void *buf, int n_bytes );
  int read( void *buf, int max_bytes );
};


#endif /* __base32_file_h__ */