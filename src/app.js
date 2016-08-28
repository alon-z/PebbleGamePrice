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
  { url: 'https://alonikomax.github.io/PebbleGamePrice/' + "?" + encodeURIComponent(JSON.stringify(Settings.option('games')))},
  function(e) {
    console.log('opening configurable');
    console.log('https://alonikomax.github.io/PebbleGamePrice/' + "?" + encodeURIComponent(JSON.stringify(Settings.option('games'))));
  },
  function(e) {
    console.log('closed configurable');
    console.log(Settings.option());
    console.log(Settings.option('games'));
  },
  function(e) {
    console.log('error with configuration');
  }
);

if (!Settings.option('games')) {
  Settings.option('games', {'GTA V': 271590},{'ARK': 346110});
}

var games = [
	{
		'title': 'GTA V',
		'appid': 271590,
		'price': 0
	},
	{
		'title': 'ARK',
		'appid': 346110,
		'price': 0
	}
];

var menu_items = [];

var formatPrice = function(price) {
	if (String(price).length < 3) {
		return 0 + '.' + String(price).slice(-String(price).length) + '$'; 
	}
	return String(price).slice(0,String(price).length - 2) + '.' + String(price).slice(-2) + '$';
};

for (var game in games) {
  menu_items.push({
    title: games[game].title,
    subtitle: formatPrice(games[game].price)
  });
}

var menu = new UI.Menu({
    sections: [{
      items: menu_items
    }]
});

menu.redrawItem = function(index) {
  menu.item(0, index, {title: games[index].title, subtitle: formatPrice(games[index].price)});
};

var priceUpdator = function(gameIndex) {
		console.log(games[gameIndex].title + " " + games[gameIndex].appid);
    ajax({ url: "http://store.steampowered.com/api/appdetails?" + "appids=" + games[gameIndex].appid + "&cc=us", type: 'json' },
      function(data) {
        var price = data[games[gameIndex].appid].data.price_overview.final;
        console.log('Price: ' + price);
        games[gameIndex].price = price;
        menu.redrawItem(gameIndex);
      }
    );
};

menu.updatePrices = function() {
	for (var gameIndex in games) {
		priceUpdator(gameIndex);
	}
};

menu.on('select', function(e) {
  priceUpdator(e.itemIndex);
});

menu.updatePrices();
menu.show();