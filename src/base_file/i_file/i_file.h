#ifndef __i_file_h__
#define __i_file_h__

#include "../../lab2.h"

class IFile
{
public:
  virtual ~IFile( void ) = default;

  virtual bool can_read( void ) = 0;
  virtual bool can_write( void ) = 0;
  virtual int write( const void *buf, int n_bytes ) = 0;
  virtual int read( void *buf, int max_bytes ) = 0;

};

#endif /* __i_file_h__ */