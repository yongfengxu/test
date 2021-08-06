#!/usr/bin/env python3

def fun():
    name = ""
    attr = ""
    #global attr, attr_1
    (v1, v2) = addInfo(name, attr)

    name += v1
    attr += v2

    print("who?",name, attr)

def addInfo(name, attr):
    name = name + "oy"
    attr += "hello"

    return (name, attr)


#fun()


data = {'oneOf': [{'anyOf': [{'type': 'string', 'enum': ['MORE_LIKELY']}, {'type': 'string'}]}, {'$ref': '#/components/schemas/NullValue'}, 'Charlie']}


if 'anyOf' in data:
    print("anyOf in data")

if '$ref' in data:
    print("$ref in data", item)

if isinstance(data['oneOf'], list):
    for item in data['oneOf']:
        #print("item=", item)
        if 'anyOf' in item:
            print("anyOf in data:", item)
        elif 'Charlie' in item:
            print("Charlie in data:", item)
        elif '$ref' in item:
            print("$ref in data", item)
            if 'NullValue' in item['$ref']:
                print("seems NullValue")

        if 'enum' in item:
            print("enum in data:", item)

allOfData = {'allOf': [{'pattern': '^((:|(0?|([1-9a-f][0-9a-f]{0,3}))):)((0?|([1-9a-f][0-9a-f]{0,3})):){0,6}(:|(0?|([1-9a-f][0-9a-f]{0,3})))$'}, {'pattern': '^((([^:]+:){7}([^:]+))|((([^:]+:)*[^:]+)?::(([^:]+:)*[^:]+)?))$'}], 'example': '2001:db8:85a3::8a2e:370:7334', 'type': 'string'}

if 'allOf' in allOfData:
    print ("allOf in allOfData")

if 'type' in allOfData:
    print("type in allOfData")

rsp = 'TS29571_CommonData.yaml#/components/#esponses/411'
rsp1 = '#/components/#esponses/411'
print(type( rsp1.split('#')))
key = rsp1.split('#', 1)[0]
if len(key) == 0:
    print("nothing in key")

if key == "":
    print("nothing in key,too")
