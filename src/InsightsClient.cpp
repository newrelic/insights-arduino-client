/*
  InsightsClient.cpp - Library for sending events to New Relic Insights
  Created by Jason Snell, November 6, 2014
  MIT License.
*/

#include "InsightsClient.h"

static const char SERVER_URL[]          = "insights-collector.newrelic.com";

static const char POST_LINE_START[]     = "POST /v1/accounts/";
static const char POST_LINE_END[]       = "/events HTTP/1.1";
static const char INSIGHTS_HOST_LINE[]  = "Host: insights-collector.newrelic.com";
static const char USER_AGENT_LINE[]     = "User-Agent: arduino-ethernet";
static const char CONTENT_TYPE_LINE[]   = "Content-Type: application/json";
static const char KEY_HEADER_LINE[]     = "X-Insert-Key: ";
static const char CONTENT_LENGTH_LINE[] = "Content-Length: ";
static const char CONNECTION_CLOSE[]    = "Connection: close";

static const bool SUCCESS = true;
static const bool FAILURE = false;

InsightsClient::InsightsClient(Client *client, const char *account, const char *key) {
  _client  = client;
  _account = account;
  _key     = key;
}

bool InsightsClient::sendEvent(InsightsEvent *event) {
  // Ensure the connection is closed before we connect
  _client->stop();
  
  if (_client->connect(SERVER_URL, 80)) {
    String json = event->toJson();
    
    _client->print(POST_LINE_START); _client->print(_account); _client->println(POST_LINE_END);
    _client->println(INSIGHTS_HOST_LINE);
    _client->println(USER_AGENT_LINE);
    _client->println(CONTENT_TYPE_LINE);
    _client->print(KEY_HEADER_LINE); _client->println(_key);
    _client->print(CONTENT_LENGTH_LINE); _client->println(json.length());
    _client->println(CONNECTION_CLOSE);
    _client->println();
      
    _client->println(json);
    
    String response = String();
    int16_t response_code = 0;
    
    while (_client->available()) {
      char c = _client->read();
      response += c;
    }

    uint16_t code_start = response.indexOf("Status: ") + 8;
    uint16_t code_end = response.indexOf(" ", code_start);
    response_code = response.substring(code_start, code_end).toInt();
    
    _client->stop();
    
    if (response_code == 200) {
      return SUCCESS;
    } else {
      return FAILURE;
    }
  } else {
    _client->stop();
    return FAILURE;
  }
}
