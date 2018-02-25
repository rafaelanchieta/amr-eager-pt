import os
import nlpnet

CURRENT = os.path.dirname(os.path.realpath(__file__))
ROOT = (os.path.abspath(os.path.join(CURRENT, '..')))


def call_nlpnet(snt):
    tagger = nlpnet.POSTagger(ROOT+'/model_nlpnet/', language='pt')
    return tagger.tag(snt)[0]

# for word, tag in tags:
#    print(word, tag)
