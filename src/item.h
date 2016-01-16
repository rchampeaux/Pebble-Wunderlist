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
void moveToChecked(int row);
void moveToUnchecked(int row);
