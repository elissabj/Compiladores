import operators.mathOp as op
import operators.audioOp as audio
import operators.plotterOp as plt

def plot(files):
    """plots signals from option.files

    Arguments:
        options.files {array} -- [contains the files where the signals comes from]
    """
    kwargs = {f'{i}': audio.read(i).data for i in files}
    plt.plot(**kwargs)


def interpolate(ipath, factor, opath, plot):
    """[interpolates a signal by a factor options.factor]

    Arguments:
        options.factor {string}  -- [factor of interpolation]
        options.ipath  {string}  -- [path to the input signal]
        options.opath  {string}  -- [path for the output signal]
        options.plot   {boolean} -- [option to plot the signals]
    """
    signal = audio.read(ipath)
    result = op.interpolate(signal.data, int(factor))
    audio.write(opath, result, signal.rate, sampwidth=1)
    if plot:
        plt.plot(**{'Entrada: '+ipath: signal.data,
                        'Salida: '+opath: result})


def decimate(ipath, factor, opath, plot):
    """[downsample a signal by a factor options.factor]

    Arguments:
        options.factor {string}  -- [factor of interpolation]
        options.ipath  {string}  -- [path to the input signal]
        options.opath  {string}  -- [path for the output signal]
        options.plot   {boolean} -- [option to plot the signals]
    """
    signal = audio.read(ipath)
    result = op.decimate(signal.data, int(factor))
    audio.write(opath, result, signal.rate, sampwidth=1)
    if plot:
        plt.plot(**{'Entrada: '+ipath: signal.data,
                        'Salida: '+opath: result})


def shift(ipath, factor, opath, plot):
    """[shift a signal in time ]

    Arguments:
        options.factor {string}  -- [factor of interpolation]
        options.ipath  {string}  -- [path to the input signal]
        options.opath  {string}  -- [path for the output signal]
        options.plot   {boolean} -- [option to plot the signals]
    """
    signal = audio.read(ipath)
    result = op.shift(signal.data, int(factor))
    audio.write(opath, result, signal.rate, sampwidth=1)
    if plot:
        plt.plot(**{'Entrada: '+ipath: signal.data,
                        'Salida: '+opath: result})

def mamplitude(ipath, factor, opath, plot):
    """[modifies the amplitude of a signal]

    Arguments:
        options.factor {string}  -- [factor of interpolation]
        options.ipath  {string}  -- [path to the input signal]
        options.opath  {string}  -- [path for the output signal]
        options.plot   {boolean} -- [option to plot the signals]
    """
    signal = audio.read(ipath)
    result = op.mamplitude(signal.data, float(factor))
    audio.write(opath, result, signal.rate, sampwidth=1)
    if plot:
        plt.plot(**{'Entrada: '+ipath: signal.data,
                        'Salida: '+opath: result})


def reflect(ipath, opath, plot):
    """[reflect the signal in time]

    Arguments:
        options.ipath  {string}  -- [path to the input signal]
        options.opath  {string}  -- [path for the output signal]
        options.plot   {boolean} -- [option to plot the signals]
    """
    signal = audio.read(ipath)
    result = op.reflect(signal.data)
    audio.write(opath, result, signal.rate, sampwidth=1)
    if plot:
        plt.plot(**{'Entrada: '+ipath: signal.data,
                        'Salida: '+opath: result})


def decodeCode (line):
    """
    [clean the input]
    
    Arguments:
        code {str} --[input of .txt]
    """
    text = ''
    for i in range (0,len(line)):
        for j in range (0,len(line[i])):
            if line[i][j] == '\n' or line[i][j] == ' ':
                j += 1
            else:
                text += line[i][j]
    return text


import lexerS.lexer as lx
import sys

symbolTable = lx.conection()
first = lx.conectionDetails()

def isCorrect (s):
    """
    [produce token errors]

    Arguments:
        symbol table {dictionary} -- [tokens]    
    """
    if symbolTable['TK_OPE'] != "reflect":
        ct = 0
        ct2 = 0
        aux = ""
        aux_names = ""
        aux_namef = ""
        for i in range (0,len(s)):
            if s[i] == ";":
                ct +=1
            if ct >= 2:
                if ct == 2:
                    ct += 1
                    continue
                aux += s[i]
        
        ct = 0
        while ct < len(aux):
            
            if(aux[ct]) == '(':
                ct2 = ct+1
                while aux[ct2] != ',':
                    aux_names += aux[ct2]
                    ct2 += 1
                ct = ct2
            if (aux[ct] == ','):
                ct2 = ct+1
                while aux[ct2] != ')':
                    aux_namef += aux[ct2]
                    ct2 += 1
                ct = ct2
            
            ct += 1

        
        for i in range (0, len(first)):
            if first[i] == "signal":
                symbolTable["TK_NAMES"] = first[i+1]
            if first[i] == "float":
                symbolTable["TK_NAMEF"] = first[i+1]
            
        if symbolTable['TK_NAMES'] != aux_names:
            symbolTable["TK_ERROR"] = ('"Semantic Error '+aux_names+'"')
            print("Syntax Error '"+aux_names+"'")
            sys.exit()

        if symbolTable['TK_NAMEF'] != aux_namef:
            symbolTable["TK_ERROR"] =  ('"Semantic Error '+aux_namef+'"')
            print("Syntax Error '"+aux_namef+"'")
            sys.exit()

        

    ipath = symbolTable['TK_DATA']
    factor = symbolTable['TK_DATAI']
    opath = 'output.wav'
    plot='True'
    if symbolTable.keys() != 'TK_ERROR':
        if symbolTable['TK_OPE'] == "interpolate":
            factor = int(factor)
            interpolate(ipath, factor, opath, plot)
        elif symbolTable['TK_OPE'] == "decimate":
            factor = int(factor)
            decimate(ipath, factor, opath, plot)
        elif symbolTable['TK_OPE'] == "shift":
            factor = int(factor)
            shift(ipath, factor, opath, plot)
        elif symbolTable['TK_OPE'] == "amplitude":
            mamplitude(ipath, factor, opath, plot)
        elif symbolTable['TK_OPE'] == "reflect":
            reflect(ipath, opath, plot)
    