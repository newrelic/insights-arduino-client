/*
  InsightsEvent.cpp - A simple New Relic Insights event container.
  Created by Jason Snell, November 6, 2014
  MIT License.
*/

#ifndef insightsevent_h
#define insightsevent_h

#include <Arduino.h>

class InsightsEvent {
public:
  InsightsEvent(String type);

  void addAttribute(String key, String value);
  void addAttribute(String key, int16_t value);
  String toJson();
  
private:
  String json;
};

#endif
