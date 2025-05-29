#ifndef PLAYS_H
#define PLAYS_H

#include <string>
#include <vector>
using namespace std;

class Plays {
public:
  Plays();
  ~Plays();
  int getId() const { return m_playsId; }
  string getName() const { return m_playsName; }
  string getLocation() const { return m_playsLocation; }
  string getDate() const; // time_t를 string으로 변환하여 반환
  string getTime() const; // time_t를 string으로 변환하여 반환
  int getPrice() const { return m_playsPrice; }
  string getGenre() const { return m_playsGenre; }
  float getReviewScore() const { return m_playsReviewScore; }
  const vector<string> &getCast() const { return m_playsCast; }
  int getRunningTime() const { return m_playsRunningTime; }

private:
  int m_playsId;
  string m_playsName;
  time_t m_playsDate;
  time_t m_playsTime;
  string m_playsLocation;
  int m_playsPrice;
  string m_playsGenre;
  float m_playsReviewScore;
  vector<string> m_playsCast;
  int m_playsRunningTime;
};

#endif // PLAYS_H
