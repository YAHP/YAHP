import json
import logging

from ThugAPI import *
from Plugins.ThugPlugins import *

log = logging.getLogger("Thug")
log.setLevel(logging.WARN)

class YAHP(ThugAPI):
    def __init__(self, args):
        ThugAPI.__init__(self, args)

    def analyze(self):
        request = json.loads(self.args)

        for plugin, plugin_version in request['plugin_info'].items(): 
            p = getattr(self, "set_%s" % (plugin, ), None)
            if p and plugin_version:
                p(plugin_version)

        with open('DOM/personalities/dynamic.json') as personality_template:
            dynamic_personality = json.load(personality_template)

        for personality, personality_value in request['personality_info'].items():
            dynamic_personality[personality] = personality_value

        with open('DOM/personalities/' + request['personality_info']['browserTag'] + '.json', 'w') as new_personality:
            json.dump(dynamic_personality, new_personality)

        self.set_useragent(request['personality_info']['browserTag'])

        self.set_file_logging()
        self.set_json_logging()

        self.log_init(request['url'])
        self.run_remote(request['url'])
        self.log_event()

        return log

