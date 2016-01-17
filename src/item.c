#include <pebble.h>
#include "item.h"
#include "checklist_layer.h"

#define MAX_ITEMS 50

Item* createItem(char* name, int id, int order) {
  Item* item = malloc(sizeof(Item));
  item->name = name;
  item->isChecked = false;
  item->id = id;
  item->order = order;
  
  return item;
}

void clearItems() {
  for(int i=0; i<itemCount; i++) {
    free(items[i]->name);
    free(items[i]);
    items[i] = NULL;
  }
  
  itemCount = 0;
}

void addItem(int id, char* name, int order, bool isChecked) {
  if (itemCount < MAX_ITEMS) {
    Item* item = malloc(sizeof(Item));
    item->id = id;
    item->name = malloc(strlen(name)+1);
    strcpy(item->name, name);
    item->order = order;
    item->isChecked = isChecked;
    items[itemCount] = item;
    itemCount++;
    sortItems();
    
    reloadMenu();
  }
}

void init_item_list() {
  itemCount = 0;
  items = malloc(MAX_ITEMS * sizeof(Item*));
  
  for(int i=0; i<MAX_ITEMS; i++) {
    items[i] = NULL;
  }  
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


