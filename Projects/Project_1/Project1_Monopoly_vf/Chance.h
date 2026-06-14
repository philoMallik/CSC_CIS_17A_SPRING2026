#ifndef CHANCE_H
#define CHANCE_H

#include <string>
using namespace std;

struct ChanceCard {
    int id; //Unique identifier for the card
    char description[256]; //Description of the card's effect
    int type; //Type of the card (e.g., 0 for money gain, 1 for money loss, 2 for move, etc.)
    int value; //Value associated with the card (e.g., amount of money gained/lost, number of spaces to move, etc.)
};

#endif // CHANCE_H

/*
List of Monopoly Chance cards (US)
1. Advance to Boardwalk.
2. Advance to Go (Collect $200).
3. Advance to Illinois Avenue. If you pass Go, collect $200.
4. Advance to St. Charles Place. If you pass Go, collect $200.
5. Advance to the nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay wonder twice the rental to which they are otherwise entitled.
6. Advance to the nearest Railroad. If unowned, you may buy it from the Bank. If owned, pay wonder twice the rental to which they are otherwise entitled.
7. Advance token to nearest Utility. If unowned, you may buy it from the Bank. If owned, throw dice and pay owner a total ten times amount thrown.
8. Bank pays you dividend of $50.
9. Get Out of Jail Free.
10. Go Back 3 Spaces.
11. Go to Jail. Go directly to Jail, do not pass Go, do not collect $200.
12. Make general repairs on all your property. For each house pay $25. For each hotel pay $100.
13. Speeding fine $15.
14. Take a trip to Reading Railroad. If you pass Go, collect $200.
15. You have been elected Chairman of the Board. Pay each player $50.
16. Your building loan matures. Collect $150

1.advance to location collect 200 if pass go
2.advanced to nearest railroad/utility
3.move x spaces


4.pay bank / collect from bank (+/- money)
5.pay for upgrades
6.pay other players / collect from other players (+/- money)



*/