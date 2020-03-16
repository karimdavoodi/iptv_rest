import unittest
import requests


class TestLauncher(unittest.TestCase):
    
    defAuth = requests.auth.HTTPBasicAuth('test','test')

    def check_status_code(self, res):
        if res.status_code != 200:
            print res.status_code," --> ", res.url
            if res.text != None: print res.text

        self.assertEqual(res.status_code, 200, "statuc code != 200 ")

    def xtest_post_default(self):
        res = requests.post(
                "http://localhost:8139/launcher/default",
                auth = self.defAuth,
                json =  {
                "id": "int",
                "launcher": "main",
                "fontFa": "string",
                "fontEn": "string",
                "language": "string",
                "welcomeEn": "string",
                "welcomeFa": "string",
                "welcomeAr": "string",
                "userEn": "string",
                "userFa": "string",
                "userAr": "string",
                "playWelcomeClip": "boolean",
                "uiStartup": "string",
                "unitName": "string",
                "clientHotspot": "string",
                "testUserId": "int",
                "defaultChannel": "string"
                }
                )
        self.check_status_code(res)

    def xtest_get_default(self):
        res = requests.get(
                "http://localhost:8139/launcher/default",
                auth = self.defAuth,
                params = {}
                )
        
        self.check_status_code(res)
        self.assertEqual(res.json()['launcher'], 'main', "OK")


    def xtest_post_background(self):
        fdata = open('data/bg.png', 'rb').read()
        assert( len(fdata) > 1000 )
        res = requests.post(
                "http://localhost:8139/launcher/background",
                auth = self.defAuth,
                params = { 'launcher': 'main' },
                headers={'Content-Type': 'application/octet-stream'},
                data = fdata
                #files = {'file': ('background.png', 
                #        open('data/bg.png', 'rb') 
                #        )
                #    }
                )
        self.check_status_code(res)
    def xtest_get_background(self):
        res = requests.get(
                "http://localhost:8139/launcher/background",
                auth = self.defAuth,
                params = { 'launcher':'main' }
                )
        self.check_status_code(res)
        assert( len(res.content) > 1000 )

    def test_post_background(self):
        fdata = open('data/bg.png', 'rb').read()
        assert( len(fdata) > 1000 )
        res = requests.post(
                "http://localhost:8139/launcher/logo",
                auth = self.defAuth,
                params = { 'launcher': 'main', 'language':'en' },
                headers={'Content-Type': 'application/octet-stream'},
                data = fdata
                )
        self.check_status_code(res)
    def test_get_background(self):
        res = requests.get(
                "http://localhost:8139/launcher/logo",
                auth = self.defAuth,
                params = { 'launcher': 'main', 'language':'en' }
                )
        self.check_status_code(res)
        assert( len(res.content) > 1000 )


if __name__ == "__main__":
    unittest.main()
     

#http --auth "test:test"  "http://localhost:8139/status/information"
#http --auth "test:test"  "http://localhost:8139/status/cpu_mem"
#http --auth "test:test"  "http://localhost:8139/status/network"
#http --auth "test:test"  "http://localhost:8139/status/storage"
#http --auth "test:test"  "http://localhost:8139/status/dvb"
#http --auth "test:test"  "http://localhost:8139/status/channels/input"
#http --auth "test:test"  "http://localhost:8139/status/channels/output"
#http --auth "test:test"  "http://localhost:8139/status/channels/output/view"
#http --auth "test:test"  "http://localhost:8139/status/users"
#http --auth "test:test"  "http://localhost:8139/status/errors"
#http --auth "test:test"  "http://localhost:8139/report/user"
#http --auth "test:test"  "http://localhost:8139/report/system"
#http --auth "test:test"  "http://localhost:8139/report/live"
#http --auth "test:test"  "http://localhost:8139/report/vod"
#http --auth "test:test"  "http://localhost:8139/report/component"
#http --auth "test:test"  "http://localhost:8139/report/system_user"
#http --auth "test:test"  "http://localhost:8139/system/location"
#http --auth "test:test"  "http://localhost:8139/system/system_logo"
#http --auth "test:test"  "http://localhost:8139/system/subtitle_logo"
#http --auth "test:test"  "http://localhost:8139/system/network"
#http --auth "test:test"  "http://localhost:8139/system/users"
#http --auth "test:test"  "http://localhost:8139/system/users/id"
#http --auth "test:test"  "http://localhost:8139/system/pms"
#http --auth "test:test"  "http://localhost:8139/system/vod_account"
#http --auth "test:test"  "http://localhost:8139/system/vod_account/id"
#http --auth "test:test"  "http://localhost:8139/system/permission"
#http --auth "test:test"  "http://localhost:8139/system/permission/id"
#http --auth "test:test"  "http://localhost:8139/system/weektime"
#http --auth "test:test"  "http://localhost:8139/system/weektime/id"
#http --auth "test:test"  "http://localhost:8139/storage/setting"
#http --auth "test:test"  "http://localhost:8139/storage/timeshift/setting"
#http --auth "test:test"  "http://localhost:8139/storage/timeshift/files"
#http --auth "test:test"  "http://localhost:8139/storage/npvr/setting"
#http --auth "test:test"  "http://localhost:8139/storage/npvr/files"
#http --auth "test:test"  "http://localhost:8139/storage/avod/import"
#http --auth "test:test"  "http://localhost:8139/storage/avod/files"
#http --auth "test:test"  "http://localhost:8139/storage/audio_book/import"
#http --auth "test:test"  "http://localhost:8139/storage/audio_book/files"
#http --auth "test:test"  "http://localhost:8139/storage/book/import"
#http --auth "test:test"  "http://localhost:8139/storage/book/files"
#http --auth "test:test"  "http://localhost:8139/storage/advertize/import"
#http --auth "test:test"  "http://localhost:8139/storage/advertize/files"
#http --auth "test:test"  "http://localhost:8139/storage/advertize/files/id"
#http --auth "test:test"  "http://localhost:8139/system/backup"
#http --auth "test:test"  "http://localhost:8139/system/license"
#http --auth "test:test"  "http://localhost:8139/system/firmware"
#http --auth "test:test"  "http://localhost:8139/system/restart"
#http --auth "test:test"  "http://localhost:8139/system/stop"
#http --auth "test:test"  "http://localhost:8139/system/reboot"
#http --auth "test:test"  "http://localhost:8139/system/logout"
#http --auth "test:test"  "http://localhost:8139/live/input_tuners"
#http --auth "test:test"  "http://localhost:8139/live/input_tuners_scan/id"
#http --auth "test:test"  "http://localhost:8139/live/output_tuners"
#http --auth "test:test"  "http://localhost:8139/live/inputs/dvb"
#http --auth "test:test"  "http://localhost:8139/live/inputs/dvb/id"
#http --auth "test:test"  "http://localhost:8139/live/inputs/archive"
#http --auth "test:test"  "http://localhost:8139/live/inputs/archive/id"
#http --auth "test:test"  "http://localhost:8139/live/inputs/network"
#http --auth "test:test"  "http://localhost:8139/live/inputs/network/id"
#http --auth "test:test"  "http://localhost:8139/live/inputs/iptv"
#http --auth "test:test"  "http://localhost:8139/live/inputs/iptv/id"
#http --auth "test:test"  "http://localhost:8139/live/inputs/virtual_net"
#http --auth "test:test"  "http://localhost:8139/live/inputs/virtual_net/id"
#http --auth "test:test"  "http://localhost:8139/live/inputs/virtual_dvb"
#http --auth "test:test"  "http://localhost:8139/live/inputs/virtual_dvb/id"
#http --auth "test:test"  "http://localhost:8139/live/transcode"
#http --auth "test:test"  "http://localhost:8139/live/transcode/id"
#http --auth "test:test"  "http://localhost:8139/live/cccam"
#http --auth "test:test"  "http://localhost:8139/live/cccam/id"
#http --auth "test:test"  "http://localhost:8139/live/unscramble"
#http --auth "test:test"  "http://localhost:8139/live/unscramble/id"
#http --auth "test:test"  "http://localhost:8139/live/scramble"
#http --auth "test:test"  "http://localhost:8139/live/scramble/id"
#http --auth "test:test"  "http://localhost:8139/live/output/silver"
#http --auth "test:test"  "http://localhost:8139/live/output/silver/id"
#http --auth "test:test"  "http://localhost:8139/live/output/gold"
#http --auth "test:test"  "http://localhost:8139/live/output/gold/id"
#http --auth "test:test"  "http://localhost:8139/live/icons"
#http --auth "test:test"  "http://localhost:8139/live/icons/id"

#http --auth "test:test"  "http://localhost:8139/launcher/default" 
#http --auth "test:test"  "http://localhost:8139/launcher/default" 
#http --auth "test:test"  "http://localhost:8139/launcher/background GET & POST"
#http --auth "test:test"  "http://localhost:8139/launcher/logo"
#http --auth "test:test"  "http://localhost:8139/launcher/make"
#http --auth "test:test"  "http://localhost:8139/launcher/make/id"
#http --auth "test:test"  "http://localhost:8139/launcher/arrange"
#http --auth "test:test"  "http://localhost:8139/launcher/arrange/id"

#http --auth "test:test"  "http://localhost:8139/users/group"
#http --auth "test:test"  "http://localhost:8139/users/group/id"
#http --auth "test:test"  "http://localhost:8139/users/user"
#http --auth "test:test"  "http://localhost:8139/users/user/id"
#http --auth "test:test"  "http://localhost:8139/users/message/to/userid"
#http --auth "test:test"  "http://localhost:8139/users/message/to/userid/msg_id"
#http --auth "test:test"  "http://localhost:8139/users/message/from/userid"
#http --auth "test:test"  "http://localhost:8139/users/message/broadcast"
#http --auth "test:test"  "http://localhost:8139/users/message/broadcast/msg_id"

