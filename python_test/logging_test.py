#!/usr/bin/env python3

import logging


#FORMAT = '%(asctime)-15s %(clientip)s %(user)-8s %(message)s'
FORMAT = '%(asctime)-15s %(clientip)s %(user)-8s %(message)s'
logging.basicConfig(format=FORMAT)
d = {'clientip': '192.168.0.1', 'user': 'fbloggs'}

#logger = logging.getLogger('tcpserver')
#logger.warning('Protocol problem: %s', 'connection reset', extra=d)


logger = logging.getLogger('son')
logger.setLevel(__debug__)

logger.debug("hello")
