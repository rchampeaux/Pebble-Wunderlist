console.log("Top of the .js file");

function sendClear() {
  console.log("sendClear()");
	Pebble.sendAppMessage({"clear": 0});
}

function sendAdd(name, id, order, isChecked) {
  console.log("sendAdd " + name + " " + id + " " + order + " " + isChecked);
	Pebble.sendAppMessage({
    "add": id,
    "name": name,
    "order": order,
    "isChecked": isChecked
  });
}

Pebble.addEventListener("ready",
							function(e) {
								console.log("ready");
                sendClear();
                sendAdd("Milk", 1, 1, 0);
                sendAdd("Bread", 2, 2, 0);
                sendAdd("Eggs", 3, 3, 0);
                sendAdd("Chips", 4, 4, 0);
                sendAdd("Dip", 5, 5, 0);
							});


Pebble.addEventListener("appmessage",
							function(e) {
								console.log("Received Status: " + e.payload.status);
							});
