#!/lab/epg_st_utils/lao/rhes6.x86_64/bin/python

def square(x):
    '''
    >>> square(2)
    4
    >>> square(3)
    9
    '''
    return x * x


if __name__ == '__main__':
    import doctest, my_math
    doctest.testmod(my_math)



