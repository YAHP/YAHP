// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/**
 * Get the current URL.
 *
 * @param {function(string)} callback - called when the URL of the current tab
 *   is found.
 **/
    
function getCurrentTabUrl(callback) {
  // Query filter to be passed to chrome.tabs.query - see
  // https://developer.chrome.com/extensions/tabs#method-query
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


function sendURL(URL) {
    var serverURL = 'http://118.161.167.239:8888';//+ '?url=' + encodeURIComponent(URL);
    //var serverURL = "http://people.cs.nctu.edu.tw/~nyhu/GSoC/return_hash.php";
    var x = new XMLHttpRequest();
    x.open('POST', serverURL, true);

    x.setRequestHeader("Content-type", "application/json;charset=UTF-8");
    x.onreadystatechange = function() {
        if (x.readyState == 4) {
            document.write(x.responseText);
        }
    }
    
    var useragent = navigator.userAgent;
    var acrobat_version = getAcrobatInfo().acrobatVersion;
    var flash_version = getFlashVersion();
    var java_version = deployJava.getJREs();

    if (-1 != acrobat_version.search("Chrome")) {
        acrobat_version = "0";
    }

    if (flash_version == "0,0,0") {
        flash_version = "0"; 
    }

    if (java_version) {
        java_version = "0";
    }
    
    x.send(JSON.stringify({"url":URL, "userAgent":useragent, "browserTag":"chrome42", "plugins_info":{"adobepdf":acrobat_version, "shockwave":flash_version, "javaplugin":java_version}}));    

}

function rendertext(id, statusText) {
    document.getElementById(id).textContent = statusText;
}

function BWcompare(URL) {
    var serverURL = "http://people.cs.nctu.edu.tw/~nyhu/GSoC/return_hash.php";
    var x = new XMLHttpRequest();
    x.open('POST', serverURL, true);

    x.setRequestHeader("Content-type","application/x-www-form-urlencoded");
    x.onreadystatechange = function() {
        if (x.readyState == 4) {
            //document.write(x.responseText);
            //rendertext("server", x.responseText);
            if(-1 != x.responseText.search("Not in")) {
                rendertext("server", "Not in Blacklist!");
                //sendURL(URL); //call Thug
            } else {
                //document.write("The website is in the Blacklist!")
                rendertext("server", "In Blacklist!");
            }
        }
    }

    x.send("URL="+URL);
}

function BWcompare2(URL) {
    var hash_value_sdbm = sdbm(URL);
    if(hashtable[hash_value_sdbm] == 1) {
        rendertext("client", "In Blacklist!");
    } else {
        var hash_value_djb2 = djb2(URL);
        if(hashtable[hash_value_djb2] == 1) {
            rendertext("client", "In Blacklist!");
        } else {  
            rendertext("client", "Not in Blacklist!");
        }
    }
}
/*
function BWcompare3(URL) {
    var hash_value_sdbm = sdbm(URL);
    if(cdn_hashtable[hash_value_sdbm] == 1) {
        //document.write("In Blacklist!");
        rendertext("cdn", "In Blacklist!");
    } else {
        var hash_value_djb2 = djb2(URL);
        if(cdn_hashtable[hash_value_djb2] == 1) {
            //document.write("In blacklist!");
            rendertext("cdn", "In Blacklist!");
        } else {
            //document.write("Not in Blacklist!");
            rendertext("cdn", "Not in Blacklist!");
        }
    }
}
*/
document.addEventListener('DOMContentLoaded', function() {
    //alert(hashtable);
    getCurrentTabUrl(function(url) {

        /* trim http:// */
        var sub_url = url.substr(7);

        if (sub_url.charAt(sub_url.length - 1) == '/') {
            sub_url = sub_url.substr(0,sub_url.length - 1);
        }
        if (sub_url.charAt(0) == '/') {
            sub_url = sub_url.substr(1);
        }

        BWcompare(sub_url);
        BWcompare2(sub_url);
        //BWcompare3(sub_url);
    });
});
