Pebble.addEventListener("ready",
    function(e) {
        console.log("Hello world! - Sent from your javascript application.");
    }
);


var s = 0;
setInterval(function() {
    s++;
    console.log("JavaScript is running for " + s + " seconds.");
}, 1000);