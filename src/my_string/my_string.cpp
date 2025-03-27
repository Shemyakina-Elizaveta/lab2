#include "my_string.h"

MyString::MyString( const char *str )
{
  if (str == nullptr)
    throw;

  if (data != nullptr)
    delete[] data;

  length = (int)strlen(str);
  capacity = length + 1;

  data = new char[capacity] {};

  for (int i = 0; i < length; i++)
    data[i] = str[i];

  data[length] = '\0';
}

MyString::MyString( const MyString &MStr )
{
  if (MStr.data == nullptr)
    throw;

  if (data != nullptr)
    delete[] data;

  length = MStr.length;
  capacity = MStr.capacity + 1;

  data = new char[capacity] {};

  for (int i = 0; i < length; i++)
    data[i] = MStr.data[i];

  data[length] = '\0';
}

MyString & MyString::operator=( const MyString &MStr )
{
  if (data != nullptr)
    delete[] data;

  length = MStr.length;
  capacity = MStr.capacity;

  data = new char[capacity] {};

  for (int i = 0; i < length; i++)
    data[i] = MStr.data[i];

  return *this;
}

MyString & MyString::operator=( const char *str )
{
  if (data != nullptr)
    delete[] data;


  if (str == nullptr)
  {
    length = 0;
    capacity = 0;
    return *this;
  }

  length = (int)strlen(str);
  capacity = length + 1;

  data = new char[capacity] {};

  for (int i = 0; i < length; i++)
    data[i] = str[i];

  data[length] = '\0';

  return *this;
}


char MyString::get( int i )
{
  if (i < 0 || i > length || data == nullptr)
    throw;

  return data[i];
}

char * MyString::get_pointer( void )
{
  return data;
}

void MyString::set( int i, char c )
{
  if (i < 0 || i > length || data == nullptr)
    throw;

  data[i] = c;
}

void MyString::set_new_string( const char *str )
{
  if (str == nullptr)
    throw;

  if (data != nullptr)
    delete[] data;

  length = (int)strlen(str);
  capacity = length + 1;

  data = new char[capacity] {};

  for (int i = 0; i < length; i++)
    data[i] = str[i];

  data[length] = '\0';
}

void MyString::print( void )
{
  if (data == nullptr)
    return;

  for (int i = 0; i < length; i++)
    std::cout << data[i];

  std::cout << '\n';
}

int MyString::get_length( void )
{
  return length;
}





void MyString::read_line( void )
{
  std::cout << "Enter new string: ";

  char ch;

  if (data != nullptr)
    delete[] data;

  capacity = 1;
  length = 0;
  data = new char[capacity] {};

  while ((ch = getchar()) != '\n')
  {
    if (length + 1 >= capacity)
    {
      capacity = capacity * 2 + 1;

      char *new_str = new char[capacity];

      for (int i = 0; i < length; i++)
        new_str[i] = data[i];
      delete[] data;
      data = new_str;
    }

    data[length++] = ch;
  }

  data[length] = '\0';
}
