import unittest
import requests

#base = "http://data.moojafzar.com:8139"
base = "http://localhost:8139"
defAuth = requests.auth.HTTPBasicAuth('test','test')

def check_status_code(res):
    if res.status_code != 200: #print "##### Error #####"
        print "\t",res.request.method,":",res.status_code,":",res.text
    #if res.text != None: print res.text

def test_url(url, jdata, rdata, param, methods):
    print url
    if jdata != None:
        if "put" in methods:
            res = requests.put(base + url,
                    auth = defAuth,
                    params = param,
                    json = jdata)
            check_status_code(res)
        if "post" in methods:
            res = requests.post(base + url,
                    auth = defAuth,
                    params = param,
                    json = jdata)
            check_status_code(res)
    else:
        #fdata = open('data/bg.png', 'rb').read()
        if "put" in methods:
            res = requests.put(base + url,
                    auth = defAuth,
                    headers = {
                        'content-type': 'application/octet-stream',
                        'content-length': str(len(rdata)),
                        },
                    params = param,
                    data = rdata)
            check_status_code(res)

        #fdata = open('data/bg.png', 'rb').read()
        if "post" in methods:
            res = requests.post(base + url,
                    auth = defAuth,
                    headers = {
                        'content-type': 'application/octet-stream',
                        'content-length': str(len(rdata)),
                        },
                    params = param,
                    data = rdata)
            check_status_code(res)
    if "get" in methods:
        res = requests.get(base + url,
                auth = defAuth,
                params = param,
                )
        check_status_code(res)

    if "del11" in methods:
        res = requests.delete(base + url,
                auth = defAuth,
                params = param,
                )
        check_status_code(res)

fdata = open('data/bg.png', 'rb').read()
test_url("/launcher/components/info", {"_id":2}, None, None, "get put post del")
test_url("/launcher/components/info/2", {"_id":2}, None, None, "get put post del")
test_url("/launcher/components/logo/2", None, fdata, {"language":2}, "get put post del")
test_url("/launcher/components/types", {"_id":2}, None, None, "get put post del")
test_url("/launcher/background/2", None,fdata,None,"get put post del")
test_url("/launcher/default", {"_id":2}, None, None, "get put post del")
test_url("/launcher/logo/2", None, fdata, {"language":2}, "get put post del")
test_url("/launcher/menu", {"_id":2}, None, None, "get put post del")
test_url("/launcher/menu/2", {"_id":2}, None, None, "get put post del")

test_url("/live/input/dvb", {"_id":2}, None, None, "get put post del")
test_url("/live/input/dvb/2", {"_id":2}, None, None, "get put post del")
test_url("/live/tuners/hardware/input", {"_id":2}, None, None, "get")
test_url("/live/tuners/hardware/output", {"_id":2}, None, None, "get")
test_url("/live/tuners/input", {"_id":2}, None, None, "get put post del")
test_url("/live/tuners/scan/2", {"_id":2}, None, None, "get")
test_url("/live/tuners/input/2", {"_id":2}, None, None, "get put post del")
test_url("/live/tuners/output", {"_id":2}, None, None, "get put post del")

test_url("/report/component", {"_id":2}, None, {"start-time":"0", "end-time":"2"}, "get")
test_url("/report/live", {"_id":2}, None, {"start-time":"0", "end-time":"2"}, "get")
test_url("/report/system", {"_id":2}, None, {"start-time":"0", "end-time":"2"}, "get")
test_url("/report/system_user", {"_id":2}, None, {"start-time":0, "end-time":2}, "get")
test_url("/report/user", {"_id":2}, None, {"start-time":0, "end-time":2}, "get")
test_url("/report/vod", {"_id":2}, None, {"start-time":0, "end-time":2}, "get")

test_url("/status/channels_input", {"_id":2}, None, None, "get ")
test_url("/status/channels_output", {"_id":2}, None, None, "get ")
test_url("/status/channels_output_view", {"_id":2}, None, None, "get ")
test_url("/status/channels_output_view/2", {"_id":2}, None, None, "get ")
test_url("/status/cpu_mem", {"_id":2}, None, {"start-time":0, "end-time":2}, "get ")
test_url("/status/dvb", {"_id":2}, None, {"start-time":0, "end-time":2}, "get ")
test_url("/status/error", {"_id":2}, None, {"start-time":0, "end-time":2}, "get ")
test_url("/status/information", {"_id":2}, None, None, "get ")
test_url("/status/network", {"_id":2}, None, {"start-time":0, "end-time":2}, "get ")
test_url("/status/storage", {"_id":2}, None, {"start-time":0, "end-time":2}, "get ")
test_url("/status/users", {"_id":2}, None, {"start-time":0, "end-time":2}, "get ")

test_url("/storage/advertize", {"_id":2}, None, None, "get put post del")
test_url("/storage/advertize/2", {"_id":2}, None, None, "get put post del")
test_url("/storage/contents/categories", {"_id":2}, None, None, "get put post del")
test_url("/storage/contents/categories/2", {"_id":2}, None, None, "get put post del")
test_url("/storage/contents/info", {"_id":2}, None, None, "get put post del")
test_url("/storage/contents/info/2", {"_id":2}, None, None, "get put post del")
test_url("/storage/contents/media/2", None, fdata, None, "get put post del")
test_url("/storage/contents/platforms", {"_id":2}, None, None, "get put post del")
test_url("/storage/contents/platforms/2", {"_id":2}, None, None, "get put post del")
test_url("/storage/contents/poster/2", None, fdata, None, "get put post del")
test_url("/storage/contents/subtitle/2", None, fdata, None, "get put post del")
test_url("/storage/contents/types", {"_id":2}, None, None, "get put post del")
test_url("/storage/contents/types/2", {"_id":2}, None, None, "get put post del")
test_url("/storage/setting", {"_id":2}, None, None, "get put post del")

test_url("/system/backup", None, fdata, None, "get put")
test_url("/system/firmware", None, fdata, None, "put")
test_url("/system/license", None, fdata, None, "get put")
test_url("/system/location", {"_id":2}, None, None, "get put post del")
test_url("/system/network", {"_id":2}, None, None, "get put post del")
test_url("/system/permission", {"_id":2}, None, None, "get put post del")
test_url("/system/permission/2", {"_id":2}, None, None, "get put post del")
test_url("/system/pms", {"_id":2}, None, None, "get put post del")
test_url("/system/reboot", {"_id":2}, None, None, "get ")
test_url("/system/logout", {"_id":2}, None, None, "get ")
test_url("/system/restart", {"_id":2}, None, None, "get ")
test_url("/system/stop", {"_id":2}, None, None, "get ")
test_url("/system/subtitle_logo", None,fdata, None, "get put post del")
test_url("/system/system_logo", None, fdata, None, "get put post del")
test_url("/system/users", {"_id":2}, None, None, "get put post del")
test_url("/system/users/me", {"_id":2}, None, None, "get put post del")
test_url("/system/users/2", {"_id":2}, None, None, "get put post del")
test_url("/system/vod_account", {"_id":2}, None, None, "get put post del")
test_url("/system/vod_account/2", {"_id":2}, None, None, "get put post del")
test_url("/system/weektime", {"_id":2}, None, None, "get put post del")
test_url("/system/weektime/2", {"_id":2}, None, None, "get put post del")
test_url("/users/group", {"_id":2}, None, None, "get put post del")
test_url("/users/group/2", {"_id":2}, None, None, "get put post del")
test_url("/users/message/broadcast", {"_id":2}, None, None, "get put post del")
test_url("/users/message/broadcast/2", {"_id":2}, None, None, "get put post del")
test_url("/users/message/from/2", {"_id":2}, None, None, "get put post del")
test_url("/users/message/to/2", {"_id":2}, None, None, "get put post del")
test_url("/users/user", {"_id":2}, None, None, "get put post del")
test_url("/users/user/2", {"_id":2}, None, None, "get put post del")
