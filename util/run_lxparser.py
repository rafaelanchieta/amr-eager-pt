
import os

CURRENT = os.path.dirname(os.path.realpath(__file__))
ROOT = (os.path.abspath(os.path.join(CURRENT, '..')))

#INPUT = ROOT+'/files/dev.txt.tok'
OUTPUT = ROOT+'/util/output_lxparser.txt'

def call_lxparser(input):

    cmd = 'java -Xmx500m -cp '+ROOT+'/stanford-parser-2010-11-30/stanford-parser.jar edu.stanford.nlp.parser.lexparser.LexicalizedParser -tokenized -sentences newline -outputFormat oneline -uwModel edu.stanford.nlp.parser.lexparser.BaseUnknownWordModel '+ROOT+'/model/cintil.ser.gz '+input+' > '+OUTPUT
    os.system(cmd)
    return open(OUTPUT,'r').readlines()

if __name__ == '__main__':
    call_lxparser()

