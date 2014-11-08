## New Relic Insights Ardunio Library.

Use this library to easily post custom events to New Relic Insights.  It should work on all newer Arduino and Intel Edison hardware.

## Usage

    // Construct an event...
    InsightsEvent event("ExampleEvent");
    event.addAttribute("awesomeKey", "awesomeValue");
    event.addAttribute("cats", 100);
    
    // And send it!
    insightsClient.sendEvent(&event);


See the examples dir for a more complete example on how to use this library.
