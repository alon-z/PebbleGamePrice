/**
 * Welcome to Pebble.js!
 *
 * This is where you write your app.
 */

var UI = require('ui');
var ajax = require('ajax');
var Settings = require('settings');

// Set a configurable with the open callback
Settings.config(
  { url: 'https://alonikomax.github.io/PebbleGamePrice/'},
  function(e) {
    console.log('opening configurable');
    console.log(JSON.stringify(e));
    console.log('https://alonikomax.github.io/PebbleGamePrice/');
  },
  function(e) {
    console.log('closed configurable');
    console.log(JSON.stringify(Settings.option()));
    console.log(JSON.stringify(Settings.option('games')));
  },
  function(e) {
    console.log('error with configuration');
  }
);

if (Settings.option('games') === undefined) {
  Settings.option('games', [{'name': 'Grand Theft Auto V', 'title': 'GTA V', 'appid': 271590, 'price': 0}]);
}

var menu_items = [];

var formatPrice = function(price) {
	if (String(price).length < 3) {
		return 0 + '.' + String(price).slice(-String(price).length) + '$'; 
	}
	return String(price).slice(0,String(price).length - 2) + '.' + String(price).slice(-2) + '$';
};

for (var game in Settings.option('games')) {
  menu_items.push({
    title: Settings.option('games')[game].title,
    subtitle: formatPrice(Settings.option('games')[game].price)
  });
}

var menu = new UI.Menu({
    sections: [{
      items: menu_items
    }]
});

menu.redrawItem = function(index) {
  menu.item(0, index, {title: Settings.option('games')[index].title, subtitle: formatPrice(Settings.option('games')[index].price)});
};

var priceUpdator = function(gameIndex) {
		console.log(Settings.option('games')[gameIndex].title + " " + Settings.option('games')[gameIndex].appid);
    ajax({ url: "http://store.steampowered.com/api/appdetails?" + "appids=" + Settings.option('games')[gameIndex].appid + "&cc=us", type: 'json' },
      function(data) {
        var price = data[Settings.option('games')[gameIndex].appid].data.price_overview.final;
        console.log('Price: ' + price);
        Settings.option('games')[gameIndex].price = price;
        menu.redrawItem(gameIndex);
      }
    );
};

menu.updatePrices = function() {
	for (var gameIndex in Settings.option('games')) {
		priceUpdator(gameIndex);
	}
};

menu.on('select', function(e) {
  priceUpdator(e.itemIndex);
});

menu.updatePrices();
menu.show();