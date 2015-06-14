function getCurrentTabUrl(callback) {
    var queryInfo = {
        active: true,
        currentWindow: true
    };

    chrome.tabs.query(queryInfo, function(tabs) {
        var tab = tabs[0];
        var url = tab.url;
        console.assert(typeof url == 'string', 'tab.url should be a string');
        callback(url);
    });
}


function sendURL(searchTerm) {
    var serverURL = 'http://YOUR_SERVER';
    var x = new XMLHttpRequest();
    x.open('POST', serverURL, true);
    x.onreadystatechange = function() {
        if (x.readyState == 4) {
            document.write(x.responseText);
        }
    }
    x.send();
}

document.addEventListener('DOMContentLoaded', function() {
    getCurrentTabUrl(function(url) {
        /* trim http:// */
        var sub_url = url.substr(7);

        if (sub_url.charAt(sub_url.length - 1) == '/') {
            sub_url = sub_url.substr(0,sub_url.length - 1);
        }
        if (sub_url.charAt(0) == '/') {
            sub_url = sub_url.substr(1);
        }
        sendURL(sub_url);
    });
});
