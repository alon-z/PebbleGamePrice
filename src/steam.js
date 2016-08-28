Pebble.addEventListener("ready", function(e) {
  connectSteam();
});

Pebble.addEventListener("appmessage", function(e) {
  connectSteam();
});

Pebble.addEventListener("webviewclosed", function(e) {
  console.log("webview closed");
});

function connectSteam() {
  var req = new XMLHttpRequest();
  var appid = 271590;
  req.open('GET', "http://store.steampowered.com/api/appdetails?" + "appids=" + appid + "&cc=" + "us", true);
  req.onload = function(e) {
    if (req.readyState == 4) {
      if(req.status == 200) {
        console.log(req.responseText);

        var response = JSON.parse(req.responseText);

        var price = response[appid].data.price_overview.final;

        console.log(price);
        Pebble.sendAppMessage({
          "PRICE": price
        });

      } else {
        console.log("Error");
      }
    }
  };
  req.send(null);
}