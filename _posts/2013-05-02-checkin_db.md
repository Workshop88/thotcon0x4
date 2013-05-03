---
layout: post
title: "checkin data"
description: ""
category: resources
tags: [announcements, data, badge]
---
{% include JB/setup %}

One of the functions of the badge was to report its location checkins to a central server upon the request of one of the beacons.  There was a beacon hidden in the Hacker Village area of THOTCON that would collect your badge checkin counts by area along with your badge node ID.   We started collecting checkins an hour after all areas were open which was shortly after noon, we were receiving connections until about 8:15pm when Hacker Village started to close.  Over that time period we had 643 by 256 distinct badges that hung around in the village long enough to receive a report request and report back.  This amounts to about half the population of people who had badges.  

Upon entering the con each badge was issued a two byte unique ID that is proceeded in the welcome message by "THOTCON 0x4 Badge Node:".  You can power up your badge, read your badge node number and query the database to see where you spent your time at the con.  The following is an example of the query for badge id 0x027d: 

```
sqlite3 reports 'select * from checkins where BID = "0x027d";' 
0x02d7|0|38|2|11|16|79|0|1|4|5
0x02d7|0|38|2|11|16|79|0|1|4|6
0x02d7|0|38|2|11|16|79|0|1|4|6
```  
The data returned is representative of your badge ID followed by the number of checkin for each numbered beacon.  The beacons were placed in the following areas or at the following events and were released incrimentally throughout the conference:

* AREA1 -- Hacker Brew Contest and THOTCON After Party
* AREA2 -- Main talk Track / Entrance area
* AREA3 -- Workshops and Roof Deck
* AREA4 -- Hacker Village
* AREA5 -- Chill Out Lounge
* AREA6 -- Track 2 area
* AREA7 -- VIP Sky Lounge
* AREA8 -- Hacker Alley
* AREA9 -- Main Area Bar
* AREA10 -- Food Stations 

More about how and when the badges would "checkin" will be revealed in the coming days.

We're releasing this data to satisfy curiosity and hope that someone may do something interesting with it.
  
A sqlite database of the checkins is available [here](http://badge.workshop88.com/reports)
