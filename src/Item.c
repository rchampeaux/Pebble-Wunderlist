#include <pebble.h>
#include "Item.h"

Item* createItem(char* name) {
  Item* item = malloc(sizeof(Item));
  item->name = name;
  item->isChecked = false;
  
  return item;
}

void init_item_list() {
  itemCount = 10;
  items = malloc(itemCount * sizeof(Item*));
  
  items[0] = createItem("Milk");
  items[1] = createItem("Bread");
  items[2] = createItem("Peanut Butter");
  items[3] = createItem("Eggs");
  items[4] = createItem("Ground Beef");
  items[5] = createItem("Raisen Bran");
  items[6] = createItem("Chicken Breasts");
  items[7] = createItem("Green Beans");
  items[8] = createItem("Chips");
  items[9] = createItem("Dip");
}

void moveToChecked(int row) {
  Item* item = items[row];
  for(int i=row+1; i < itemCount; i++) {
    items[i-1] = items[i];
  }  
  
  items[itemCount-1] = item;
}

void moveToUnchecked(int row) {
  int targetIndex = 0;
  for(; targetIndex<row; targetIndex++) {
    if (items[targetIndex]->isChecked) {
      break;
    }
  }
  
  Item* item = items[row];
  for(int i=targetIndex; i<row; i++) {
    items[i+1] = items[i];
  }
  
  items[targetIndex] = item;
  item->isChecked = false;
}



