import unittest
import requests

class TestLive(unittest.TestCase):
    
    defAuth = requests.auth.HTTPBasicAuth('test','test')

    def check_status_code(self, res):
        if res.status_code != 200: #print "##### Error #####"
            print res.request.method,":",res.status_code," -> ", res.url
            if res.text != None: print res.text
        #self.assertEqual(res.status_code, 200, "statuc code != 200 ")

    def test_users_message_broadcast_put(self):
        res = requests.put(
                "http://localhost:8139/users/message/broadcast/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "group": [ 1,3 ],
                "time": 15800000,
                "weektime": [ 1,2 ],
                "expire": 15800000,
                "subject": "", 
                "body": "",
                }
                )
        self.check_status_code(res)
    def test_users_message_broadcast_post(self):
        res = requests.post(
                "http://localhost:8139/users/message/broadcast/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "group": [ 1,3 ],
                "time": 15800000,
                "weektime": [ 1,2 ],
                "expire": 15800000,
                "subject": "", 
                "body": "",
                }
                )
        self.check_status_code(res)

    def xtest_users_message_broadcast_del(self):
        res = requests.delete(
                "http://localhost:8139/users/message/broadcast/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
    def test_users_message_broadcast_get(self):
        res = requests.get(
                "http://localhost:8139/users/message/broadcast/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
        res = requests.get(
                "http://localhost:8139/users/message/broadcast",
                auth = self.defAuth,
                params = { 'from': 1, 'to':10 },
                )
        self.check_status_code(res)
"""
class TestUsers(unittest.TestCase):
    
    defAuth = requests.auth.HTTPBasicAuth('test','test')

    def check_status_code(self, res):
        if res.status_code != 200: #print "##### Error #####"
            print res.request.method,":",res.status_code," -> ", res.url
            if res.text != None: print res.text
        #self.assertEqual(res.status_code, 200, "statuc code != 200 ")

    def test_users_message_broadcast_put(self):
        res = requests.put(
                "http://localhost:8139/users/message/broadcast/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "group": [ 1,3 ],
                "time": 15800000,
                "weektime": [ 1,2 ],
                "expire": 15800000,
                "subject": "", 
                "body": "",
                }
                )
        self.check_status_code(res)
    def test_users_message_broadcast_post(self):
        res = requests.post(
                "http://localhost:8139/users/message/broadcast/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "group": [ 1,3 ],
                "time": 15800000,
                "weektime": [ 1,2 ],
                "expire": 15800000,
                "subject": "", 
                "body": "",
                }
                )
        self.check_status_code(res)

    def xtest_users_message_broadcast_del(self):
        res = requests.delete(
                "http://localhost:8139/users/message/broadcast/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
    def test_users_message_broadcast_get(self):
        res = requests.get(
                "http://localhost:8139/users/message/broadcast/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
        res = requests.get(
                "http://localhost:8139/users/message/broadcast",
                auth = self.defAuth,
                params = { 'from': 1, 'to':10 },
                )
        self.check_status_code(res)
        #########################################
    def test_users_message_from_put(self):
        res = requests.put(
                "http://localhost:8139/users/message/from/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "time": 1580000,
                "subject": "string", 
                "body": "string",
                }
                )
        self.check_status_code(res)
    def test_users_message_from_post(self):
        res = requests.post(
                "http://localhost:8139/users/message/from/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "time": 1580000,
                "subject": "string", 
                "body": "string",
                }
                )
        self.check_status_code(res)

    def xtest_users_message_from_del(self):
        res = requests.delete(
                "http://localhost:8139/users/message/from/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
    def test_users_message_from_get(self):
        res = requests.get(
                "http://localhost:8139/users/message/from/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
        res = requests.get(
                "http://localhost:8139/users/message/from/1",
                auth = self.defAuth,
                params = { 'from': 1, 'to':10 },
                )
        self.check_status_code(res)
        #########################################
    def test_users_message_to_put(self):
        res = requests.put(
                "http://localhost:8139/users/message/to/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "time": 1580000,
                "subject": "string", 
                "body": "string",
                }
                )
        self.check_status_code(res)
    def test_users_message_to_post(self):
        res = requests.post(
                "http://localhost:8139/users/message/to/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "time": 1580000,
                "subject": "string", 
                "body": "string",
                }
                )
        self.check_status_code(res)

    def xtest_users_message_to_del(self):
        res = requests.delete(
                "http://localhost:8139/users/message/to/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
    def test_users_message_to_get(self):
        res = requests.get(
                "http://localhost:8139/users/message/to/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
        res = requests.get(
                "http://localhost:8139/users/message/to/1",
                auth = self.defAuth,
                params = { 'from': 1, 'to':10 },
                )
        self.check_status_code(res)
        #########################################
    def test_users_user_put(self):
        res = requests.put(
                "http://localhost:8139/users/user/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "active": True,
                "name": "string", 
                "group": [1, 2 ],
                "connections": 1, 
                "ipaddress": "string", 
                "language": "string", 
                "launcher": 1, 
                "user": "string", 
                "pass": "string", 
                "vod_id": 1,
                "npvr": 1,
                "expire": 15800000,
                }
                )
        self.check_status_code(res)
    def test_users_user_post(self):
        res = requests.post(
                "http://localhost:8139/users/user/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "active": True,
                "name": "string", 
                "group": [1, 2 ],
                "connections": 1, 
                "ipaddress": "string", 
                "language": "string", 
                "launcher": 1, 
                "user": "string", 
                "pass": "string", 
                "vod_id": 1,
                "npvr": 1,
                "expire": 15800000,
                }
                )
        self.check_status_code(res)
    def xtest_users_user_del(self):
        res = requests.delete(
                "http://localhost:8139/users/user/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
    def test_users_user_get(self):
        res = requests.get(
                "http://localhost:8139/users/user/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
        res = requests.get(
                "http://localhost:8139/users/user/1",
                auth = self.defAuth,
                params = { 'from': 1, 'to':10 },
                )
        self.check_status_code(res)
    def test_users_group_put(self):
        res = requests.put(
                "http://localhost:8139/users/group/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "active": True,
                "name": "string", 
                "permission": [1, 2],
                "weektime": [1, 2] 
                }
                )
        self.check_status_code(res)
    def test_users_group_post(self):
        res = requests.post(
                "http://localhost:8139/users/group/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "active": False,
                "name": "string", 
                "permission": [1, 2],
                "weektime": [1, 2] 
                }
                )
        self.check_status_code(res)
    def xtest_users_group_del(self):
        res = requests.delete(
                "http://localhost:8139/users/group/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
    def test_users_group_get(self):
        res = requests.get(
                "http://localhost:8139/users/group/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
        res = requests.get(
                "http://localhost:8139/users/group/1",
                auth = self.defAuth,
                params = { 'from': 1, 'to':10 },
                )
        self.check_status_code(res)
    def xtest_all_del_methods(self):
        self.xtest_users_message_to_del()
        self.xtest_users_user_del()
        self.xtest_users_group_del()
        self.xtest_users_message_from_del()
        self.xtest_users_message_broadcast_del()
class TestLauncher(unittest.TestCase):
    
    defAuth = requests.auth.HTTPBasicAuth('test','test')

    def check_status_code(self, res):
        if res.status_code != 200:
            print res.status_code," --> ", res.url
            if res.text != None: print res.text

        self.assertEqual(res.status_code, 200, "statuc code != 200 ")

    def test_post_default(self):
        res = requests.post(
                "http://localhost:8139/launcher/default",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "launcher": "string",
                "font":{
                    "en": "string",
                    "fa": "string",
                    "ar": "string"
                    },
                "welcome":{
                    "en": "string",
                    "fa": "string",
                    "ar": "string"
                    },
                "user":{
                    "en": "string",
                    "fa": "string",
                    "ar": "string"
                    },
                "language": "string",
                "welcomeClip": True,
                "uiStartup": "string",
                "unitName": "string",
                "clientHotspot": "string",
                "testUserId": "int",
                "defaultChannel": "int" 
                }
                )
        self.check_status_code(res)

    def test_get_default(self):
        res = requests.get(
                "http://localhost:8139/launcher/default",
                auth = self.defAuth,
                params = {}
                )
        
        self.check_status_code(res)
        self.assertEqual(res.json()['launcher'], 'string', "OK")


    def test_post_background(self):
        fdata = open('data/bg.png', 'rb').read()
        assert( len(fdata) > 1000 )
        res = requests.post(
                "http://localhost:8139/launcher/background/1",
                auth = self.defAuth,
                #params = { 'launcher': 'main' },
                headers={'Content-Type': 'application/octet-stream'},
                data = fdata
                )
        self.check_status_code(res)
    def test_put_background(self):
            self.test_post_background()
    def test_get_background(self):
        res = requests.get(
                "http://localhost:8139/launcher/background/1",
                auth = self.defAuth
                )
        self.check_status_code(res)
        assert( len(res.content) > 1000 )

    def xtest_del_background(self):
        res = requests.delete(
                "http://localhost:8139/launcher/background/1",
                auth = self.defAuth
                )
        self.check_status_code(res)

    def test_post_logo(self):
        fdata = open('data/bg.png', 'rb').read()
        assert( len(fdata) > 1000 )
        res = requests.post(
                "http://localhost:8139/launcher/logo/1",
                auth = self.defAuth,
                params = { 'language': 'en' },
                headers={'Content-Type': 'application/octet-stream'},
                data = fdata
                )
        self.check_status_code(res)
    def test_put_logo(self):
        fdata = open('data/bg.png', 'rb').read()
        assert( len(fdata) > 1000 )
        res = requests.put(
                "http://localhost:8139/launcher/logo/1",
                auth = self.defAuth,
                params = { 'language': 'en' },
                headers={'Content-Type': 'application/octet-stream'},
                data = fdata
                )
        self.check_status_code(res)
    def test_get_logo(self):
        res = requests.get(
                "http://localhost:8139/launcher/logo/1",
                params = { 'language': 'en' },
                auth = self.defAuth
                )
        self.check_status_code(res)
        assert( len(res.content) > 1000 )

    def xtest_del_logo(self):
        res = requests.delete(
                "http://localhost:8139/launcher/logo/1",
                params = { 'language': 'en' },
                auth = self.defAuth
                )
        self.check_status_code(res)

    def test_get_components_types(self):
        res = requests.get(
                "http://localhost:8139/launcher/components/types",
                auth = self.defAuth,
                )
        
        self.check_status_code(res)

    def test_post_components_logo(self):
        fdata = open('data/bg.png', 'rb').read()
        assert( len(fdata) > 1000 )
        res = requests.post(
                "http://localhost:8139/launcher/components/logo/1",
                auth = self.defAuth,
                params = { 'launcher': '1' },
                headers={'Content-Type': 'application/octet-stream'},
                data = fdata
                )
        self.check_status_code(res)
    def test_put_components_logo(self):
        fdata = open('data/bg.png', 'rb').read()
        assert( len(fdata) > 1000 )
        res = requests.put(
                "http://localhost:8139/launcher/logo/1",
                auth = self.defAuth,
                params = { 'language': 'en' },
                headers={'Content-Type': 'application/octet-stream'},
                data = fdata
                )
        self.check_status_code(res)
    def test_get_components_logo(self):
        res = requests.get(
                "http://localhost:8139/launcher/components/logo/1",
                params = { 'launcher': '1' },
                auth = self.defAuth
                )
        self.check_status_code(res)
        assert( len(res.content) > 1000 )
    def test_get_components_info(self):
        res = requests.get(
                "http://localhost:8139/launcher/components/info/1",
                auth = self.defAuth,
                params = { 'from': 1, 'to':10 },
                )
        self.check_status_code(res)
    def xtest_put_components_info(self):
        res = requests.put(
                "http://localhost:8139/launcher/components/info/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "active": True,
                "type": 1,
                "name":{
                    "en": "string",
                    "fa": "string",
                    "ar": "string"
                    }, 
                "logo": 1,
                "contentType": 1,
                "contentCategories":[1, 2, 3, 4]
               }
                )
        self.check_status_code(res)
    def test_post_components_info(self):
        res = requests.post(
                "http://localhost:8139/launcher/components/info",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "active": True,
                "type": 1,
                "name":{
                    "en": "string",
                    "fa": "string",
                    "ar": "string"
                    }, 
                "logo": 1,
                "contentType": 1,
                "contentCategories":[1, 2, 3, 4]
               }
             )
        self.check_status_code(res)

    def test_get_launcher_menu(self):
        res = requests.get(
                "http://localhost:8139/launcher/menu",
                auth = self.defAuth,
                params = { 'from': 1, 'to':10 },
                )
        self.check_status_code(res)
        res = requests.get(
                "http://localhost:8139/launcher/menu/1",
                auth = self.defAuth,
                )
        self.check_status_code(res)
    def xtest_put_launcher_menu(self):
        res = requests.put(
                "http://localhost:8139/launcher/menu/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "active": True,
                "name":{
                    "en": "string",
                    "fa": "string",
                    "ar": "string"
                    }, 
                "icon": 1,
                "permission": 1,
                "components": [1,2,3 ]
               }
                )
        self.check_status_code(res)
    def test_post_launcher_menu(self):
        res = requests.post(
                "http://localhost:8139/launcher/menu/1",
                auth = self.defAuth,
                json =  {
                "_id": 1,
                "active": True,
                "type": 3,
                "name":{
                    "en": "string",
                    "fa": "string",
                    "ar": "string"
                    }, 
                "logo": 1,
                "contentType": 1,
                "contentCategories":[1, 2, 3, 4]
               }
             )
        self.check_status_code(res)

"""
if __name__ == "__main__":
    unittest.main()
     
