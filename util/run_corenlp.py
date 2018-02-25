
import os

CURRENT = os.path.dirname(os.path.realpath(__file__))
ROOT = (os.path.abspath(os.path.join(CURRENT, '..')))
OUTPUT = ROOT+'/util/output_corenlp.txt'

def call_corenlp(line):
    open(ROOT+'/util/tmp_sentences.txt', 'w').write(line)
    os.system('java -cp '+ROOT+'/stanford-corenlp-full-2017-06-09/stanford-corenlp-3.8.0.jar edu.stanford.nlp.parser.nndep.DependencyParser -model '+ROOT+'/model/dep-parser -tagger.model '+ROOT+'/model/pos-tagger.dat -textFile '+ROOT+'/util/tmp_sentences.txt > '+OUTPUT)
    return open(OUTPUT,'r').read()

if __name__ == '__main__':
    print(call_corenlp('Capítulo 7'))
