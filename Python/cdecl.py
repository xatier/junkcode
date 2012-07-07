#!/usr/bin/python

# this is a program from <<Expert C programming>>, ch 3.8
# a c token parser

class token:
    """
    a C token
    """
    def __init__ (self, t, s):
        _type = t
        _string = s
    def dump():
        print _type, _string


def classfy_string(s):
    if s == "const":
        return "qualifier"
    if s == "volatile":
        return "qualifier"
    if s == "void" or s == "char" or s == "signed" or s == "unsigned" or \
        s == "short" or s == "int" or s == "long" or s == "float" or \
        s == "double" or s == "struct" or s == "union" or s == "enum":
        return "type"
    return "identifier"


def gettocken():
    global buf_ptr
    while buf[buf_ptr] == ' ':
        buf_ptr = buf_ptr + 1

    p = buf[buf_ptr]
    if 'a' <= p and p <= 'z':
        while 1:
            p += buf[buf_ptr]
            if not ('a' <= p[-1:] and p[-1:] <= 'z'):
                p = p[:-1]
                break
        this = token(classfy_string(p), p)
        return

    if p == '*':
        this = token("*", "pointer to")
        return

    this = token(p[:1], p[:1])


def read_to_first_identifier():
    gettocken()
    print this._type, this._string
    while this._type != "identifier":
        stack.push(this)
        gettocken()

    print "identifier is ", this._string
    gettocken()

def deal_with_function_args():
    while this._type != ')':
        gettocken()

    gettocken()
    print "function returning",

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
    
    stack = []
    this = token("", "")
    buf = raw_input()
    buf_ptr = 0
    read_to_first_identifier()
    deal_with_declarator()



