// DisplayConsoleView.h
#pragma once

#include <string>
#include <vector>

// Forward declarations
class Customer;
class Plays;
class Ticket;

class DisplayConsoleView {
public:
  // Menu display functions
  static void showMainMenu();
  static void showCustomerMenu();
  static void showPlaysMenu();
  static void showTicketMenu();

  // List display functions
  static void displayCustomerList(const std::vector<std::string> &customers);
  static void displayPlaysList(const std::vector<std::string> &plays);
  static void displayTicketList(const std::vector<std::string> &tickets);

  // Single item display functions
  static void displayCustomer(const Customer *customer);
  static void displayPlay(const Plays *play);
  static void displayTicket(const Ticket *ticket);

  // Utility functions
  static void showMessage(const std::string &message);
  static void showErrorMessage(const std::string &message);
  static void clearScreen();
  static void pressEnterToContinue();

  static std::string getInput(const std::string &prompt);
  static int getIntInput(const std::string &prompt);
};