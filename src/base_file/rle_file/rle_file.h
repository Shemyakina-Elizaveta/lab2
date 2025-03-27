#ifndef __rle_file_h__
#define __rle_file_h__


#include "../../lab2.h"
#include "../base_file.h"


class RleFile : public BaseFile
{
  int ost_data_num = 0;
  char ost_data_ch = 0;

public:

  RleFile( void ) : BaseFile() 
  {
    std::cout << "RLE file constructor\n";
  }

  RleFile( const char *file_path, const char *mode ) : BaseFile(file_path, mode)
  {
    std::cout << "RLE file constructor\n";
  }

  RleFile( FILE *file, const char *mode ) : BaseFile(file, mode)
  {
    std::cout << "RLE file constructor\n";
  }

  ~RleFile( void ) override
  {
    std::cout << "RLE file destructor\n";
  }

  int write( const void *buf, int n_bytes );
  int read( void *buf, int max_bytes );
};


class RleFile2 : public IFile
{
  IFile *file;

public:

  RleFile2( void ) : file(nullptr) {}

  RleFile2( IFile *file ) : file(file) {}

  ~RleFile2( void )
  {
    if (file != nullptr)
      delete file;
    file = nullptr;
  }
  
  bool can_read( void );
  bool can_write( void );

  int write( const void *buf, int n_bytes );
  int read( void *buf, int max_bytes );
};

#endif /* __rle_file_h__ */