var SLOT_NUM = 98317;
var INT_MAX = 4294967296;

function djb2(str) {
    var hash = 5381;

    var i = 0;
    for(; i < str.length; i++) {
        hash = hash*33 + str.charCodeAt(i);
        while(hash > INT_MAX - 1){
            hash = hash - INT_MAX;
        }
    }
    return hash % SLOT_NUM;
}

function sdbm(str) {
    var hash = 0;

    var i = 0;
    for(; i < str.length; i++) {
        hash = hash*64 + hash*65536 - hash + str.charCodeAt(i);
        
        while(hash > INT_MAX - 1){
            hash = hash - INT_MAX;
        }
    }

    return hash % SLOT_NUM;
}
