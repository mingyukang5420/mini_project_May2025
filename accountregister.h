#ifndef ACCOUNTREGISTER_H
#define ACCOUNTREGISTER_H

#include <string>
using namespace std;

class AccountRegister {
public:
  AccountRegister();
  ~AccountRegister();
  bool isValidate(const string &newId);

private:
  bool isValidIdFormat(const string &id);
};

#endif
