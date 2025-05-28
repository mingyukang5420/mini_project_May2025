#ifndef ACCOUNTREGISTER_H
#define ACCOUNTREGISTER_H

#include "user.h"

class AccountRegister {
public:
  AccountRegister();
  ~AccountRegister();
  bool isValidate();

private:
  string m_logInId;
  string m_logInPassword;
};

#endif
