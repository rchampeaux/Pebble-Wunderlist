#pragma once

typedef struct _Item {
  char* name;
  bool isChecked;
  int id;
  int order;
} Item;

int itemCount;
Item** items;

void init_item_list();

void sortItems();

void addItem(int id, char* name, int order, bool isChecked);
void clearItems();
