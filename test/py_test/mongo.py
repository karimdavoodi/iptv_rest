#!/usr/bin/python
from pymongo import MongoClient

class Mongo(object):
    def __init__(self):
        self.client = MongoClient('localhost', 27017)
        if 'iptv' not in self.client.list_database_names():
            raise Exception("DB of iptv not exists!")
        self.db = self.client['iptv']

    def info(self):
        return self.db.list_collection_names()
    
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
            "Running": boolean,
            "Owner": string,
            "LicenseExpire": string,
            "Serial": string,
            "Version": string,
            "Uptime": string,
            "LastReset": string,
            "SystemIP": string,
            "SystemDate": string,
            "SystemInternet": boolean,
            "Manufacturer": string,
            "Model": string,
            "CPU": string,
            "Memory": string
            }
    cols['status_cpu_mem'] = { 
            "_id": int,
            "time": epochtime,
            "cpuLoad":float,
            "cpuCoreNum": int,
            "cpuPercent":float,
            "memTotal": int,
            "memFree": int,
            }
    cols['status_network'] = { 
            "_id": int,
            "time": epochtime,
            "interfaces":[
                {
                    "name": string,
                    "ip": string,
                    "mask": string,
                    "sendAve": int,
                    "receiveAve": int
                    },
                ],
            "dns": string,
            "gateway": string
            }
    cols['status_storage'] = { 
            "_id": int,
            "time": epochtime,
            "mounts":[
                {
                    "name": string,
                    "partition": string,
                    "total": int,
                    "free": int,
                    "readAve": int,
                    "writeAve": int
                    },
                ]
            }
    cols['status_dvb'] = { 
            "_id": int,
            "time": epochtime,
            "inputDVBs":[
                {
                    "_id": int,
                    "type": string
                    "parameters": string,
                    "channelNumber": int,
                    "signal": int,
                    "snr": int
                    },
                ],
            "outputDVBs":[
                {
                    "_id": int,
                    "frequency": int,
                    "capacity": int
                    },
                ]
            }
    cols['status_channels_input'] = { 
            "_id": int,
            "type": string,     #DVB, NET, HDD 
            "name": string,
            "health": boolean,
            }
    cols['status_channels_output'] = { 
            "_id": int,
            "status": boolean,
            "type": string
            "name": string,
            "rf": boolean,
            "rfFreq": int,
            "rfSid": int,
            "permission": int,
            "record": boolean,
            "udp": boolean,
            "http": boolean,
            "rtsp": boolean,
            "hls": boolean
            }
    cols['status_channels_output_view'] = { 
            "_id": int,
            "name": string,
            }
    cols['status_users'] = { 
            "_id": int,
            "name": string,
            "active": boolean,
            "online": boolean,
            "lastActivity": string,
            "lastLogin": epochtime
            }
    cols['status_errors'] = { 
            "_id": int,
            "time": epochtime,
            "error": string,
            "priority": int
            }
    cols['report_user'] = { 
            "_id": int,
            "time": epochtime,
            "user": string,
            "activity": string  
            }
    cols['report_system'] = { 
            "_id": int,
            "time": epochtime,
            "activity": string
            }
    cols['report_live'] = { 
            "_id": int,
            "time": epochtime,
            "activity": string
            }
    cols['report_vod'] = { 
            "_id": int,
            "time": epochtime,
            "activity": string
            }
    cols['report_component'] = { 
            "_id": int,
            "time": epochtime,
            "activity": string
            }
    cols['report_system_user'] = { 
            "_id": int,
            "time": epochtime,
            "activity": string
            }
    cols['system_location'] = { 
            "_id": 1,
            "name": string,
            "weatherLocation": string,
            "pryerTime": string,
            "timeZone": string,
            "systemTime": epochtime,
            "gamaryShift": int
            "subtitleLogo":{
                "isLeft": boolean,
                "components":[int, ...]
                }
            }
    cols['system_network'] = { 
            "_id": 1,
            "interfaces":[
                {
                    "_id": int,
                    "name": string,
                    "description": string,
                    "ip": string,  
                    "mask": string,
                    },
                ],
            "dns": string,
            "gateway": string,
            "mainInterface": int,
            "multicastBase": string,
            "multicastInterface": int,
            "addressForNAT": string,
            "staticRoute": [string, ... ],
            "firewallRule": [string, ... ]
            }
    cols['system_users'] = { 
            "_id": int,
            "name": string,
            "locationName": string,
            "creatorId": int, 
            "active": boolean,
            "start": epochtime,
            "end": epochtime,
            "expire": string,
            "permission": [ 
                "/system/users":[GET,PUT,POST,DELET],
                "/system/pms":[GET,PUT,POST,DELET],
                ...

                ],   
            "user": string,
            "pass": string,
            }
    cols['system_pms'] = { 
            "_id": 1,
            "active": boolean,
            "name": string,
            "address": string,
            "user": string,
            "pass": string,   
            }
    cols['system_vod_account'] = { 
            "_id": int,
            "partner": string,
            "user": string,
            "pass": string,
            }
    cols['system_permission'] = { 
            "_id": int,
            "active": boolean,
            "name": string 
            }
    cols['system_weektime'] = { 
            "_id": int,
            "active": boolean,
            "name": string,
            "hours": [
                "0": [int, int, ..],
                "1": [int, int, ..],
                "2": [int, int, ..],
                "3": [int, int, ..],
                "4": [int, int, ..],
                "5": [int, int, ..],
                "6": [int, int, ..]
                ]
            }
    cols['system_license'] = { 
            "_id"
            "license":{    
                }
            }
    cols['storage_setting'] = { 
            "_id": 1,
            "root": string,
            "partitions":{
                "vod": int,
                "aod": int,
                "timeshift": int,
                "npvr": int,
                "audiobook": int,
                "book": int,
                "photo": int,
                },
            "timeShift":{
                "recordDuration": int,
                "EPGnaming": boolean,
                },
            "NPVR":{
                "perUser": int
                }
            }
    cols['storage_contents_types'] = { 
            "_id":int,
            "name":string,
            }
    cols['storage_contents_platforms'] = { 
            "_id":int,
            "name":string,
            }
    cols['storage_contents_categories'] = { 
            "_id":int,
            "name":string,
            }
    cols['storage_contents_info'] = { 
            "_id": int,
            "type": int,
            "category":[int, ...],
            "group": string,
            "permission": int,
            "price": int,
            "platform":[int, ...],
            "date": epochtime,
            "languages" : [2-char, ... ], 
            "description":[
                "en": {
                    "name": string,
                    "description": string
                    },
                "fa": {
                    "name": string,
                    "description": string
                    },
                "ar": {
                    "name": string,
                    "description": string
                    }
                ]
            }
    cols['storage_advertize'] = { 
            "_id": int,
            "content": int,
            "name": string,
            "weektime": [int, ...],
            "expire": epochtime,
            "priority": int,
            }
    cols['live_tuners_hardware_input'] = { 
            "_id": int,
            "name": string, 
            "is_dvbt": boolean, 
            }
    cols['live_tuners_hardware_output'] = { 
            "_id": int,
            "name": string, 
            "is_dvbt": boolean, 
            }
    cols['live_tuners_input'] = { 
            "_id": int,
            "name": string, 
            "active": boolean,
            "is_dvbt": boolean, 
            "freq": int, 
            "errrate": string, 
            "pol": string, 
            "symrate": int,
            "switch": int, 
            }
    cols['live_tuners_input_scan'] = { 
            "_id": int,
            "name": string, 
            "dvb_id": int, 
            "is_dvbt": boolean, 
            "sid": int, 
            "aid": int, 
            "vid": int,
            "freq": int, 
            "pol": int, 
            "scramble": boolean, 
            "symb": int
            }
    cols['live_tuners_output'] = { 
            "_id": 1,
            "dvbs": [int, int, ], 
            "dvbt": [int, int, ], 
            "mode_s": string, 
            "mode_t": string, 
            "pcr": int
            }
    cols['live_inputs_dvb'] = { 
            "_id": int,
            "active": boolean,
            "name": string, 
            "dvb_id": int, 
            "is_dvbt": boolean, 
            "sid": int, 
            "aid": int, 
            "vid": int,
            "freq": int, 
            "pol": int, 
            "scramble": boolean, 
            "symb": int
            }
    cols['live_inputs_archive'] = { 
            "_id": int,
            "dir": [ string, .. ]
            "is_tv": boolean, 
            "name": string,
            "active": boolean
            }
    cols['live_inputs_network'] = { 
            "_id": int,
            "name": string,
            "url": string, 
            "active": boolean,
            "static": boolean
            }
    cols['live_inputs_iptv'] = { 
            "_id": int,
            "name": string,
            "iptv": string,
            "url": string, 
            "active": boolean
            }
    cols['live_inputs_virtual_net'] = { 
            "_id": int,
            "active": boolean,
            "name": string, 
            "url": string, 
            "record": boolean,
            "permission": int
            }
    cols['live_inputs_virtual_dvb'] = { 
            "_id": int,
            "active": boolean,
            "name": string, 
            "freq": int, 
            "sid": int, 
            "record": boolean,
            "permission": int
            }

    cols['live_transcode'] = { 
            "_id": int,
            "active": boolean,
            "input": string, 
            "output": string, 
            "preset": string,
            "videoCodec": string, 
            "videoSize": string, 
            "videoRate": string, 
            "videoFps": string, 
            "videoProfile": string, 
            "audioCodec": string, 
            "audioRate": string 
            }
    cols['live_cccam'] = { 
            "_id": int,
            "active": boolean,
            "name": string, 
            "protocol": string,
            "server": string, 
            "user": string, 
            "pass": string 
            }
    cols['live_unscramble'] = { 
            "_id": int,
            "active": boolean,
            "channel": string, 
            "use_bsskey": boolean,
            "use_cccam": boolean
            }
    cols['live_scramble'] = { 
            "_id": int,
            "active": boolean,
            "channel": string, 
            "crypto": string,
            "key": string 
            }
    cols['live_output_silver'] = { 
            "_id": int,
            "active": boolean,
            "name": string, 
            "permission": int,
            "freq": int, 
            "sid": int, 
            "record": boolean,
            "udp": boolean,
            "http": boolean,
            "rtsp": boolean,
            "hls": boolean
            }
    cols['live_output_gold'] = { 
            "_id": int,
            "active": boolean,
            "userId": int, 
            "iptvAccount": string,
            "tunerId": int,
            "satellites":[ 
                {
                    "name": string,
                    "switch": int,
                    "LNC":["LH", "LV", "HH", "HV"]
                    }
                ] 
            }
    cols['live_logo'] = { 
            "_id":int,
            "channelName":string
            }
    cols['launcher_components_types'] = {
            "_id": int,
            "name": string,
            }
    cols['launcher_components_info'] = { 
            "_id": int,
            "active": boolean,
            "type": int,
            "name":{
                "en": string,
                "fa": string,
                "ar": string
                }, 
            "logo": int,
            "contentType": int,
            "contentCategories":[int, ...]
            }
    cols['launcher_default'] = { 
            "_id": int,
            "launcher": string,
            "font":{
                "en": string,
                "fa": string,
                "ar": string
                },
            "welcome":{
                "en": string,
                "fa": string,
                "ar": string
                },
            "user":{
                "en": string,
                "fa": string,
                "ar": string
                },
            "language": string,
            "welcomeClip": boolean,
            "uiStartup": string,
            "unitName": string,
            "clientHotspot": string,
            "testUserId": int,
            "defaultChannel": int 

            }
    cols['launcher_menu'] = { 
            "_id": int,
            "active": boolean,
            "name":{
                "en": string,
                "fa": string,
                "ar": string
                }, 
            "icon": int,
            "permission": int,
            "components": [int, ... ]
            }
    cols['users_group'] = { 
            "_id": int,
            "active": boolean,
            "name": string, 
            "permission": [int, ... ],
            "weektime": [int, ... ] 
            }
    cols['users_user'] = { 
            "_id": int,
            "active": boolean,
            "name": string, 
            "group": [int, ... ],
            "connections": int, 
            "ipaddress": string, 
            "language": string, 
            "launcher": int, 
            "user": string, 
            "pass": string, 
            "vod_id": int,
            "npvr": int,
            "expire": epochtime,
            }
    cols['users_message_broadcast'] = { 
            "_id": int,
            "group": [ int, ... ],
            "time": epochtime,
            "weektime": [int, ... ],
            "expire": epochtime,
            "subject": string, 
            "body": string,

            }
    cols['users_message_from'] = { 
            "_id": int,
            "time": epochtime,
            "subject": string, 
            "body": string,
            }
    cols['users_message_to'] = {
            "_id": int,
            "time": epochtime,
            "subject": string, 
            "body": string,
            }

    m = Mongo()

    m.insert('system_pms', {})
    print m.info()
    print m.find('system_pms', {})
    print m.find_one('system_pms', {})
    print m.find_id('system_pms', 1)
"""

"""
