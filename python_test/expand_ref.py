#!/usr/bin/env python3

import os
import re
import json

global schemas

def changeStr(str):
    str = "hello world"
    return str

def getRefValue(ref):
    '''$ref'''
    print("getRefValue:", ref)
    if "#/components" in ref:
        refKey = ref.rsplit('/', 1)[1]
        return schemas[refKey]

    return ""

def replaceRefList(refList):
    l = []
    for item in refList:
        if '#/components/schemas/' in item:
            print("    expandRef-try to getRefValue:", item)
            l.append(getRefValue(item))
        else:
            l.append(item)

    print("my new list:",l)
    return l


def expandRef(data):

    for (k, v) in data.items():
        print("expandRef:", k, v)
        if k == 'anyOf' or k == 'oneOf' or k == 'allOf':
            data[k] = replaceRefList(v)

        elif isinstance(v, dict):
            expandRef(v)

        elif '#/components/schemas/' in v:
            data[k] = getRefValue(v)

        else:
            pass

    return data

copy = {}
def removeRef(data):
    for (k, v) in data.items():
        if k == '$ref':
            data[k] = getRefValue(v)

        elif k == 'anyOf':
            print('hit anyOf')
            for obj in v:
                expandRef(obj)

        elif k == 'oneOf':
            for obj in v:
                expandRef(obj)

        elif k == 'allOf':
            for obj in v:
                expandRef(obj)

        elif isinstance(v, dict):
            expandRef(v)
        else:
            pass




schemas = {'Tai' : {'v1':'3'}, 'NullValue': 2}

#schemas = {'N3IwfId':{'pattern': '^[A-Fa-f0-9]+$', 'type': 'string'}, 'DurationSecRm': {'nullable': True, 'type': 'integer'}, 'DateRm': {'format': 'date', 'nullable': True, 'type': 'string'}, 'SmContextStatusNotification':{'properties': {'apnRateStatus': {'$ref': 'TS29571_CommonData.yaml#/components/schemas/ApnRateStatus'}, 'oldSmContextRef': {'$ref': 'TS29571_CommonData.yaml#/components/schemas/Uri'}, 'newSmfSetId': {'$ref': 'TS29571_CommonData.yaml#/components/schemas/NfSetId'}, 'oldSmfId': {'$ref': 'TS29571_CommonData.yaml#/components/schemas/NfInstanceId'}, 'smallDataRateStatus': {'$ref': 'TS29571_CommonData.yaml#/components/schemas/SmallDataRateStatus'}, 'newSmfId': {'$ref': 'TS29571_CommonData.yaml#/components/schemas/NfInstanceId'}, 'ddnFailureStatus': {'default': False, 'type': 'boolean'}, 'statusInfo': {'$ref': '#/components/schemas/StatusInfo'}, 'notifyCorrelationIdsForddnFailure': {'minItems': 1, 'type': 'array', 'items': {'type': 'string'}}}, 'required': ['statusInfo'], 'type': 'object'}}

data1 = {'CoreNetworkTypeRm':{'allOf': [{'$ref': '#/components/schemas/CoreNetworkType'}, {'$ref': '#/components/schemas/NullValue'}]}, 'Tai':{'nihao': {'ref': '#/components/schemas/CoreNetworkType'}}}
schemas = {'CoreNetworkType':{'anyOf': [{'enum': ['5GC', 'EPC'], 'type': 'string'}, {'type': 'string'}]}, 'NullValue':2}

def replace_item(obj, key, replace_value):
    for k, v in obj.items():
        if isinstance(v, dict):
            obj[k] = replace_item(v, key, replace_value)
    if key in obj:
        obj[key] = replace_value
    return obj

goal = []
def find_item(obj, key):
    if key in obj: return obj[key]
    for k, v in obj.items():
        if isinstance(v,dict) and 'anyOf' != k:
            item = find_item(v, key)
            if item is not None:
                return item
        elif 'anyOf' == k:
            for subObj in v:
                item = find_item(subObj, key)
                goal.append(item)
                continue
            return goal


def replaceRefDict(matched):
    print("==Matched:", matched.group(1))
    return matched.group(1)


print("before json dumps: ",(data1))
strData = json.dumps(data1)
print("after json dumps: ",(strData))
expandedData = re.sub(r'{\"\$ref\": (.*?)}', replaceRefDict, strData)
print("after json replaced: ",(expandedData))
data1 = json.loads(expandedData)
print("what I want :", data1, type(data1))
data1 = expandRef(data1)
print("Aha:", data1)

#str = '#/components/schemas/Tai'
#print("===%s===" % str.rsplit('/',1)[1])

#print("find $ref from ", find_item(data, "$ref"))
#print("find $ref from ", find_item(data1, "$ref"))
#data = replace_item(data, "$ref", "hello")
#print("data=", data)
