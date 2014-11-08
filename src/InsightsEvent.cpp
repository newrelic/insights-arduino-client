/*
  InsightsEvent.cpp - A simple New Relic Insights event container.
  Created by Jason Snell, November 6, 2014
  MIT License.
*/

static const char EVENT_TYPE[] = "[{\"eventType\":\"";
static const char QUOTE[]      = "\"";
static const char KV_SEP[]     = "\":";
static const char ATTR_SEP[]   = ",\"";
static const char TERMINATOR[] = "}]";

#include "InsightsEvent.h"

InsightsEvent::InsightsEvent(String type) {
  json = String(EVENT_TYPE);
  json += type;
  json += QUOTE;
}

void InsightsEvent::addAttribute(String key, String value) {
  json += ATTR_SEP;
  json += key;
  json += KV_SEP;
  json += QUOTE;
  json += value;
  json += QUOTE;
}

void InsightsEvent::addAttribute(String key, int16_t value) {
  json += ATTR_SEP;
  json += key;
  json += KV_SEP;
  json += String(value);
}

String InsightsEvent::toJson() {
  return json + TERMINATOR;
}
