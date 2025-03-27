#ifndef __my_string_h__
#define __my_string_h__

#include "../lab2.h"

class MyString
{
  char *data = nullptr;
  int length = 0;
  int capacity = 0;

public:

  MyString( void )
  {
    length = 0;
    capacity = 0;
    data = nullptr;
  }

  ~MyString( void )
  {
    if (data == nullptr)
      return;

    delete[] data;
  }

  MyString( const char *str );
  MyString( const MyString &MStr );

  MyString & operator=( const MyString &MStr );
  MyString & operator=( const char *str );

  bool operator==( const MyString &MStr )
  {
    return (strcmp(data, MStr.data) == 0);
  }

  bool operator==( const char *str )
  {
    return strcmp(data, str) == 0;
  }

  char get( int i );
  char * get_pointer( void );
  void set( int i, char c );
  void set_new_string( const char *str );
  void print( void );
  int get_length( void );
  void read_line( void );
};


#endif /* __my_string_h__ */