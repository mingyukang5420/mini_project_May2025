#include "reserved.h"

Reserved::Reserved()
    : m_reservedId(0), m_reservedPlaysId(0), m_reservedCustomerId(0),
      m_reservedDate(0), m_reservedTime(0), m_reservedPrice(0.0f),
      m_reservedStatus("PENDING") {}

Reserved::~Reserved() {
  // vector와 string은 자동으로 소멸됨
  // 추가적인 정리 작업 필요 없음
}
