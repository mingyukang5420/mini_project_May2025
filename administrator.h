#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "user.h"

class Administrator : public User {
public:
  Administrator();
  ~Administrator();

private:
  int m_adminId;
  string m_adminName;
};
#endif // ADMINISTRATOR_H
