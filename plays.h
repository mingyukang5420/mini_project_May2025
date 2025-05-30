#ifndef PLAYS_H
#define PLAYS_H

#include <string>
#include <vector>
using namespace std;

class Plays {
public:
  Plays();
  ~Plays();
  int getPlaysId() const { return m_playsId; }
  string getName() const { return m_playsName; }
  string getLocation() const { return m_playsLocation; }
  string getDate() const; // time_t를 string으로 변환하여 반환
  string getTime() const; // time_t를 string으로 변환하여 반환
  int getPrice() const { return m_playsPrice; }
  string getGenre() const { return m_playsGenre; }
  float getReviewScore() const { return m_playsReviewScore; }
  const vector<string> &getCast() const { return m_playsCast; }
  int getRunningTime() const { return m_playsRunningTime; }
  string getStatus() const { return m_playsStatus; }

  void setId(int id) { m_playsId = id; }
  void setName(const string &name) { m_playsName = name; }
  void setLocation(const string &location) { m_playsLocation = location; }
  void setDate(time_t date) { m_playsDate = date; }
  void setTime(time_t time) { m_playsTime = time; }
  void setPrice(int price) { m_playsPrice = price; }
  void setGenre(const string &genre) { m_playsGenre = genre; }
  void setReviewScore(float score) { m_playsReviewScore = score; }
  void setCast(const vector<string> &cast) { m_playsCast = cast; }
  void setRunningTime(int minutes) { m_playsRunningTime = minutes; }
  void setStatus(const string &status) { m_playsStatus = status; }

  time_t getRawDate() const { return m_playsDate; }
  time_t getRawTime() const { return m_playsTime; }
  bool isUpcoming() const;
  bool hasTimeConflict(const Plays &other) const;

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
  string m_playsStatus;
};

#endif // PLAYS_H
