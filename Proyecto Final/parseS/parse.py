from ply import *
import sys
import lexerS.lexer as lx

symbolsTable = lx.conection()
tokens = lx.tokens

"""
[definition of grammar]

Arguments: 
    tokens {LexToken} -- [tokens]
"""

def line(p):
    '''
    line : expression
    '''
    pass

def p_expression(p):
    '''
    expression : declaration declaration declarationFuntion TK_LNBK
    '''
    pass

def p_declaration(p):
    '''
    declaration : declareS 
    | declareI
    '''
    pass

def p_declareS(p):
    '''
    declareS : TK_SGN TK_LCOR TK_NAME TK_RCOR TK_ASIG TK_DATAS TK_LNBK
    '''
    pass

def p_declareI(p):
    '''
    declareI : TK_FLT TK_LCOR TK_NAME TK_RCOR TK_ASIG TK_DATAI TK_LNBK
    '''
    pass

def p_declarationFuntion(p):
    '''
    declarationFuntion : declareBasicOp 
    | declareOp
    '''
    pass

def p_declareBasicOp(p):
    '''
    declareBasicOp : TK_OPER TK_LPAR TK_NAME TK_RPAR 
    '''
    pass

def p_typeOperation(p):
    '''
    typeOperation : TK_OPED
    | TK_OPES
    | TK_OPEI
    | TK_OPEA
    '''
    pass
def p_declareOp(p):
    '''
    declareOp : typeOperation TK_LPAR TK_NAME ',' TK_NAME TK_RPAR 
    '''
    pass

def p_error(p): 
    global s
    if p:
        print("Syntax Error '%s'" %p.value)
        sys.exit()
    else: 
        print("EOF Error")
        sys.exit()


sParser = yacc.yacc() #parser construction

def sgnParser(code):
    """
    [run funtion]
    """
    sParser.error = 0
    p = sParser.parse(code)
    if sParser.error:
        return None
    return p  
