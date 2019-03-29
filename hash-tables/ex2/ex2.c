#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(16);
  char **route = malloc(length * sizeof(char *));

  // loop over list of tickets to create hash table
  for (int i = 0; i < length; i++)
  {
    // insert into hash table where:
    // key = source
    // value = destination
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
  }

  // fill in the first slot in route with the route origin (destination with NONE source)
  route[0] = hash_table_retrieve(ht, "NONE");

  // loop over list of tickets to determine route
  for (int i = 1; i < length; i++)
  {
    // per hint: when constructing the entire route, the ith location in the route can be found by checking the hash table for the i-1th location.
    route[i] = hash_table_retrieve(ht, route[i - 1]);
  }

  destroy_hash_table(ht); // if you malloc, you must free
  print_route(route, length);
  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++)
  {
    printf("%s\n", route[i]);
  }
}

#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  return 0;
}
#endif
