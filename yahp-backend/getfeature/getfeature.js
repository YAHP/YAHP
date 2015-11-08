var URL = process.argv[2] || 'http://www.google.com';

var request = require('request');

var iframe_num = 0,
    hidden_num = 0,
    script_num = 0,
    script_ratio = 0,
    whitespace_ratio = 0,
    embed_num = 0,
    script_char_num = 0,
    char_num = 0;

var script_tag = false;

function parse_js(js_code) {
    var esprima = require('esprima');
    //console.log(js_code);
    //console.log("************************************************");
    //console.log(JSON.stringify(esprima.parse(js_code), null, 4)); 
}

function parse(to_parse) {
    var htmlparser = require("htmlparser2");
    var parser = new htmlparser.Parser({
        onopentag: function(name, attribs) {
            if(name === "iframe") {
                iframe_num ++;
            }
            else if(name === "script") {
                script_tag = true;
                script_num ++;
            } 
            else if(attribs.hasOwnProperty('scr')) {
                var include_name = attribs.scr;
                if(include_name.substr(include_name.length - 3) == ".js") {
                    script_num ++;
                }
            }
            else if(attribs.hasOwnProperty('inline')) {
                var include_name = attribs.inline;
                if(include_name.substr(include_name.length - 3) == ".js") {
                    script_num ++;
                }
            }
            if(attribs.type === "hidden") {
                hidden_num ++;
            }
            
        },
        ontext: function(text) {
            if(script_tag) {
                script_char_num += text.length;
                parse_js(text);
            }
            char_num += text.length;
        },
        onclosetag: function(tagname) {
            if(script_tag && tagname === "script" ) {
                script_tag = false;
            }
        }
    }, {decodeEntities: true});
    parser.write(to_parse);
    parser.end();
}

request(URL, function (error, response, body) {
    if (!error && response.statusCode == 200) {
        console.log(body) // Show the HTML for the Google homepage. 
        char_num = body.length;
        var whitespace_num = char_num - body.replace(/\s+/g, '').length; 
        whitespace_ratio = whitespace_num * 100 / char_num;

        parse(body);

        script_ratio = script_char_num * 100 / char_num;
        console.log("iframe_number: " + iframe_num); 
        console.log("hidden_number: " + hidden_num);
        console.log("script_number: " + script_num);
        console.log("script_ratio: " + script_ratio.toFixed(2) + "%");
        console.log("whitespace_ratio: " + whitespace_ratio.toFixed(2) + "%");
        console.log("embed_number: " + embed_num);
        console.log("char_number: " + char_num);
    }
})
