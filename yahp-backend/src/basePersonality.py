class basePersonality(dict):
    def __init__(self, userAgent, browserTag):
        self[browserTag] = {
                "id"              : 0,
                "description"     : None,
                "version"         : None,
                "userAgent"       : userAgent,
                "appCodeName"     : None,
                "appName"         : None,
                "appVersion"      : None,
                "appMinorVersion" : None,
                "platform"        : None,
                "product"         : None,
                "productSub"      : None,
                "vendor"          : None,
                "vendorSub"       : None,
                "oscpu"           : None,
                "buildID"         : None,
                "javaUserAgent"   : None,
                "cc_on"           : None,
                "browserTag"      : browserTag,
                }
