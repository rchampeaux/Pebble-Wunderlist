#pragma once

typedef struct _Item {
  char* name;
  bool isChecked;
} Item;

int itemCount;
Item** items;

void init_item_list();

void moveToChecked(int row);
void moveToUnchecked(int row);
