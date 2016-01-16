#include <pebble.h>
#include "item.h"

Item* createItem(char* name, int id, int order) {
  Item* item = malloc(sizeof(Item));
  item->name = name;
  item->isChecked = false;
  item->id = id;
  item->order = order;
  
  return item;
}

void init_item_list() {
  itemCount = 10;
  items = malloc(itemCount * sizeof(Item*));
  
  items[0] = createItem("Milk", 1, 1);
  items[1] = createItem("Bread", 2, 2);
  items[2] = createItem("Peanut Butter", 3, 3);
  items[3] = createItem("Eggs", 4, 4);
  items[4] = createItem("Ground Beef", 9, 9);
  items[5] = createItem("Raisen Bran", 5, 5);
  items[6] = createItem("Chicken Breasts", 8, 8);
  items[7] = createItem("Green Beans", 10, 10);
  items[8] = createItem("Chips", 6, 6);
  items[9] = createItem("Dip", 7, 7);
  
  sortItems();
}

int compareItem(Item* item1, Item* item2) {
  if (item1->isChecked == item2->isChecked) {
    if (item1->order > item2->order) {
      return 1;
    }
    else if (item1->order < item2->order) {
      return -1;
    }
    else {
      return 0;
    }
  }
  else if (item1->isChecked) {
    return 1;
  } 
  else {
    return -1;
  }
}

void sortItems() {
  for(int i=0; i<itemCount-1; i++) {
    for(int j=i+1; j<itemCount; j++) {
      if (compareItem(items[i],items[j]) > 0) {
        Item* temp = items[i];
        items[i] = items[j];
        items[j] = temp;
      }
    }
  }
}


