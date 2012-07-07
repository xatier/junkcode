#!/usr/bin/python

# this is a program from <<Expert C programming>>, ch 3.8
# a c token parser

class tocken:
    """
    a C token
    """
    def __init__ (t, s):
        _type = t
        _string = s
    def dump():
        print _type, _string

global stack        # stack to record tokens
global this         # this token


def classfy_string():
    pass
    #return this._type

def gettocken():
    p = buffer[buf_ptr]
    while p == ' '
        buf_ptr += 1
        p = buffer[buf_ptr]
    if 'a' <= p and p <= 'z':


    pass
    #if this.

def read_to_first_identifier():
    print "identifier is ", this._string
    pass

def deal_with_function_args():
    # read to ')'
    pass

def deal_with_arrays():
    # read [size]
    pass

def deal_with_any_pointers():
    # read a '*'
    print "a pointer points to "
    #pop()

def deal_with_declarator():
    if this._type == '[':
        deal_with_arrays()
    if this._type == '(':
        deal_with_function_args()
    deal_with_any_pointers()
    while len(stack) != 0:
        if '(':
            #pop, gettocken, get '('
            pass
            deal_with_declarator
        else:
            #pop
            #print
            pass



if __name__ == '__main__':
    buf_ptr = 0;
    global buffer = raw_input()
    read_to_first_identifier()
    deal_with_declarator()



