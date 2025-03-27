#ifndef __base_file_h__
#define __base_file_h__

#include "../lab2.h"

#include "i_file/i_file.h"

class BaseFile : public IFile
{
  FILE *file;
  const char *mode;
  
public:

  BaseFile( void ) : file(nullptr), mode(nullptr)
  {
    std::cout << "Base file constructor\n";
  }

  BaseFile( const char *file_path, const char *new_mode )
  {
    std::cout << "Base file constructor\n";
    mode = new_mode;
    file = fopen(file_path, mode);
  }

  BaseFile( FILE *file, const char *new_mode ) : file(file), mode(new_mode)
  {
    std::cout << "Base file constructor\n";
  }

  virtual ~BaseFile( void ) override
  {
    std::cout << "Base file destructor\n";
    
    if (file != nullptr)
      fclose(file);
  }

  void close( void );
  bool is_open( void );
  bool can_read( void );
  bool can_write( void );
  int write_raw( const void *buf, int n_bytes );
  int read_raw( void *buf, int max_bytes );
  long tell( void );
  bool seek( long offset );
  virtual int write( const void *buf, int n_bytes );
  virtual int read( void *buf, int max_bytes );
};


void write_size_t(IFile &file, int n);

#endif /*__base_file_h__ */
