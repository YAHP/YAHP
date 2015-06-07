import json
import os
from thug import Thug

def set_plugins(plugin_name, plugin_version):
    plugin_args = []

    if plugin_name == 'adobepdf':
        if plugin_version != '0':
            plugin_args.append('-A')
            plugin_args.append(plugin_version)
        else:
            plugin_args.append('-P')

    elif plugin_name == 'shockwave':
        if plugin_version != '0':
            plugin_args.append('-S')
            plugin_args.append(plugin_version)
        else:
            plugin_args.append('-R')

    elif plugin_name == 'javaplugin':
        if plugin_version != '0':
            plugin_args.append('-J')
            plugin_args.append(plugin_version)
        else:
            plugin_args.append('-K')

    return plugin_args

def handle_request(request):
    args = []
    client_info = json.loads(request)

    os.environ['USER_AGENT'] = client_info['userAgent']
    os.environ['BROWSER_TAG'] = client_info['browserTag']

    args.append('-u')
    args.append(client_info['browserTag'])

    for plugin_name in client_info['plugins_info']:
        args.extend(set_plugins(plugin_name, client_info['plugins_info'][plugin_name]))

    args.append(client_info['url'])

    Thug(args)()

    return
