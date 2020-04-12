#!/usr/bin/python
from pymongo import MongoClient

class Mongo(object):
    def __init__(self):
        self.client = MongoClient('localhost', 27017)
        #if 'iptv' not in self.client.list_database_names():
        #    raise Exception("DB of iptv not exists!")
        self.db = self.client['iptv']

    def info(self):
        return self.db.list_collection_names()
    
    def insert(self, collection, doc):
        self.db[collection].insert(doc)

    def find(self, collection, query):
        cursor = self.db[collection].find(query)
        if cursor.count() < 1: return "EMPTY"
        c_list = []
        for c in cursor: c_list.append(c)
        return c_list

    def find_one(self, collection, query):
        return self.db[collection].find_one(query)

    def find_id(self, collection, _id):
        return self.db[collection].find_one({'_id':_id})

if __name__ == "__main__":
    cols = {}
    cols['status_information'] = { 
            "_id": 1,
            "Running": True,
            "Owner": "string",
            "LicenseExpire": "string",
            "Serial": "string",
            "Version": "string",
            "Uptime": "string",
            "LastReset": "string",
            "SystemIP": "string",
            "SystemDate": "string",
            "SystemInternet": True,
            "Manufacturer": "string",
            "Model": "string",
            "CPU": "string",
            "Memory": "string"
            }
    cols['status_cpu_mem'] = { 
            "_id": 1,
            "time": 1570000,
            "cpuLoad":1,
            "cpuCoreNum": 1,
            "cpuPercent":1,
            "memTotal": 1,
            "memFree": 1,
            }
    cols['status_network'] = { 
            "_id": 1,
            "time": 1570000,
            "1erfaces":[
                {
                    "name": "string",
                    "ip": "string",
                    "mask": "string",
                    "sendAve": 1,
                    "receiveAve": 1
                    },
                ],
            "dns": "string",
            "gateway": "string"
            }
    cols['status_storage'] = { 
            "_id": 1,
            "time": 1570000,
            "mounts":[
                {
                    "name": "string",
                    "partition": "string",
                    "total": 1,
                    "free": 1,
                    "readAve": 1,
                    "writeAve": 1
                    },
                ]
            }
    cols['status_dvb'] = { 
            "_id": 1,
            "time": 1570000,
            "inputDVBs":[
                {
                    "_id": 1,
                    "type": "string",
                    "parameters": "string",
                    "channelNumber": 1,
                    "signal": 1,
                    "snr": 1
                    },
                ],
            "outputDVBs":[
                {
                    "_id": 1,
                    "frequency": 1,
                    "capacity": 1
                    },
                ]
            }
    cols['status_channels_input'] = { 
            "_id": 1,
            "type": "string",     #DVB, NET, HDD 
            "name": "string",
            "health": True,
            }
    cols['status_channels_output'] = { 
            "_id": 1,
            "status": True,
            "type": "string",
            "name": "string",
            "rf": True,
            "rfFreq": 1,
            "rfSid": 1,
            "permission": 1,
            "record": True,
            "udp": True,
            "http": True,
            "rtsp": True,
            "hls": True
            }
    cols['status_channels_output_view'] = { 
            "_id": 1,
            "name": "string",
            }
    cols['status_users'] = { 
            "_id": 1,
            "name": "string",
            "active": True,
            "online": True,
            "lastActivity": "string",
            "lastLogin": 1570000
            }
    cols['status_errors'] = { 
            "_id": 1,
            "time": 1570000,
            "error": "string",
            "priority": 1
            }
    cols['report_user'] = { 
            "_id": 1,
            "time": 1570000,
            "user": "string",
            "activity": "string"  
            }
    cols['report_system'] = { 
            "_id": 1,
            "time": 1570000,
            "activity": "string"
            }
    cols['report_live'] = { 
            "_id": 1,
            "time": 1570000,
            "activity": "string"
            }
    cols['report_vod'] = { 
            "_id": 1,
            "time": 1570000,
            "activity": "string"
            }
    cols['report_component'] = { 
            "_id": 1,
            "time": 1570000,
            "activity": "string"
            }
    cols['report_system_user'] = { 
            "_id": 1,
            "time": 1570000,
            "activity": "string"
            }
    cols['system_location'] = { 
            "_id": 1,
            "name": "string",
            "weatherLocation": "string",
            "pryerTime": "string",
            "timeZone": "string",
            "systemTime": 1570000,
            "gamaryShift": 1,
            "subtitleLogo":{
                "isLeft": True,
                "components":[1, 2]
                }
            }
    cols['system_network'] = { 
            "_id": 1,
            "1erfaces":[
                {
                    "_id": 1,
                    "name": "string",
                    "description": "string",
                    "ip": "string",  
                    "mask": "string",
                    },
                ],
            "dns": "string",
            "gateway": "string",
            "mainInterface": 1,
            "multicastBase": "string",
            "multicastInterface": 1,
            "addressForNAT": "string",
            "staticRoute": ["string", 2 ],
            "firewallRule": ["string", 2 ]
            }
    cols['system_users'] = { 
            "_id": 1,
            "name": "string",
            "locationName": "string",
            "creatorId": 1, 
            "active": True,
            "start": 1570000,
            "end": 1570000,
            "expire": "string",
            "permission": { 
                "/system/users":["GET","PUT","POST","DELETE"],
                "/system/pms":["GET","PUT","POST","DELETE"],
                },   
            "user": "string",
            "pass": "string",
            }
    cols['system_pms'] = { 
            "_id": 1,
            "active": True,
            "name": "string",
            "address": "string",
            "user": "string",
            "pass": "string",   
            }
    cols['system_vod_account'] = { 
            "_id": 1,
            "partner": "string",
            "user": "string",
            "pass": "string",
            }
    cols['system_permission'] = { 
            "_id": 1,
            "active": True,
            "name": "string" 
            }
    cols['system_weektime'] = { 
            "_id": 1,
            "active": True,
            "name": "string",
            "hours": {
                "0": [1, 1],
                "1": [1, 1],
                "2": [1, 1],
                "3": [1, 1],
                "4": [1, 1],
                "5": [1, 1],
                "6": [1, 1]
                }
            }
    cols['system_license'] = { 
            "_id"
            "license":{    
                }
            }
    cols['storage_setting'] = { 
            "_id": 1,
            "root": "string",
            "partitions":{
                "vod": 1,
                "aod": 1,
                "timeshift": 1,
                "npvr": 1,
                "audiobook": 1,
                "book": 1,
                "photo": 1,
                },
            "timeShift":{
                "recordDuration": 1,
                "EPGnaming": True,
                },
            "NPVR":{
                "perUser": 1
                }
            }
    cols['storage_contents_types'] = { 
            "_id":1,
            "name":"string",
            }
    cols['storage_contents_platforms'] = { 
            "_id":1,
            "name":"string",
            }
    cols['storage_contents_categories'] = { 
            "_id":1,
            "name":"string",
            }
    cols['storage_contents_info'] = { 
            "_id": 1,
            "type": 1,
            "category":[1, 2],
            "group": "string",
            "permission": 1,
            "price": 1,
            "platform":[1, 2],
            "date": 1570000,
            "languages" : ["EN" ], 
            "description":{
                "en": {
                    "name": "string",
                    "description": "string"
                    },
                "fa": {
                    "name": "string",
                    "description": "string"
                    },
                "ar": {
                    "name": "string",
                    "description": "string"
                    }
                }
            }
    cols['storage_advertize'] = { 
            "_id": 1,
            "content": 1,
            "name": "string",
            "weektime": [1, 2],
            "expire": 1570000,
            "priority": 1,
            }
    cols['live_tuners_hardware_input'] = { 
            "_id": 1,
            "name": "string", 
            "is_dvbt": True, 
            }
    cols['live_tuners_hardware_output'] = { 
            "_id": 1,
            "name": "string", 
            "is_dvbt": True, 
            }
    cols['live_tuners_input'] = { 
            "_id": 1,
            "name": "string", 
            "active": True,
            "is_dvbt": True, 
            "freq": 1, 
            "errrate": "string", 
            "pol": "string", 
            "symrate": 1,
            "switch": 1, 
            }
    cols['live_tuners_input_scan'] = { 
            "_id": 1,
            "name": "string", 
            "dvb_id": 1, 
            "is_dvbt": True, 
            "sid": 1, 
            "aid": 1, 
            "vid": 1,
            "freq": 1, 
            "pol": 1, 
            "scramble": True, 
            "symb": 1
            }
    cols['live_tuners_output'] = { 
            "_id": 1,
            "dvbs": [1, 1, ], 
            "dvbt": [1, 1, ], 
            "mode_s": "string", 
            "mode_t": "string", 
            "pcr": 1
            }
    cols['live_inputs_dvb'] = { 
            "_id": 1,
            "active": True,
            "name": "string", 
            "dvb_id": 1, 
            "is_dvbt": True, 
            "sid": 1, 
            "aid": 1, 
            "vid": 1,
            "freq": 1, 
            "pol": 1, 
            "scramble": True, 
            "symb": 1
            }
    cols['live_inputs_archive'] = { 
            "_id": 1,
            "dir": [ "string"],
            "is_tv": True, 
            "name": "string",
            "active": True
            }
    cols['live_inputs_network'] = { 
            "_id": 1,
            "name": "string",
            "url": "string", 
            "active": True,
            "static": True
            }
    cols['live_inputs_iptv'] = { 
            "_id": 1,
            "name": "string",
            "iptv": "string",
            "url": "string", 
            "active": True
            }
    cols['live_inputs_virtual_net'] = { 
            "_id": 1,
            "active": True,
            "name": "string", 
            "url": "string", 
            "record": True,
            "permission": 1
            }
    cols['live_inputs_virtual_dvb'] = { 
            "_id": 1,
            "active": True,
            "name": "string", 
            "freq": 1, 
            "sid": 1, 
            "record": True,
            "permission": 1
            }

    cols['live_transcode'] = { 
            "_id": 1,
            "active": True,
            "input": "string", 
            "output": "string", 
            "preset": "string",
            "videoCodec": "string", 
            "videoSize": "string", 
            "videoRate": "string", 
            "videoFps": "string", 
            "videoProfile": "string", 
            "audioCodec": "string", 
            "audioRate": "string" 
            }
    cols['live_cccam'] = { 
            "_id": 1,
            "active": True,
            "name": "string", 
            "protocol": "string",
            "server": "string", 
            "user": "string", 
            "pass": "string" 
            }
    cols['live_unscramble'] = { 
            "_id": 1,
            "active": True,
            "channel": "string", 
            "use_bsskey": True,
            "use_cccam": True
            }
    cols['live_scramble'] = { 
            "_id": 1,
            "active": True,
            "channel": "string", 
            "crypto": "string",
            "key": "string" 
            }
    cols['live_output_silver'] = { 
            "_id": 1,
            "active": True,
            "name": "string", 
            "permission": 1,
            "freq": 1, 
            "sid": 1, 
            "record": True,
            "udp": True,
            "http": True,
            "rtsp": True,
            "hls": True
            }
    cols['live_output_gold'] = { 
            "_id": 1,
            "active": True,
            "userId": 1, 
            "iptvAccount": "string",
            "tunerId": 1,
            "satellites":[ 
                {
                    "name": "string",
                    "switch": 1,
                    "LNC":["LH", "LV", "HH", "HV"]
                    }
                ] 
            }
    cols['live_logo'] = { 
            "_id":1,
            "channelName":"string"
            }
    cols['launcher_components_types'] = {
            "_id": 1,
            "name": "string",
            }
    cols['launcher_components_info'] = { 
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
            "contentCategories":[1, 2]
            }
    cols['launcher_default'] = { 
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
            "testUserId": 1,
            "defaultChannel": 1 

            }
    cols['launcher_menu'] = { 
            "_id": 1,
            "active": True,
            "name":{
                "en": "string",
                "fa": "string",
                "ar": "string"
                }, 
            "icon": 1,
            "permission": 1,
            "components": [1, 2 ]
            }
    cols['users_group'] = { 
            "_id": 1,
            "active": True,
            "name": "string", 
            "permission": [1, 2 ],
            "weektime": [1, 2 ] 
            }
    cols['users_user'] = { 
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
            "expire": 1570000,
            }
    cols['users_message_broadcast'] = { 
            "_id": 1,
            "group": [ 1, 2 ],
            "time": 1570000,
            "weektime": [1, 2 ],
            "expire": 1570000,
            "subject": "string", 
            "body": "string",

            }
    cols['users_message_from'] = { 
            "_id": 1,
            "time": 1570000,
            "subject": "string", 
            "body": "string",
            }
    cols['users_message_to'] = {
            "_id": 1,
            "time": 1570000,
            "subject": "string", 
            "body": "string",
            }

    m = Mongo()
    for key, val in cols.iteritems():
        print "insert ",key
        m.insert(key, val)

