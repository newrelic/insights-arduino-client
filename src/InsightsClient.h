/*
  InsightsClient.h - Library for sending events to New Relic Insights
  Created by Jason Snell, November 6, 2014
  MIT License.
*/

#ifndef insightsclient_h
#define insightsclient_h

#include "Client.h"
#include "InsightsEvent.h"

class InsightsClient {

public:
  InsightsClient(Client *client, const char *account, const char *key);
  
  bool sendEvent(InsightsEvent *event);
  //virtual int sendEvents(Event *events, int count);
private:
  Client *_client;
  const char *_account;
  const char *_key;
};

#endif

