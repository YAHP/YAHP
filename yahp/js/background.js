chrome.webRequest.onBeforeRequest.addListener(
    function(details) {
        //console.log(details.url);
        //console.log(details.type);

        var is_script = ("script" == details.type);
        var is_inBlacklist = BWcompare_front2(trim(details.url));
        var to_block = is_script || is_inBlacklist;

        console.log(is_script, is_inBlacklist, to_block);

        return { cancel: to_block };
    },
    {
        urls: ["<all_urls>"]
        //types: ["script"]
    }
    ,
    ["blocking"]);        

function trim(url) {
    var sub_url = url.substr(7);

    if (sub_url.charAt(sub_url.length - 1) == '/') {
        sub_url = sub_url.substr(0,sub_url.length - 1);
    }
    if (sub_url.charAt(0) == '/') {
        sub_url = sub_url.substr(1);
    }

    return sub_url;
}

function BWcompare_front2(url) {
    var hash_value_sdbm = sdbm(url);
    //console.log(url); 
    if(hashtable[hash_value_sdbm] == 1) {
        return true;
    }
    
    else {
        var hash_value_djb2 = djb2(url);
        if(hashtable[hash_value_djb2] == 1) {
            return true;
        } else {
            return false;
        }
    }
}

