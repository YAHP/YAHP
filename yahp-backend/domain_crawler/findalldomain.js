var ip = process.argv[2] || '140.113.235.120';
var ip_array = ip.split('.');

var url = "https://www.robtex.com/en/advisory/ip/";
for(var i = 0; i < 4; i++) {
    url += ip_array[i];
    url += "/"
}

var request = require('request');
request(url, function (error, response, body) {
    if (!error && response.statusCode == 200) {
        parse(body);
    }
})

function parse(to_parse) {
    var htmlparser = require("htmlparser2");
    var ol = false;
    var xbul_count = 0;
    var parser = new htmlparser.Parser({
        onopentag: function(name, attribs) {
            if(name === "ol" && attribs.class === "xbul") {
                ol = true;
                xbul_count++;
            }
        },
        ontext: function(text) {
            if(ol && xbul_count == 2) {
                text = "http://" + text;
                console.log(text);
            }
        },
        onclosetag: function(tagname) {
            if(ol && tagname === "ol" ) {
                ol = false;
            }
        }
    }, {decodeEntities: true});
    parser.write(to_parse);
    parser.end();
}
