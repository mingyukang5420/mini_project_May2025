// Play.h
#ifndef __PLAY_H__
#define __PLAY_H__

#include <ctime> // For time_t
#include <string>


class Play {
public:
  Play(int a_id = 0, std::string a_name = "", time_t a_showingDate = 0,
       std::string a_genre = "", float a_price = 0.0f);

  int getPlaysId() const;
  std::string getPlaysName() const;
  time_t getShowingDate() const;
  std::string getGenre() const;
  float getPrice() const;

  void setPlaysName(const std::string &a_name);
  void setShowingDate(time_t a_showingDate);
  void setGenre(const std::string &a_genre);
  void setPrice(float a_price);

private:
  int m_playsId;
  std::string m_playsName;
  time_t m_showingDate; // YYYY-MM-DD 형식으로 관리 (저장 시 변환)
  std::string m_genre;
  float m_price;
};

#endif // __PLAY_H__