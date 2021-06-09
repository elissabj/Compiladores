from ply import *
import sys

"""
[start creating the tokens given the regular expression.]

Arguments:
    t {str} -- [code of .txt]
"""
first = []
symbolTable = {}
literals = [',','.']
reserved = {'signal':'TK_SGN', 'float':'TK_FLT', 'interpolate':'TK_OPEI', 'decimate':'TK_OPED', 'shift':'TK_OPES', 'reflect':'TK_OPER', 'amplitude':'TK_OPEA'}
tokens = list(reserved.values()) + ['TK_NAMEF','TK_NAME', 'TK_LNBK', 'TK_DATAS', 'TK_DATAI', 'TK_ASIG', 'TK_LCOR', 'TK_RCOR', 'TK_LPAR', 'TK_RPAR']

def t_TK_SGNA(t):
    r'signal'
    symbolTable["TK_SGN"] = 'signal'
    first.append('signal')
    t.type = reserved.get(t.value)
    return t

def t_TK_FLTA(t):
    r'float'
    symbolTable["TK_FLT"] = 'float'
    first.append('float')
    t.type = reserved.get(t.value)
    return t

def t_TK_DATAI(t):
    r'\-*\d+\.*\d*'
    t.value = float(t.value)
    symbolTable["TK_DATAI"] = float(t.value)
    return t

def t_TK_OPEI(t):
    r'interpolate'
    t.type = reserved.get(t.value)
    symbolTable["TK_OPE"] = 'interpolate'
    return t

def t_TK_OPED(t):
    r'decimate'
    t.type = reserved.get(t.value)
    symbolTable["TK_OPE"] = 'decimate'
    return t

def t_TK_OPES(t):
    r'shift'
    t.type = reserved.get(t.value)
    symbolTable["TK_OPE"] = 'shift'
    return t

def t_TK_OPER(t):
    r'reflect'
    t.type = reserved.get(t.value)
    symbolTable["TK_OPE"] = 'reflect'
    return t

def t_TK_OPEA(t):
    r'amplitude'
    t.type = reserved.get(t.value)
    symbolTable["TK_OPE"] = 'amplitude'
    return t

def t_TK_DATAS(t):
    r'[a-zA-Z_][a-zA-Z]*\.wav'
    symbolTable["TK_DATA"] = t.value
    return t

def t_TK_NAME(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    first.append(t.value)
    return t

def t_TK_NAMEF(t):
    r'[a-z][a-z]*'
    first.append(t.value)
    return t

t_TK_SGN = t_TK_SGNA
t_TK_FLT = t_TK_FLTA
t_TK_ASIG = r'='
t_TK_LNBK = r';'
t_TK_LCOR = r'\['
t_TK_RCOR = r'\]'
t_TK_LPAR = r'\('
t_TK_RPAR = r'\)'

def t_error(t):
    print("Illegal Symbol '%s'" %t.value[0])
    t.lexer.skip(1)
    sys.exit()


lex.lex(debug=0)
          

class Information:
    """
    [symbolsTable]

    Arguments:
        dict {dictionary} -- [specific tokens]
    """
    def __init__(self, dict):
        self.dict = dict

    def getDict(self):
        return self.dict

class Details:
    """
    [detalis of the lexer]

    Arguments:
        first {list} -- [order of specific tokens]
    """
    def __init__(self, first):
        self.first = first
    
    def getFirst(self):
        return self.first

def conection():
    """
    [helper funtion to run the symbol table]

    Arguments:
        dict {dictionary} -- [specific tokens]
    """
    info = Information(symbolTable)
    symbols = info.getDict()
    return symbols

def conectionDetails():
    """
    [helper funtion to run the details]

    Arguments:
        first {list} -- [order of specific tokens]
    """
    details = Details(first)
    possibleError = details.getFirst()
    return possibleError

