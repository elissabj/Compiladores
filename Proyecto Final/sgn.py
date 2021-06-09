import sys
import lexerS.lexer as lexer
import parseS.parse as parse
import sgnOp as op
sys.path.insert(0,"../..")


file = open("codigo.txt")
line = file.readlines()
data = op.decodeCode(line)
prog = parse.sgnParser(data)
op.isCorrect(data)
if not prog:
    raise SystemExit

