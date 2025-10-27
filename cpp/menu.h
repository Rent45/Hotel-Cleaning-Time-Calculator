#ifndef MENU_H
#define MENU_H

#include <string>
#include <functional>
#include <map>
using namespace std;

class Menu {
  string title;
  // key -> (description, action)
  map<string, pair<string, function<bool()>>> items;
public:
  explicit Menu(string title = "Menu");

  // Add an action that returns bool: return true -> keep running, false -> stop menu loop
  void add(const string& key, const string& description, function<bool()> action);

  // Convenience overload: add a void() action (it will be wrapped and keep the loop running)
  void add(const string& key, const string& description, function<void()> action);

  // Show entries (doesn't run the loop)
  void show() const;

  // Run interactive loop until an action returns false
  void run();

  // Execute a single key programmatically (returns true if loop should continue)
  bool execute(const string& key);
};

#endif // MENU_H
