#! /usr/bin/env python
import unittest, my_math

class ProductTestCase(unittest.TestCase):
    def testIntegers(self):
        for x in xrange(-10, 10):
            for y in xrange(-10, 10):
                p = my_math.product(x, y)
                self.failUnless(p == x * y, 'Integer multiplication failed')

def 


