#pragma once
#include <algorithm>
#include <string>
#include <vector>

template <typename T> class Manager {
public:
  Manager() = default;
  virtual ~Manager() = default;

  virtual void add(const T &item) { m_items.push_back(item); }

  virtual bool remove(const std::string &id) {
    auto it = std::find_if(m_items.begin(), m_items.end(),
                           [&id](const T &item) { return item.getId() == id; });
    if (it != m_items.end()) {
      m_items.erase(it);
      return true;
    }
    return false;
  }

  virtual const T *search(const std::string &id) const {
    auto it = std::find_if(m_items.begin(), m_items.end(),
                           [&id](const T &item) { return item.getId() == id; });
    return it != m_items.end() ? &(*it) : nullptr;
  }

  virtual std::vector<T> getAll() const { return m_items; }

  virtual void input() = 0;
  virtual bool modify(const std::string &id) = 0;
  virtual std::string makeId() const = 0;

protected:
  std::vector<T> m_items;
};