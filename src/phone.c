#include <pebble.h>
#include "phone.h"
#include "item.h"

enum {
	CLEAR_KEY = 0,	
	ADD_KEY = 1,
  UPDATE_KEY = 2,
  NAME_KEY = 3,
  ORDER_KEY = 4,
  IS_CHECKED_KEY = 5
};

void send_message(int message) {
// 	DictionaryIterator *iter;
	
// 	app_message_outbox_begin(&iter);
// 	dict_write_uint8(iter, STATUS_KEY, message);
	
// 	dict_write_end(iter);
//   	app_message_outbox_send();
}

static void in_received_handler(DictionaryIterator *received, void *context) {
	Tuple *tuple;
	
	tuple = dict_find(received, CLEAR_KEY);
	if(tuple) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Clear"); 
}
	
	tuple = dict_find(received, ADD_KEY);
	if(tuple) {
    Tuple* nameTuple = dict_find(received, NAME_KEY);
    Tuple* orderTuple = dict_find(received, ORDER_KEY);
    Tuple* isCheckedTuple = dict_find(received, IS_CHECKED_KEY);
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Add: %d %s %d %d", 
            tuple->value->int16,
           nameTuple->value->cstring,
           orderTuple->value->int16,
           isCheckedTuple->value->int16);
    
    addItem(tuple->value->int16,
           nameTuple->value->cstring,
           orderTuple->value->int16,
           isCheckedTuple->value->int16 > 0 ? true : false);
	}
}

// Called when an incoming message from PebbleKitJS is dropped
static void in_dropped_handler(AppMessageResult reason, void *context) {	
}

// Called when PebbleKitJS does not acknowledge receipt of a message
static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
}

void init_phone_connection() {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "init_phone_connection()"); 
  // Register AppMessage handlers
	app_message_register_inbox_received(in_received_handler); 
	app_message_register_inbox_dropped(in_dropped_handler); 
	app_message_register_outbox_failed(out_failed_handler);
		
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());

}

void deinit_phone_connection() {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "deinit_phone_connection()"); 
	app_message_deregister_callbacks();
}
